#pragma once
#include <memory>
#include "IAstrumComponentList.hpp"
#include "../AstrumException.hpp"

struct IAstrumComponent;
struct IAstrumObject;

class AstrumComponentList : public IAstrumComponentList, private std::vector<std::shared_ptr<IAstrumComponent>>
{
	using vec = std::vector<std::shared_ptr<IAstrumComponent>>;
	using iter = vec::iterator;
public:
	AstrumComponentList(IAstrumObject* ownerObject);
	~AstrumComponentList();
	virtual bool Add(const std::shared_ptr<IAstrumComponent>& component) override;
	virtual bool Remove(const std::shared_ptr<IAstrumComponent>& component) override;
	virtual void Clear() override;

	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) override;

	virtual std::vector<std::shared_ptr<IAstrumComponent>> ToArray() const override;
	iter begin() { return vec::begin(); }
	iter end() { return vec::end(); }
	auto rbegin() { return vec::rbegin(); }
	auto rend() { return vec::rend(); }
private:
	IAstrumObject* const owner;
};