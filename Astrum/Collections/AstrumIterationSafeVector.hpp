#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <algorithm>

/// <summary>
/// 순회 도중에 추가/삭제되어도 안전한, 추가된 순서를 유지하는 shared_ptr 목록입니다. (AstrumObjectList, AstrumComponentList의 내부 저장소)
/// - 순회 중이 아닐 때: 추가는 뒤에 붙이고, 삭제는 바로 지웁니다.
/// - 순회 중일 때: 추가는 똑같이 뒤에 붙이고(진행 중인 순회에는 포함되지 않고, 중첩 순회와 다음 순회부터 포함),
///   삭제는 그 칸을 nullptr(툼스톤)로 바꿔 진행 중인 순회에서 즉시 건너뛰게 합니다.
///   삭제된 객체는 graveyard가 가장 바깥 순회가 끝날 때까지 붙잡아 두므로, 자기 자신을 삭제한 객체가 실행 도중 소멸하지 않습니다.
/// - 가장 바깥 순회가 끝나면 툼스톤을 정리합니다.
/// 스냅샷 복사나 std::function 없이 인덱스로 순회하므로, 순회 비용은 vector를 직접 range-for로 도는 것과 같습니다.
/// </summary>
template <typename T>
class AstrumIterationSafeVector {
public:
    using Pointer = std::shared_ptr<T>;

    /// <summary>
    /// 순회 범위입니다. 살아있는 동안 순회 중으로 표시되며, range-for에서 T*를 차례로 돌려줍니다. (nullptr인 칸은 건너뜀)
    /// 예: for (T* item : list.Iterate()) { ... }
    /// </summary>
    class Range {
    public:
        class Iterator {
        public:
            T* operator*() const { return (*items)[index].get(); }
            Iterator& operator++() { ++index; SkipEmpty(); return *this; }
            bool operator!=(const Iterator& other) const { return index != other.index; }

        private:
            friend class Range;
            Iterator(const std::vector<Pointer>* source, size_t startIndex, size_t endIndex) : items(source), index(startIndex), end(endIndex) { SkipEmpty(); }
            // 순회 도중 추가로 벡터가 재할당될 수 있으므로, 데이터 포인터가 아닌 벡터를 가리키고 매번 인덱스로 읽습니다.
            void SkipEmpty() { while (index < end && nullptr == (*items)[index]) ++index; }

            const std::vector<Pointer>* items;
            size_t index;
            size_t end;
        };

        explicit Range(AstrumIterationSafeVector& target) : owner(target), count(target.items.size()) { ++owner.iterationDepth; }
        ~Range() { owner.EndIteration(); }
        Range(const Range&) = delete;
        Range& operator=(const Range&) = delete;

        // 순회를 시작할 때의 개수까지만 순회합니다. (순회 도중 뒤에 추가된 항목은 다음 순회부터)
        Iterator begin() const { return Iterator(&owner.items, 0, count); }
        Iterator end() const { return Iterator(&owner.items, count, count); }

    private:
        AstrumIterationSafeVector& owner;
        const size_t count;
    };

    AstrumIterationSafeVector() = default;
    AstrumIterationSafeVector(const AstrumIterationSafeVector&) = delete;
    AstrumIterationSafeVector& operator=(const AstrumIterationSafeVector&) = delete;

    /// <summary>
    /// 안전하게 순회할 수 있는 범위를 반환합니다. (반환된 Range가 살아있는 동안 순회 중으로 취급)
    /// </summary>
    Range Iterate() { return Range(*this); }

    /// <summary>
    /// 모든 항목에 대해 func(const std::shared_ptr&lt;T&gt;&amp;)를 호출합니다. 콜백 안에서 추가가 일어나 벡터가 재할당되어도 안전하도록 복사본을 넘깁니다.
    /// (shared_ptr가 필요한 인터페이스용. 성능이 중요하면 Iterate()를 사용하세요.)
    /// </summary>
    template <typename Function>
    void ForEachShared(Function&& func) {
        Range range(*this);
        for (size_t i = 0, count = items.size(); i < count; ++i) {
            if (nullptr == items[i]) continue;
            const Pointer item = items[i];
            func(item);
        }
    }

    /// <summary>
    /// 뒤에 추가합니다. (중복 검사는 호출하는 쪽에서 합니다.)
    /// </summary>
    void PushBack(const Pointer& item) {
        items.push_back(item);
        ++liveCount;
    }

    /// <summary>
    /// 항목을 제거합니다. 순회 중이면 툼스톤으로 표시하고 가장 바깥 순회가 끝날 때 정리합니다.
    /// </summary>
    /// <returns>항목을 찾아 제거했으면 true</returns>
    bool Erase(const T* target) {
        if (nullptr == target) return false;
        const auto it = std::find_if(items.begin(), items.end(), [target](const Pointer& item) { return item.get() == target; });
        if (it == items.end()) return false;

        if (0 == iterationDepth) {
            items.erase(it);
        }
        else {
            graveyard.push_back(std::move(*it));
            *it = nullptr;
            hasTombstones = true;
        }
        --liveCount;
        return true;
    }

    /// <summary>
    /// 모든 항목을 제거하고, 제거된 항목들을 추가된 순서대로 반환합니다. (순회 중이면 툼스톤으로 표시)
    /// </summary>
    std::vector<Pointer> TakeAll() {
        std::vector<Pointer> removed;
        removed.reserve(liveCount);
        if (0 == iterationDepth) {
            for (auto& item : items) {
                if (nullptr != item) removed.push_back(std::move(item));
            }
            items.clear();
        }
        else {
            for (auto& item : items) {
                if (nullptr == item) continue;
                removed.push_back(item);
                graveyard.push_back(std::move(item));
                item = nullptr;
                hasTombstones = true;
            }
        }
        liveCount = 0;
        return removed;
    }

    /// <summary>
    /// 살아있는(제거되지 않은) 항목의 개수입니다.
    /// </summary>
    size_t Count() const { return liveCount; }

    /// <summary>
    /// 살아있는 항목 중 index번째 항목을 반환합니다. (범위를 벗어나면 nullptr)
    /// </summary>
    T* At(size_t index) const {
        if (false == hasTombstones) return index < items.size() ? items[index].get() : nullptr;
        for (const auto& item : items) {
            if (nullptr == item) continue;
            if (0 == index--) return item.get();
        }
        return nullptr;
    }

    /// <summary>
    /// 살아있는 항목들을 추가된 순서대로 복사해서 반환합니다.
    /// </summary>
    std::vector<Pointer> ToVector() const {
        std::vector<Pointer> result;
        result.reserve(liveCount);
        for (const auto& item : items) {
            if (nullptr != item) result.push_back(item);
        }
        return result;
    }

private:
    void EndIteration() {
        if (0 != --iterationDepth || false == hasTombstones) return;

        std::erase(items, nullptr);
        hasTombstones = false;
        // 소멸자가 다시 이 목록을 건드려도 상태가 일관되도록, 목록을 먼저 정리한 뒤 마지막에 해제합니다.
        const auto released = std::move(graveyard);
        graveyard.clear();
    }

    // 추가된 순서대로의 항목. 순회 중에 제거된 칸은 nullptr(툼스톤)입니다.
    std::vector<Pointer> items;
    // 순회 중에 제거된 항목을 가장 바깥 순회가 끝날 때까지 살려두는 곳
    std::vector<Pointer> graveyard;
    size_t liveCount = 0;
    int iterationDepth = 0;
    bool hasTombstones = false;
};
