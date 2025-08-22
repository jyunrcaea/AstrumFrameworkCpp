#pragma once
#include "AstrumColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"

namespace Astrum {
	class CircleColliderComponent : public ColliderComponent, public ICircleColliderComponent
	{
	public:
		virtual ColliderType GetColliderType() const override { return ColliderType::ColliderType_Circle; }
		virtual Circle GetCircle() const;

		virtual bool IsOverlap(IColliderComponent* other) override;
		virtual bool IsOverlapToAABB(IAABBColliderComponent* other) override;
		virtual bool IsOverlapToOBB(IOBBColliderComponent* other) override;
		virtual bool IsOverlapToCircle(ICircleColliderComponent* other) override;

		virtual bool IsOverlapToPoint(Vector2 point) override;

	public:
		static std::shared_ptr<CircleColliderComponent> MakeShared() {
			return std::make_shared<CircleColliderComponent>();
		}
	};
}