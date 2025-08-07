#include "IAstrumObject.hpp"

void IAstrumObject::SetPosition(const AstrumObservedVector3& vec) { GetPosition().Reset(vec); }
void IAstrumObject::SetRotation(const AstrumObservedVector3& vec) { GetRotation().Reset(vec); }
void IAstrumObject::SetScale(const AstrumObservedVector3& vec) { GetScale().Reset(vec); }
void IAstrumObject::SetPosition(const AstrumVector3& vec) { GetPosition().Reset(vec); }
void IAstrumObject::SetRotation(const AstrumVector3& vec) { GetRotation().Reset(vec); }
void IAstrumObject::SetScale(const AstrumVector3& vec) { GetScale().Reset(vec); }

void IAstrumObject::SetPosition(float x, float y, float z) { GetPosition().Reset(x, y, z); }
void IAstrumObject::SetRotation(float x, float y, float z) { GetRotation().Reset(x, y, z); }
void IAstrumObject::SetScale(float x, float y, float z) { GetScale().Reset(x, y, z); }

bool IAstrumObject::AddComponent(std::shared_ptr<IAstrumComponent> const component) { return GetComponents().Add(component); }
bool IAstrumObject::RemoveComponent(std::shared_ptr<IAstrumComponent> const component) { return GetComponents().Remove(component); }
void IAstrumObject::ClearComponent() { GetComponents().Clear(); }