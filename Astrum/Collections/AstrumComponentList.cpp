#include "AstrumComponentList.hpp"

namespace Astrum {
	ComponentList::ComponentList(IObject* ownerObject) : owner(ownerObject) {}

	ComponentList::~ComponentList()
	{
		for (auto& component : *this) {
			if (nullptr != component) {
				component->SetOwner(nullptr); // Clear owner reference
			}
		}
	}

	bool ComponentList::Add(const std::shared_ptr<IComponent>& component)
	{
		if (nullptr == component) return false; //nullptr인 컴포넌트를 줬다면
		if (owner == component->GetOwner()) return false; // 이미 owner가 설정되어 있고, owner가 같다면 추가하지 않음
		if (nullptr != component->GetOwner()) {
			throw Exception("Component already has an owner.");
		}

		this->push_back(component);
		component->SetOwner(owner);
		if (owner->IsPrepared()) component->Prepare();
		return true;
	}

	bool ComponentList::Remove(const std::shared_ptr<IComponent>& component)
	{
		if (nullptr == component) return false;

		auto it = std::find(this->begin(), this->end(), component);
		if (it == this->end()) return false;

		this->erase(it);
		component->SetOwner(nullptr);
		return true;
	}

	void ComponentList::Clear()
	{
		for (auto& component : *this) {
			if (component != nullptr) {
				component->SetOwner(nullptr); // Clear owner reference
			}
		}
		this->clear();
	}

	void ComponentList::Prepare()
	{
		for (auto& component : *this) {
			component->Prepare();
		}
	}

	void ComponentList::Update()
	{
		for (auto& component : *this) {
			component->Update();
		}
	}

	void ComponentList::Release()
	{
		for (auto& component : *this) {
			component->Release();
		}
	}

	void ComponentList::ForEach(const std::function<void(const std::shared_ptr<IComponent>&)>& func) {
		for (auto& component : *this) {
			if (component != nullptr) {
				func(component);
			}
		}
	}

	std::vector<std::shared_ptr<IComponent>> ComponentList::ToArray() const {
		return vec(*this);
	}
}