#pragma once
#include "IAstrumObject.hpp"
#include "AstrumVector3.hpp"
#include <memory>

class AstrumObject : public IAstrumObject {
public:
    virtual void Prepare() override {}
    virtual void Update() override {}
    virtual void Release() override {}
    virtual void Draw() override {}

    AstrumVector3& GetPosition() override { return position; }
    AstrumVector3& GetRotation() override { return rotation; }
    AstrumVector3& GetScale() override { return scale; }

    bool IsVisible() const override { return visible; }
    IAstrumObject* GetParent() const override { return parent; }

    bool SetParent(IAstrumObject* p) override {
        if (parent != nullptr) return false;
        parent = p;
        return true;
    }

    bool ClearParent(IAstrumObject* p) override {
        if (parent != p) return false;
        parent = nullptr;
        return true;
    }

protected:
    AstrumVector3 position{};
    AstrumVector3 rotation{};
    AstrumVector3 scale{1,1,1};

    bool visible = true;
    IAstrumObject* parent = nullptr;
};
