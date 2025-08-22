#include "AstrumObject.hpp"

namespace Astrum
{
	Object::Object()
		: Position(0, 0, 0, std::bind(&Object::UpdateAbsolutePosition, this)),
		Rotation(std::bind(&Object::UpdateAbsoluteRotation, this)),
		Scale(1, 1, 1, std::bind(&Object::UpdateAbsoluteScale, this)),
		absoluteScale(1, 1, 1), Components(this) { }

	void Object::Prepare() {
		UpdateAbsoluteScale();
		UpdateAbsoluteRotation();
		UpdateAbsolutePosition();

		for (auto& component : Components) {
			if (component) component->Prepare();
		}

		isPrepared = true;
	}
	void Object::Update() {
		for (auto& component : Components) {
			if (component) component->Update();
		}
	}
	void Object::Release() {
		for (auto& component : Components) {
			if (component) component->Release();
		}

		isPrepared = false;
	}
	void Object::Draw() {
		if (false == IsVisible()) return;
		for (auto& component : Components) {
			if (component) component->Draw();
		}
	}

	ObservedVector3& Object::GetPosition() { return Position; }
	ObservedVector3& Object::GetRotation() { return Rotation; }
	ObservedVector3& Object::GetScale() { return Scale; }

	const Vector3& Object::GetAbsolutePosition() { return absolutePosition; }
	const Vector3& Object::GetAbsoluteRotation() { return absoluteRotation; }
	const Vector3& Object::GetAbsoluteScale() { return absoluteScale; }

	void Object::SetAbsolutePosition(const Vector3& vec) { absolutePosition = vec; }
	void Object::SetAbsoluteRotation(const Vector3& vec) { absoluteRotation = vec; }
	void Object::SetAbsoluteScale(const Vector3& vec) { absoluteScale = vec; }

	void Object::SetVisible(bool enable) { visible = enable; }

	bool Object::IsVisible() const { return visible; }
	bool Object::IsPrepared() const { return this->isPrepared; }

	IGroupObject* Object::GetParent() const { return parent; }

	bool Object::SetParent(IGroupObject* const p) {
		if (nullptr != parent) return false;
		parent = p;
		return true;
	}

	bool Object::ClearParent(IGroupObject* const p) {
		if (parent != p) return false;
		parent = nullptr;
		return true;
	}

	IComponentList& Object::GetComponents() { return Components; }

	void Object::UpdateAbsolutePosition()
	{
		if (nullptr == parent) {
			absolutePosition = Position;
			return;
		}
		// 1. 부모 회전 사원수
		Quaternion parentRotation = Quaternion::FromEuler(parent->GetAbsoluteRotation());
		// 2. 자식 좌표 * 부모 절대크기 * 회전
		Vector3 localed = parentRotation.Rotate(this->Position * parent->GetAbsoluteScale());
		// 3. 부모 절대좌표 + 자식 좌표
		absolutePosition = parent->GetAbsolutePosition() + localed;
	}

	void Object::UpdateAbsoluteRotation()
	{
		if (nullptr == parent) {
			absoluteRotation = Rotation;
			return;
		}
		absoluteRotation = parent->GetAbsoluteRotation() + this->Rotation;
	}

	void Object::UpdateAbsoluteScale()
	{
		if (nullptr == parent) {
			absoluteScale = Scale;
			return;
		}
		absoluteScale = parent->GetAbsoluteScale() * this->Scale;
	}
}