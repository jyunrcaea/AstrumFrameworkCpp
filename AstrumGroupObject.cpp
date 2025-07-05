#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"

AstrumGroupObject::AstrumGroupObject()
    : selfPtr(std::shared_ptr<AstrumObject>(this, [](AstrumObject*){})),
      objects(std::make_shared<AstrumObjectList>(selfPtr)) {
}

void AstrumGroupObject::Update() {
    objects->ForEach([](std::shared_ptr<IAstrumObject> obj) {
        obj->Update();
    });
}

void AstrumGroupObject::Release() {
    objects->Clear();
}

void AstrumGroupObject::Draw() {
    if (visible) {
        objects->ForEach([](std::shared_ptr<IAstrumObject> obj) {
            obj->Draw();
        });
    }
}

std::shared_ptr<AstrumObjectList>& AstrumGroupObject::GetObjects() { return objects; }