#include "AstrumComponentList.hpp"

AstrumComponentList::AstrumComponentList(IAstrumObject* ownerObject) : owner(ownerObject) {}

AstrumComponentList::~AstrumComponentList()
{
	for (auto& component : *this) {
		if (component != nullptr) {
			component->SetOwner(nullptr); // Clear owner reference
		}
	}
}

bool AstrumComponentList::Add(std::shared_ptr<IAstrumComponent> const component)
{
	if (component == nullptr) return false;
	if (component->GetOwner() != nullptr) {
		throw AstrumException("Component already has an owner.");
	}
	if (component->GetOwner() == owner) return false;

	this->push_back(component);
	component->SetOwner(owner);
	return true;
}

bool AstrumComponentList::Remove(std::shared_ptr<IAstrumComponent> const component)
{
	if (component == nullptr) return false;

	auto it = std::find(this->begin(), this->end(), component);
	if (it == this->end()) return false;

	this->erase(it);
	component->SetOwner(nullptr);
	return true;
}

void AstrumComponentList::Clear()
{
	for (auto& component : *this) {
		if (component != nullptr) {
			component->SetOwner(nullptr); // Clear owner reference
		}
	}
	this->clear();
}

void AstrumComponentList::Prepare()
{
	for (auto& component : *this) {
		component->Prepare();
	}
}

void AstrumComponentList::Update()
{
	for (auto& component : *this) {
		component->Update();
	}
}

void AstrumComponentList::Release()
{
	for (auto& component : *this) {
		component->Release();
	}
}

std::vector<std::shared_ptr<IAstrumComponent>>& AstrumComponentList::GetVector()
{
	return *this;
}
