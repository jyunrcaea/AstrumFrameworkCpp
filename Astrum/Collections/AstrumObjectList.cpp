#include "AstrumObjectList.hpp"

AstrumObjectList::AstrumObjectList(IAstrumGroupObject* const owner) : owner(owner)
{
}

bool AstrumObjectList::Add(const std::shared_ptr<IAstrumObject>& obj) {
    //컬렉션에 객체를 추가할때마다, 자식에게 부모가 누구인지 할당하는 작업을 해줘요.
    if (obj->SetParent(owner) && objectSet.insert(obj).second) {
        if (owner->IsPrepared()) obj->Prepare();
        changed = true;
        return true;
    }
    return false;
}

void AstrumObjectList::AddRange(const std::initializer_list<std::shared_ptr<IAstrumObject>>& objects)
{
    for (auto& obj : objects) Add(obj);
}

bool AstrumObjectList::Remove(const std::shared_ptr<IAstrumObject>& obj) {
    //삭제할때도 자식에게 부모가 더이상 없음을 알려요.
    if (obj->ClearParent(owner) && objectSet.erase(obj) > 0) {
        if (owner->IsPrepared()) obj->Release();
        changed = true;
        return true;
    }
    return false;
}

void AstrumObjectList::Clear() {
    ForEach([&](const std::shared_ptr<IAstrumObject>& obj) {
        obj->ClearParent(owner);
        if (owner->IsPrepared()) obj->Release();
    });
    objectSet.clear();
    objectArray.clear();
    changed = false;
}

bool AstrumObjectList::Contains(const std::shared_ptr<IAstrumObject>& obj) const {
    return objectSet.find(obj) != objectSet.end();
}

int AstrumObjectList::Count() const {
    return static_cast<int>(objectSet.size());
}

void AstrumObjectList::ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) {
    Update();
    for (auto& obj : objectArray) {
        func(obj);
    }
}

std::vector<std::shared_ptr<IAstrumObject>> AstrumObjectList::ToArray() const {
    Update();
    return objectArray;
}

void AstrumObjectList::Update() const {
    if (changed) {
        objectArray.assign(objectSet.begin(), objectSet.end());
        changed = false;
    }
}