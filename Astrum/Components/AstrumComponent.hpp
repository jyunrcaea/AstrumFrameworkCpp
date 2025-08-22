#pragma once
#include "IAstrumComponent.hpp"

namespace Astrum {
	class Component : public IComponent
	{
	public:
		virtual ~Component() = default;
		virtual void Prepare() override;
		virtual void Update() override;
		virtual void Release() override;
		virtual void Draw() override;

		virtual void SetOwner(IObject* owner);
		virtual IObject* GetOwner() const;

	private:
		IObject* owner = nullptr;
	};
}