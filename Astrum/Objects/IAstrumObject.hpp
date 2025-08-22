#pragma once
#include <memory>
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Collections/IAstrumComponentList.hpp"
#include "../Components/IAstrumComponent.hpp"

namespace Astrum {
	struct IComponent;
	struct IComponentList;
	struct IGroupObject;

	struct IObject : public std::enable_shared_from_this<IObject> {
		virtual ~IObject() = default;

		virtual void Prepare() = 0;
		virtual void Update() = 0;
		virtual void Release() = 0;
		virtual void Draw() = 0;

		virtual ObservedVector3& GetPosition() = 0;
		virtual ObservedVector3& GetRotation() = 0;
		virtual ObservedVector3& GetScale() = 0;

		void SetPosition(const ObservedVector3& vec);
		void SetRotation(const ObservedVector3& vec);
		void SetScale(const ObservedVector3& vec);
		void SetPosition(const Vector3& vec);
		void SetRotation(const Vector3& vec);
		void SetScale(const Vector3& vec);

		void SetPosition(float x, float y, float z);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);

		void SetRotation(float x, float y, float z);
		void SetRotationX(float x);
		void SetRotationY(float y);
		void SetRotationZ(float z);

		void SetScale(float x, float y, float z);
		void SetScaleX(float x);
		void SetScaleY(float y);
		void SetScaleZ(float z);

		virtual const Vector3& GetAbsolutePosition() = 0;
		virtual const Vector3& GetAbsoluteRotation() = 0;
		virtual const Vector3& GetAbsoluteScale() = 0;

		virtual IGroupObject* GetParent() const = 0;
		virtual bool SetParent(IGroupObject* const parent) = 0;
		virtual bool ClearParent(IGroupObject* const parent) = 0;

		virtual IComponentList& GetComponents() = 0;

		bool AddComponent(const std::shared_ptr<struct IComponent>& component);
		bool RemoveComponent(const std::shared_ptr<struct IComponent>& component);
		void ClearComponent();

		virtual void UpdateAbsolutePosition() = 0;
		virtual void UpdateAbsoluteRotation() = 0;
		virtual void UpdateAbsoluteScale() = 0;

		virtual void SetVisible(bool enable) = 0;

		virtual bool IsPrepared() const = 0;
		virtual bool IsVisible() const = 0;
	};
}