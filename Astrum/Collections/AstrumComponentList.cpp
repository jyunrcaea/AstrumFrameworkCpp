#include "AstrumComponentList.hpp"

AstrumComponentList::AstrumComponentList(IAstrumObject* ownerObject) : owner(ownerObject) {}

AstrumComponentList::~AstrumComponentList()
{
	for (auto& component : *this) {
		if (nullptr != component) {
			component->SetOwner(nullptr); // Clear owner reference
		}
	}
}

bool AstrumComponentList::Add(const std::shared_ptr<IAstrumComponent>& component)
{
	if (nullptr == component) return false; //nullptr인 컴포넌트를 줬다면
	if (owner == component->GetOwner()) return false; // 이미 owner가 설정되어 있고, owner가 같다면 추가하지 않음
	if (nullptr != component->GetOwner()) {
		AstrumException("Component already has an owner.").Alert();
	}

	this->push_back(component);
	component->SetOwner(owner);
	if (owner->IsPrepared()) component->Prepare();
	return true;
}

bool AstrumComponentList::Remove(const std::shared_ptr<IAstrumComponent>& component)
{
	if (nullptr == component) return false;

	auto it = std::find(this->begin(), this->end(), component);
	if (it == this->end()) return false;

	this->erase(it);
	// Add()에서 owner가 준비된 상태면 Prepare()를 호출하므로, 제거할 때도 대칭적으로 Release()를 호출합니다.
	if (owner->IsPrepared()) component->Release();
	component->SetOwner(nullptr);
	return true;
}

void AstrumComponentList::Clear()
{
	// Release() 도중에 목록이 바뀌어도 안전하도록 먼저 비운 뒤 처리합니다.
	vec removed;
	removed.swap(static_cast<vec&>(*this));
	const bool prepared = owner->IsPrepared();
	for (auto& component : removed) {
		if (component != nullptr) {
			if (prepared) component->Release();
			component->SetOwner(nullptr); // Clear owner reference
		}
	}
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

void AstrumComponentList::ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) {
	for (auto& component : *this) {
		if (component != nullptr) {
			func(component);
		}
	}
}

std::vector<std::shared_ptr<IAstrumComponent>> AstrumComponentList::ToArray() const {
	return vec(*this);
}