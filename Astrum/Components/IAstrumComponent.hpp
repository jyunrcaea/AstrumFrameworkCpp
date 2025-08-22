#pragma once

namespace Astrum {
	struct IObject;

	struct IComponent
	{
		virtual ~IComponent() = default;

		virtual void Prepare() = 0;
		virtual void Update() = 0;
		virtual void Release() = 0;
		// 컴포넌트가 소속된 객체의 IsVisible()가 true일 때만 호출됩니다.
		virtual void Draw() = 0;

		virtual void SetOwner(IObject* owner) = 0;
		virtual IObject* GetOwner() const = 0;
	};
}