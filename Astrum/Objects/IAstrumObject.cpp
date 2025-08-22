#include "IAstrumObject.hpp"

namespace Astrum {
	void IAstrumObject::SetPosition(const ObservedVector3& vec) { GetPosition().Reset(vec); }
	void IAstrumObject::SetRotation(const ObservedVector3& vec) { GetRotation().Reset(vec); }
	void IAstrumObject::SetScale(const ObservedVector3& vec) { GetScale().Reset(vec); }
	void IAstrumObject::SetPosition(const Vector3& vec) { GetPosition().Reset(vec); }
	void IAstrumObject::SetRotation(const Vector3& vec) { GetRotation().Reset(vec); }
	void IAstrumObject::SetScale(const Vector3& vec) { GetScale().Reset(vec); }

	void IAstrumObject::SetPosition(float x, float y, float z) { GetPosition().Reset(x, y, z); }
	void IAstrumObject::SetPositionX(float x) { GetPosition().SetX(x); }
	void IAstrumObject::SetPositionY(float y) { GetPosition().SetY(y); }
	void IAstrumObject::SetPositionZ(float z) { GetPosition().SetZ(z); }
	void IAstrumObject::SetRotation(float x, float y, float z) { GetRotation().Reset(x, y, z); }
	void IAstrumObject::SetRotationX(float x) { GetRotation().SetX(x); }
	void IAstrumObject::SetRotationY(float y) { GetRotation().SetY(y); }
	void IAstrumObject::SetRotationZ(float z) { GetRotation().SetZ(z); }
	void IAstrumObject::SetScale(float x, float y, float z) { GetScale().Reset(x, y, z); }
	void IAstrumObject::SetScaleX(float x) { GetScale().SetX(x); }
	void IAstrumObject::SetScaleY(float y) { GetScale().SetY(y); }
	void IAstrumObject::SetScaleZ(float z) { GetScale().SetZ(z); }

	bool IAstrumObject::AddComponent(const std::shared_ptr<struct IComponent>& component) { return GetComponents().Add(component); }
	bool IAstrumObject::RemoveComponent(const std::shared_ptr<struct IComponent>& component) { return GetComponents().Remove(component); }
	void IAstrumObject::ClearComponent() { GetComponents().Clear(); }
}