#pragma once
#include <memory>
#include "IAstrumComponent.hpp"
#include "AstrumException.hpp"

class AstrumComponentList : private std::vector<std::shared_ptr<IAstrumComponent>>, public IAstrumPrepareEvent, public  IAstrumUpdateEvent, public  IAstrumReleaseEvent
{
	using vec = std::vector<std::shared_ptr<IAstrumComponent>>;
	using iter = vec::iterator;
public:
	AstrumComponentList(IAstrumObject* ownerObject);
	virtual ~AstrumComponentList();
	bool Add(std::shared_ptr<IAstrumComponent> const component);
	bool Remove(std::shared_ptr<IAstrumComponent> const component);
	void Clear();

	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;

	void ForEach(const std::function<void(std::shared_ptr<IAstrumComponent> const)>& func) {
		for (auto& component : *this) {
			if (component != nullptr) {
				func(component);
			}
		}
	}

	std::vector<std::shared_ptr<IAstrumComponent>>& GetVector();
	iter begin() { return vec::begin(); }
	iter end() { return vec::end(); }
	auto rbegin() { return vec::rbegin(); }
	auto rend() { return vec::rend(); }
private:
	IAstrumObject* const owner;
};