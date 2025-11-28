#pragma once
#include <functional>
#include <memory>
#include "AstrumComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"
#include "IAstrumColliderComponent.hpp"

/// <summary>
/// 충돌 감지 및 충돌 이벤트를 처리하는 컴포넌트입니다.
/// 다양한 충돌체 타입(AABB, OBB, 원형)과의 충돌을 감지하고,
/// 충돌 진입/종료 콜백을 호출합니다.
/// </summary>
class AstrumColliderComponent : public AstrumComponent, public IAstrumColliderComponent
{
public:
	/// <summary>
	/// 충돌 컴포넌트를 생성합니다.
	/// </summary>
	AstrumColliderComponent();

	/// <summary>
	/// 충돌 컴포넌트를 준비합니다.
	/// 충돌 시스템에 등록됩니다.
	/// </summary>
	virtual void Prepare() override;
	/// <summary>
	/// 충돌 컴포넌트를 해제합니다.
	/// 충돌 시스템에서 등록 해제됩니다.
	/// </summary>
	virtual void Release() override;
	/// <summary>
	/// 충돌 진입 시 호출될 콜백 함수를 설정합니다.
	/// </summary>
	/// <param name="callback">충돌한 다른 충돌체 컴포넌트를 매개변수로 받는 콜백 함수입니다.</param>
	void SetOnCollisionEnter(std::function<void(AstrumColliderComponent*)>const& callback) { onCollisionEnter = callback; }
	/// <summary>
	/// 충돌 종료 시 호출될 콜백 함수를 설정합니다.
	/// </summary>
	/// <param name="callback">충돌이 종료된 다른 충돌체 컴포넌트를 매개변수로 받는 콜백 함수입니다.</param>
	void SetOnCollisionExit(std::function<void(AstrumColliderComponent*)>const& callback) { onCollisionExit = callback; }
	/// <summary>
	/// 충돌 진입 콜백 함수를 반환합니다.
	/// </summary>
	/// <returns>설정된 충돌 진입 콜백 함수입니다.</returns>
	auto GetOnCollisionEnter() const { return onCollisionEnter; }
	/// <summary>
	/// 충돌 종료 콜백 함수를 반환합니다.
	/// </summary>
	/// <returns>설정된 충돌 종료 콜백 함수입니다.</returns>
	auto GetOnCollisionExit() const { return onCollisionExit; }
	/// <summary>
	/// 충돌 진입 콜백을 호출합니다.
	/// </summary>
	/// <param name="other">충돌한 다른 충돌체 컴포넌트입니다.</param>
	void InvokeOnCollisionEnter(AstrumColliderComponent* const other);
	/// <summary>
	/// 충돌 종료 콜백을 호출합니다.
	/// </summary>
	/// <param name="other">충돌이 종료된 다른 충돌체 컴포넌트입니다.</param>
	void InvokeOnCollisionExit(AstrumColliderComponent* const other);

	/// <summary>
	/// 이 충돌체가 가지는 식별 비트마스크입니다.
	/// 충돌 필터링에 사용되어 충돌 시스템이 이 충돌체의 종류를 식별합니다.
	/// 기본값은 모든 비트가 1입니다. (~(0LL))
	/// </summary>
	__int64 OwnBitmask = ~(0LL);
	/// <summary>
	/// 충돌을 수신할 대상을 결정하는 비트마스크입니다.
	/// 충돌 대상의 OwnBitmask와 AND 연산했을 때 0이 아니면 콜백이 호출됩니다.
	/// 기본값은 모든 비트가 1입니다. (~(0LL)) - 모든 충돌을 수신합니다.
	/// </summary>
	__int64 ReceiveBitmask = ~(0LL);
protected:
	/// <summary>
	/// 충돌 컴포넌트의 소유 객체를 설정합니다.
	/// </summary>
	/// <param name="obj">소유할 게임 객체입니다.</param>
	virtual void SetOwner(IAstrumObject* const obj) override;

private:
	/// <summary>
	/// 충돌 진입 시 호출될 콜백 함수입니다.
	/// </summary>
	std::function<void(AstrumColliderComponent*)> onCollisionEnter;
	/// <summary>
	/// 충돌 종료 시 호출될 콜백 함수입니다.
	/// </summary>
	std::function<void(AstrumColliderComponent*)> onCollisionExit;
};