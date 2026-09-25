#include "AstrumObjectList.hpp"

AstrumObjectList::AstrumObjectList(IAstrumGroupObject* const owner) : owner(owner)
{
}

bool AstrumObjectList::Add(const std::shared_ptr<IAstrumObject>& obj) {
    if (nullptr == obj || objectSet.contains(obj.get())) return false;
    //컬렉션에 객체를 추가할때마다, 자식에게 부모가 누구인지 할당하는 작업을 해줘요.
    if (false == obj->SetParent(owner)) return false;

    objects.PushBack(obj);
    objectSet.insert(obj.get());
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

    // 인자가 목록 안의 shared_ptr를 가리키는 참조일 수도 있으므로 복사해 둡니다.
    const std::shared_ptr<IAstrumObject> target = obj;
    objectSet.erase(target.get());
    objects.Erase(target.get());
    if (owner->IsPrepared()) target->Release();
    return true;
}

void AstrumObjectList::Clear() {
    // 목록을 먼저 비운 뒤 처리하므로, Release() 도중에 목록이 바뀌어도 안전합니다.
    const auto removed = objects.TakeAll();
    objectSet.clear();

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
    return static_cast<int>(objects.Count());
}

void AstrumObjectList::ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) {
    objects.ForEachShared(func);
}

std::vector<std::shared_ptr<IAstrumObject>> AstrumObjectList::ToArray() const {
    return objects.ToVector();
}
