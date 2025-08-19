#include "AstrumObject.hpp"

AstrumObject::AstrumObject()
    : Position(0,0,0,std::bind(&AstrumObject::UpdateAbsolutePosition, this)),
    Rotation(std::bind(&AstrumObject::UpdateAbsoluteRotation, this)),
    Scale(1,1,1,std::bind(&AstrumObject::UpdateAbsoluteScale, this)),
    absoluteScale(1,1,1), Components(this) { }

void AstrumObject::Prepare() {
    UpdateAbsoluteScale();
	UpdateAbsoluteRotation();
    UpdateAbsolutePosition();

    for (auto& component : Components) {
        if (component) component->Prepare();
    }

    isPrepared = true;
}
void AstrumObject::Update() {
    for(auto& component : Components) {
        if (component) component->Update();
	}
}
void AstrumObject::Release() {
    for(auto& component : Components) {
        if (component) component->Release();
	}

    isPrepared = false;
}
void AstrumObject::Draw() {
	if (false == IsVisible()) return;
    for (auto& component : Components) {
        if (component) component->Draw();
    }
}

AstrumObservedVector3& AstrumObject::GetPosition() { return Position; }
AstrumObservedVector3& AstrumObject::GetRotation() { return Rotation; }
AstrumObservedVector3& AstrumObject::GetScale() { return Scale; }

const AstrumVector3& AstrumObject::GetAbsolutePosition() { return absolutePosition; }
const AstrumVector3& AstrumObject::GetAbsoluteRotation() { return absoluteRotation; }
const AstrumVector3& AstrumObject::GetAbsoluteScale() { return absoluteScale; }

void AstrumObject::SetAbsolutePosition(const AstrumVector3& vec) { absolutePosition = vec; }
void AstrumObject::SetAbsoluteRotation(const AstrumVector3& vec) { absoluteRotation = vec; }
void AstrumObject::SetAbsoluteScale(const AstrumVector3& vec) { absoluteScale = vec; }

void AstrumObject::SetVisible(bool enable) { visible = enable; }

bool AstrumObject::IsVisible() const { return visible; }
bool AstrumObject::IsPrepared() const { return this->isPrepared; }

IAstrumGroupObject* AstrumObject::GetParent() const { return parent; }

bool AstrumObject::SetParent(IAstrumGroupObject* const p) {
    if (nullptr != parent) return false;
    parent = p;
    return true;
}

bool AstrumObject::ClearParent(IAstrumGroupObject* const p) {
    if (parent != p) return false;
    parent = nullptr;
    return true;
}

IAstrumComponentList& AstrumObject::GetComponents() { return Components; }

void AstrumObject::UpdateAbsolutePosition()
{
    if (nullptr == parent) {
        absolutePosition = Position;
        return;
	}
    // 1. 부모 회전 사원수
	AstrumQuaternion parentRotation = AstrumQuaternion::FromEuler(parent->GetAbsoluteRotation());
    // 2. 자식 좌표 * 부모 절대크기 * 회전
	AstrumVector3 localed = parentRotation.Rotate(this->Position * parent->GetAbsoluteScale());
	// 3. 부모 절대좌표 + 자식 좌표
	absolutePosition = parent->GetAbsolutePosition() + localed;
}

void AstrumObject::UpdateAbsoluteRotation()
{
    if (nullptr == parent) {
        absoluteRotation = Rotation;
		return;
    }
	absoluteRotation = parent->GetAbsoluteRotation() + this->Rotation;
}

void AstrumObject::UpdateAbsoluteScale()
{
    if (nullptr == parent) {
		absoluteScale = Scale;
        return;
    }
    absoluteScale = parent->GetAbsoluteScale() * this->Scale;
}