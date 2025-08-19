#include "IAstrumObject.hpp"

void IAstrumObject::SetPosition(const AstrumObservedVector3& vec) { GetPosition().Reset(vec); }
void IAstrumObject::SetRotation(const AstrumObservedVector3& vec) { GetRotation().Reset(vec); }
void IAstrumObject::SetScale(const AstrumObservedVector3& vec) { GetScale().Reset(vec); }
void IAstrumObject::SetPosition(const AstrumVector3& vec) { GetPosition().Reset(vec); }
void IAstrumObject::SetRotation(const AstrumVector3& vec) { GetRotation().Reset(vec); }
void IAstrumObject::SetScale(const AstrumVector3& vec) { GetScale().Reset(vec); }

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

bool IAstrumObject::AddComponent(const std::shared_ptr<struct IAstrumComponent>& component) { return GetComponents().Add(component); }
bool IAstrumObject::RemoveComponent(const std::shared_ptr<struct IAstrumComponent>& component) { return GetComponents().Remove(component); }
void IAstrumObject::ClearComponent() { GetComponents().Clear(); }