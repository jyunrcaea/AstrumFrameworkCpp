#pragma once
#include <functional>
#include <memory>
#include "AstrumComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"
#include "IAstrumColliderComponent.hpp"

namespace Astrum {
	class ColliderComponent : public Component, public IColliderComponent
	{
	public:
		ColliderComponent();

		virtual void Prepare() override;
		virtual void Release() override;
		void SetOnCollisionEnter(std::function<void(ColliderComponent*)>const& callback) { onCollisionEnter = callback; }
		void SetOnCollisionExit(std::function<void(ColliderComponent*)>const& callback) { onCollisionExit = callback; }
		auto GetOnCollisionEnter() const { return onCollisionEnter; }
		auto GetOnCollisionExit() const { return onCollisionExit; }
		void InvokeOnCollisionEnter(ColliderComponent* const other);
		void InvokeOnCollisionExit(ColliderComponent* const other);

		// 해당 충돌체가 가지는 비트마스크입니다.
		__int64 OwnBitmask = ~(0LL);
		// 수신할 비트 규칙입니다. 충돌 당한 대상의 비트마스크와 and 연산시 0이 아니여야 콜백을 수행합니다.
		__int64 ReceiveBitmask = ~(0LL);
	protected:
		virtual void SetOwner(IObject* const obj) override;

	private:
		std::function<void(ColliderComponent*)> onCollisionEnter;
		std::function<void(ColliderComponent*)> onCollisionExit;
	};
}