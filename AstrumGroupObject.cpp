#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"

AstrumGroupObject::AstrumGroupObject() : objects(std::make_unique<AstrumObjectList>(this)) {
}

void AstrumGroupObject::Update() {
    objects->ForEach([](shared_ptr<IAstrumObject> obj) {
        obj->Update();
    });
}

void AstrumGroupObject::Release() {
    objects->Clear();
}

void AstrumGroupObject::Draw() {
    if (visible) {
        objects->ForEach([](shared_ptr<IAstrumObject> obj) {
            obj->Draw();
        });
    }
}

AstrumObjectList* AstrumGroupObject::GetObjects() { return objects.get(); }