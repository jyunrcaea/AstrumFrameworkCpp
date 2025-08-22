#pragma once
#include "AstrumObject.hpp"
#include "../Collections/AstrumObjectList.hpp"
#include "IAstrumGroupObject.hpp"
#include <memory>

namespace Astrum
{
	class GroupObject : public virtual Object, public virtual IGroupObject {
	public:
		virtual bool ClearParent(IGroupObject* const p) override { return Object::ClearParent(p); }
		virtual const Vector3& GetAbsolutePosition() override { return Object::GetAbsolutePosition(); }
		virtual const Vector3& GetAbsoluteRotation() override { return Object::GetAbsoluteRotation(); }
		virtual const Vector3& GetAbsoluteScale() override { return Object::GetAbsoluteScale(); }
		virtual IComponentList& GetComponents() override { return Object::GetComponents(); }
		virtual IGroupObject* GetParent() const override { return Object::GetParent(); }
		virtual ObservedVector3& GetPosition() override { return Object::GetPosition(); }
		virtual ObservedVector3& GetRotation() override { return Object::GetRotation(); }
		virtual ObservedVector3& GetScale() override { return Object::GetScale(); }
		virtual void SetVisible(bool enable) override { Object::SetVisible(enable); }
		virtual bool IsVisible() const override { return Object::IsVisible(); }
		virtual bool IsPrepared() const override { return Object::IsPrepared(); }
		virtual bool SetParent(IGroupObject* const p) override { return Object::SetParent(p); }

	public:
		GroupObject();

		virtual void Prepare() override;
		virtual void Update() override;
		virtual void Release() override;
		virtual void Draw() override;

		virtual IObjectList& GetObjectList() override;

		virtual void UpdateAbsolutePosition() override;
		virtual void UpdateAbsoluteRotation() override;
		virtual void UpdateAbsoluteScale() override;

	private:
		ObjectList objects;
	};
}