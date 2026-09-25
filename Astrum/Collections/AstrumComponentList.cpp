#include "AstrumComponentList.hpp"

AstrumComponentList::AstrumComponentList(IAstrumObject* ownerObject) : owner(ownerObject) {}

AstrumComponentList::~AstrumComponentList()
{
	for (auto& component : components.TakeAll()) {
		component->SetOwner(nullptr); // Clear owner reference
	}
}

bool AstrumComponentList::Add(const std::shared_ptr<IAstrumComponent>& component)
{
	if (nullptr == component) return false; //nullptr인 컴포넌트를 줬다면
	if (owner == component->GetOwner()) return false; // 이미 owner가 설정되어 있고, owner가 같다면 추가하지 않음
	if (nullptr != component->GetOwner()) {
		AstrumException("Component already has an owner.").Alert();
	}

	components.PushBack(component);
	component->SetOwner(owner);
	if (owner->IsPrepared()) component->Prepare();
	return true;
}

bool AstrumComponentList::Remove(const std::shared_ptr<IAstrumComponent>& component)
{
	if (nullptr == component) return false;
	// 인자가 목록 안의 shared_ptr를 가리키는 참조일 수도 있으므로 복사해 둡니다.
	const std::shared_ptr<IAstrumComponent> target = component;
	if (false == components.Erase(target.get())) return false;

	// Add()에서 owner가 준비된 상태면 Prepare()를 호출하므로, 제거할 때도 대칭적으로 Release()를 호출합니다.
	if (owner->IsPrepared()) target->Release();
	target->SetOwner(nullptr);
	return true;
}

void AstrumComponentList::Clear()
{
	// 목록을 먼저 비운 뒤 처리하므로, Release() 도중에 목록이 바뀌어도 안전합니다.
	const bool prepared = owner->IsPrepared();
	for (auto& component : components.TakeAll()) {
		if (prepared) component->Release();
		component->SetOwner(nullptr); // Clear owner reference
	}
}

void AstrumComponentList::Prepare()
{
	for (IAstrumComponent* component : components.Iterate()) component->Prepare();
}

void AstrumComponentList::Update()
{
	for (IAstrumComponent* component : components.Iterate()) component->Update();
}

void AstrumComponentList::Release()
{
	for (IAstrumComponent* component : components.Iterate()) component->Release();
}

void AstrumComponentList::ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) {
	components.ForEachShared(func);
}

std::vector<std::shared_ptr<IAstrumComponent>> AstrumComponentList::ToArray() const {
	return components.ToVector();
}
