#include "AstrumObjectList.hpp"
#include <bits/stdc++.h>

AstrumObjectList::AstrumObjectList(std::shared_ptr<IAstrumObject> owner)
    : owner(owner)
{
}

bool AstrumObjectList::Add(std::shared_ptr<IAstrumObject> obj) {
    if (obj->SetParent(owner.get()) && objectSet.insert(obj).second) {
        obj->Prepare();
        changed = true;
        return true;
    }
    return false;
}

bool AstrumObjectList::Remove(std::shared_ptr<IAstrumObject> obj) {
    if (obj->ClearParent(owner.get()) && objectSet.erase(obj) > 0) {
        obj->Release();
        changed = true;
        return true;
    }
    return false;
}

void AstrumObjectList::Clear() {
    ForEach([&](std::shared_ptr<IAstrumObject> obj) {
        obj->ClearParent(owner.get());
        obj->Release();
        });
    objectSet.clear();
    objectArray.clear();
    changed = false;
}

bool AstrumObjectList::Contains(std::shared_ptr<IAstrumObject> obj) const {
    return objectSet.find(obj) != objectSet.end();
}

int AstrumObjectList::Count() const {
    return static_cast<int>(objectSet.size());
}

void AstrumObjectList::ForEach(const std::function<void(std::shared_ptr<IAstrumObject>)>& func) {
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