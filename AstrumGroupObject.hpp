#pragma once
#include "AstrumObject.hpp"
#include "AstrumObjectList.hpp"
#include <memory>

class AstrumGroupObject : public AstrumObject {
public:
    AstrumGroupObject()
        : selfPtr(std::shared_ptr<AstrumObject>(this, [](AstrumObject*){})),
          objects(std::make_shared<AstrumObjectList>(selfPtr)) {
    }

    void Update() override {
        objects->ForEach([](std::shared_ptr<IAstrumObject> obj) {
            obj->Update();
        });
    }

    void Release() override {
        objects->Clear();
    }

    void Draw() override {
        if (visible) {
            objects->ForEach([](std::shared_ptr<IAstrumObject> obj) {
                obj->Draw();
            });
        }
    }

    std::shared_ptr<AstrumObjectList>& GetObjects() { return objects; }

private:
    std::shared_ptr<AstrumObject> selfPtr;
    std::shared_ptr<AstrumObjectList> objects;
};
