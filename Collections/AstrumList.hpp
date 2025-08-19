#pragma once
#include <memory>
#include <unordered_set>
#include <vector>
#include <functional>
#include <initializer_list>

// 빠르고 안정적인 순회를 지원하는 템플릿 리스트
template <typename T>
class AstrumList {
public:
    // 객체 추가 (중복이거나 nullptr 일경우 무시)
    bool Add(const std::shared_ptr<T>& obj) {
        if (nullptr == obj || true == objectSet.contains(obj)) return false;
        objectSet.insert(obj);
        changed = true;
        return true;
    }
    // 여러 객체 추가
    void AddRange(const std::initializer_list<std::shared_ptr<T>>& objects) {
        for (const auto& obj : objects) { Add(obj); }
    }
	// 객체 제거 (존재하지 않거나 nullptr 일경우 무시)
    bool Remove(const std::shared_ptr<T>& obj) {
        if (nullptr == obj || false == objectSet.contains(obj)) return false;
        objectSet.erase(obj);
        changed = true;
        return true;
    }
    // 전체 제거
    void Clear() {
        objectSet.clear();
        objectArray.clear();
        changed = false;
    }
    // 포함 여부
    bool Contains(const std::shared_ptr<T>& obj) const {
        return objectSet.contains(obj);
    }
    // 개수 반환
    int Count() const {
        return static_cast<int>(objectSet.size());
    }
    // 순회
    void ForEach(const std::function<void(const std::shared_ptr<T>&)>& func) {
        Update();
        for (const auto& obj : objectArray) {
            func(obj);
        }
    }
    // 배열 복사
    std::vector<std::shared_ptr<T>> ToArray() const {
        Update();
        return objectArray;
    }

    auto begin() { Update(); return objectArray.begin(); }
    auto end() { Update(); return objectArray.end(); }
    auto begin() const { Update(); return objectArray.begin(); }
    auto end() const { Update(); return objectArray.end(); }
    auto cbegin() const { Update(); return objectArray.cbegin(); }
    auto cend() const { Update(); return objectArray.cend(); }

private:
    void Update() const {
		if (false == changed) return;
        objectArray.assign(objectSet.begin(), objectSet.end());
        changed = false;
    }

    std::unordered_set<std::shared_ptr<T>> objectSet;
    mutable std::vector<std::shared_ptr<T>> objectArray;
    mutable bool changed = false;
};