#pragma once
#include <memory>
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Collections/IAstrumComponentList.hpp"
#include "../Components/IAstrumComponent.hpp"

struct IAstrumComponent;
struct IAstrumComponentList;
struct IAstrumGroupObject;

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
    void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

    void SetRotation(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);

    void SetScale(float x, float y, float z);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

    virtual const AstrumVector3& GetAbsolutePosition() = 0;
    virtual const AstrumVector3& GetAbsoluteRotation() = 0;
    virtual const AstrumVector3& GetAbsoluteScale() = 0;

    virtual IAstrumGroupObject* GetParent() const = 0;
    virtual bool SetParent(IAstrumGroupObject* const parent) = 0;
    virtual bool ClearParent(IAstrumGroupObject* const parent) = 0;

    virtual IAstrumComponentList& GetComponents() = 0;

    bool AddComponent(const std::shared_ptr<struct IAstrumComponent>& component);
    bool RemoveComponent(const std::shared_ptr<struct IAstrumComponent>& component);
    void ClearComponent();

    virtual void UpdateAbsolutePosition() = 0;
    virtual void UpdateAbsoluteRotation() = 0;
    virtual void UpdateAbsoluteScale() = 0;

	virtual void SetVisible(bool enable) = 0;

    virtual bool IsPrepared() const = 0;
	virtual bool IsVisible() const = 0;
};