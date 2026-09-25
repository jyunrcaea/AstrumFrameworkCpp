#include "AstrumObjectList.hpp"
#include <algorithm>

AstrumObjectList::AstrumObjectList(IAstrumGroupObject* const owner) : owner(owner)
{
}

bool AstrumObjectList::Add(const std::shared_ptr<IAstrumObject>& obj) {
    if (nullptr == obj || objectSet.contains(obj.get())) return false;
    //컬렉션에 객체를 추가할때마다, 자식에게 부모가 누구인지 할당하는 작업을 해줘요.
    if (false == obj->SetParent(owner)) return false;

    objects.push_back(obj);
    objectSet.insert(obj.get());
    changed = true;
    if (owner->IsPrepared()) obj->Prepare();
    return true;
}

void AstrumObjectList::AddRange(const std::initializer_list<std::shared_ptr<IAstrumObject>>& list)
{
    for (auto& obj : list) Add(obj);
}

bool AstrumObjectList::Remove(const std::shared_ptr<IAstrumObject>& obj) {
    if (nullptr == obj || false == objectSet.contains(obj.get())) return false;
    //삭제할때도 자식에게 부모가 더이상 없음을 알려요.
    if (false == obj->ClearParent(owner)) return false;

    objectSet.erase(obj.get());
    objects.erase(std::find(objects.begin(), objects.end(), obj));
    changed = true;
    if (owner->IsPrepared()) obj->Release();
    return true;
}

void AstrumObjectList::Clear() {
    // Release() 도중에 목록이 바뀌어도 안전하도록 먼저 비운 뒤 처리합니다.
    std::vector<std::shared_ptr<IAstrumObject>> removed;
    removed.swap(objects);
    objectSet.clear();
    changed = true;

    const bool prepared = owner->IsPrepared();
    for (auto& obj : removed) {
        obj->ClearParent(owner);
        if (prepared) obj->Release();
    }
}

bool AstrumObjectList::Contains(const std::shared_ptr<IAstrumObject>& obj) const {
    return objectSet.contains(obj.get());
}

int AstrumObjectList::Count() const {
    return static_cast<int>(objects.size());
}

void AstrumObjectList::ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) {
    RefreshSnapshot();

    // 바깥 순회 도중에 목록이 바뀐 상태에서 중첩 순회하는 경우(예: 자식을 추가한 뒤 부모를 이동),
    // 바깥 순회 중인 스냅샷은 건드리지 않고 최신 목록의 복사본을 순회합니다.
    std::vector<std::shared_ptr<IAstrumObject>> latest;
    if (changed) latest = objects;
    const auto& targets = changed ? latest : snapshot;

    // 예외가 발생해도 순회 깊이가 복구되도록 합니다.
    struct IterationGuard {
        int& depth;
        IterationGuard(int& depth) : depth(depth) { ++depth; }
        ~IterationGuard() { --depth; }
    } guard(iterationDepth);

    for (const auto& obj : targets) {
        // 순회 도중에 이 컬렉션에서 제거된 객체는 건너뜁니다. (Release() 이후에 Update()/Draw()가 호출되지 않도록)
        if (obj->GetParent() != owner) continue;
        func(obj);
    }
}

std::vector<std::shared_ptr<IAstrumObject>> AstrumObjectList::ToArray() const {
    return objects;
}

void AstrumObjectList::RefreshSnapshot() {
    // 순회 도중에는 스냅샷을 바꾸면 순회 중인 배열이 무효화되므로 갱신하지 않습니다.
    if (changed && 0 == iterationDepth) {
        snapshot = objects;
        changed = false;
    }
}
