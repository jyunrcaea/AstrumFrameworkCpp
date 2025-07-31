#pragma once
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Collections/AstrumComponentList.hpp"
#include "../Components/IAstrumComponent.hpp"
#include <memory>

struct IAstrumComponent;
class AstrumComponentList;

struct IAstrumObject : public std::enable_shared_from_this<IAstrumObject> {
    virtual ~IAstrumObject() = default;

    virtual void Prepare() = 0;
    virtual void Update() = 0;
    virtual void Release() = 0;
    virtual void Draw() = 0;

    virtual AstrumObservedVector3& GetPosition() = 0;
    virtual AstrumObservedVector3& GetRotation() = 0;
    virtual AstrumObservedVector3& GetScale() = 0;

    void SetPosition(const AstrumObservedVector3& vec);
    void SetRotation(const AstrumObservedVector3& vec);
    void SetScale(const AstrumObservedVector3& vec);
    void SetPosition(const AstrumVector3& vec);
    void SetRotation(const AstrumVector3& vec);
    void SetScale(const AstrumVector3& vec);

    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetScale(float x, float y, float z);

    virtual const AstrumVector3& GetAbsolutePosition() const = 0;
    virtual const AstrumVector3& GetAbsoluteRotation() const = 0;
    virtual const AstrumVector3& GetAbsoluteScale() const = 0;

    virtual IAstrumObject* GetParent() const = 0;
    virtual bool SetParent(IAstrumObject* const parent) = 0;
    virtual bool ClearParent(IAstrumObject* const parent) = 0;

    virtual AstrumComponentList& GetComponents() = 0;

    bool AddComponent(std::shared_ptr<struct IAstrumComponent> const component);
    bool RemoveComponent(std::shared_ptr<struct IAstrumComponent> const component);
    void ClearComponent();

    virtual void UpdateAbsolutePosition() = 0;
    virtual void UpdateAbsoluteRotation() = 0;
    virtual void UpdateAbsoluteScale() = 0;

    virtual bool IsPrepared() const = 0;
};