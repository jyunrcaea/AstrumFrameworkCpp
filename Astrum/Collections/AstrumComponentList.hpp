#pragma once
#include <memory>
#include "IAstrumComponentList.hpp"
#include "../AstrumException.hpp"

namespace Astrum {
	struct IComponent;
	struct IObject;

	class ComponentList : public IComponentList, private std::vector<std::shared_ptr<IComponent>>
	{
		using vec = std::vector<std::shared_ptr<IComponent>>;
		using iter = vec::iterator;
	public:
		ComponentList(IObject* ownerObject);
		~ComponentList();
		virtual bool Add(const std::shared_ptr<IComponent>& component) override;
		virtual bool Remove(const std::shared_ptr<IComponent>& component) override;
		virtual void Clear() override;

		virtual void Prepare() override;
		virtual void Update() override;
		virtual void Release() override;

		virtual void ForEach(const std::function<void(const std::shared_ptr<IComponent>&)>& func) override;

		virtual std::vector<std::shared_ptr<IComponent>> ToArray() const override;
		iter begin() { return vec::begin(); }
		iter end() { return vec::end(); }
		auto rbegin() { return vec::rbegin(); }
		auto rend() { return vec::rend(); }
	private:
		IObject* const owner;
	};
}