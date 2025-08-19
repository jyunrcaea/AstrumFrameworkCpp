#pragma once
#include <functional>
#include <memory>
#include "AstrumComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"
#include "IAstrumColliderComponent.hpp"

class AstrumColliderComponent : public AstrumComponent, public IAstrumColliderComponent
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

	// 해당 충돌체가 가지는 비트마스크입니다.
	__int64 OwnBitmask = ~(0LL);
	// 수신할 비트 규칙입니다. 충돌 당한 대상의 비트마스크와 and 연산시 0이 아니여야 콜백을 수행합니다.
	__int64 ReceiveBitmask = ~(0LL);
protected:
	virtual void SetOwner(IAstrumObject* const obj) override;

private:
	std::function<void(AstrumColliderComponent*)> onCollisionEnter;
	std::function<void(AstrumColliderComponent*)> onCollisionExit;
};