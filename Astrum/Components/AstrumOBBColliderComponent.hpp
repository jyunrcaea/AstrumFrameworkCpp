#pragma once
#include <algorithm>
#include <cmath>
#include <DirectXMath.h>
#include "AstrumColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"
#include "AstrumCircleColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"

namespace Astrum {
	class OBBColliderComponent : public ColliderComponent, public IOBBColliderComponent
	{
	public:
		virtual ColliderType GetColliderType() const override { return ColliderType::ColliderType_OBB; }
		virtual RotatedRect GetRotatedRect() const;
		virtual CenterHalfRect GetCenterHalfRect() const override;
		virtual std::pair<Vector2, Vector2> GetAxes() const override;

		virtual bool IsOverlap(IColliderComponent* other) override;
		virtual bool IsOverlapToAABB(IAABBColliderComponent* other) override;
		virtual bool IsOverlapToOBB(IOBBColliderComponent* other) override;
		virtual bool IsOverlapToCircle(ICircleColliderComponent* other) override;

		virtual bool IsOverlapToPoint(Vector2 point) override;
	public:
		static std::shared_ptr<OBBColliderComponent> MakeShared() {
			return std::make_shared<OBBColliderComponent>();
		}
	};
}