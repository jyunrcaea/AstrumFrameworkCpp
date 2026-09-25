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

    DI.Resolve(this);

    // 컴포넌트의 Prepare() 도중에 추가되는 컴포넌트도 즉시 준비되도록, 먼저 준비 상태로 표시합니다.
    isPrepared = true;

    // 컴포넌트가 순회 도중에 자신(또는 다른 컴포넌트)을 추가/제거해도 안전하도록 ForEach로 순회합니다.
    Components.Prepare();
}
void AstrumObject::Update() {
    Components.Update();
}
void AstrumObject::Release() {
    // 컴포넌트의 Release() 도중에 제거되는 컴포넌트도 즉시 해제되도록, 준비 상태 해제는 마지막에 합니다.
    Components.Release();

    isPrepared = false;
}
void AstrumObject::Draw() {
	if (false == IsVisible()) return;
    Components.ForEach([](const std::shared_ptr<IAstrumComponent>& component) { component->Draw(); });
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
	//absoluteRotation = parent->GetAbsoluteRotation() + this->Rotation;
    absoluteRotation = (AstrumQuaternion::FromEuler(parent->GetAbsoluteRotation()) * AstrumQuaternion::FromEuler(this->Rotation)).ToEuler();
}

void AstrumObject::UpdateAbsoluteScale()
{
    if (nullptr == parent) {
		absoluteScale = Scale;
        return;
    }
    absoluteScale = parent->GetAbsoluteScale() * this->Scale;
}