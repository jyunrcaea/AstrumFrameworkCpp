#pragma once
#include <functional>
#include <memory>
#include "AstrumComponent.h"
#include "AstrumCollisionSystem.h"

enum AstrumColliderType
{
	AstrumColliderType_None = 0,
	AstrumColliderType_AABB,
	AstrumColliderType_Circle,
	AstrumColliderType_OBB,
	AstrumColliderType_Count
};

class AstrumColliderComponent : public AstrumComponent, public std::enable_shared_from_this<AstrumColliderComponent>
{
public:
	AstrumColliderComponent();

	virtual void Prepare() override;
	virtual void Release() override;
	void SetOnCollisionEnter(std::function<void(AstrumColliderComponent*)>const& callback) { onCollisionEnter = callback; }
	void SetOnCollisionExit(std::function<void(AstrumColliderComponent*)>const& callback) { onCollisionExit = callback; }
	auto GetOnCollisionEnter() const { return onCollisionEnter; }
	auto GetOnCollisionExit() const { return onCollisionExit; }
	void InvokeOnCollisionEnter(AstrumColliderComponent* const other);
	void InvokeOnCollisionExit(AstrumColliderComponent* const other);

	virtual AstrumColliderType GetColliderType() const;
protected:
	virtual void SetOwner(IAstrumObject* const obj) override;

private:
	std::function<void(AstrumColliderComponent*)> onCollisionEnter;
	std::function<void(AstrumColliderComponent*)> onCollisionExit;
};