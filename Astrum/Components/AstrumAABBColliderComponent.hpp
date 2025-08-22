#pragma once
#include <memory>
#include "AstrumColliderComponent.hpp"
#include "IAstrumAABBColliderComponent.hpp"

namespace Astrum {
	class AABBColliderComponent : public ColliderComponent, public IAABBColliderComponent
	{
	public:
		virtual ColliderType GetColliderType() const override { return ColliderType::ColliderType_AABB; }
		virtual Rect GetRect() const;

		virtual bool IsOverlap(IColliderComponent* other) override;
		virtual bool IsOverlapToAABB(IAABBColliderComponent* other) override;
		virtual bool IsOverlapToOBB(IOBBColliderComponent* other) override;
		virtual bool IsOverlapToCircle(ICircleColliderComponent* other) override;

		virtual bool IsOverlapToPoint(Vector2 point) override;

	public:
		static std::shared_ptr<AABBColliderComponent> MakeShared() {
			return std::make_shared<AABBColliderComponent>();
		}
	};
}