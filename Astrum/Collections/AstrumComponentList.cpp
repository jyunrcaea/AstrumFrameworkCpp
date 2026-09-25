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
	changed = true;
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
	changed = true;
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
	changed = true;
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
	ForEach([](const std::shared_ptr<IAstrumComponent>& component) { component->Prepare(); });
}

void AstrumComponentList::Update()
{
	ForEach([](const std::shared_ptr<IAstrumComponent>& component) { component->Update(); });
}

void AstrumComponentList::Release()
{
	ForEach([](const std::shared_ptr<IAstrumComponent>& component) { component->Release(); });
}

void AstrumComponentList::ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) {
	RefreshSnapshot();

	// 바깥 순회 도중에 목록이 바뀐 상태에서 중첩 순회하는 경우, 바깥 순회 중인 스냅샷은 건드리지 않고 최신 목록의 복사본을 순회합니다.
	vec latest;
	if (changed) latest = static_cast<const vec&>(*this);
	const auto& targets = changed ? latest : snapshot;

	// 예외가 발생해도 순회 깊이가 복구되도록 합니다.
	struct IterationGuard {
		int& depth;
		explicit IterationGuard(int& target) : depth(target) { ++depth; }
		~IterationGuard() { --depth; }
	} guard(iterationDepth);

	for (const auto& component : targets) {
		// 순회 도중 이 목록에서 제거된 컴포넌트(owner가 해제됨)는 건너뜁니다.
		if (component != nullptr && component->GetOwner() == owner) {
			func(component);
		}
	}
}

void AstrumComponentList::RefreshSnapshot() {
	// 순회 도중에는 스냅샷을 바꾸면 순회 중인 배열이 무효화되므로 갱신하지 않습니다.
	if (changed && 0 == iterationDepth) {
		snapshot = static_cast<const vec&>(*this);
		changed = false;
	}
}

std::vector<std::shared_ptr<IAstrumComponent>> AstrumComponentList::ToArray() const {
	return vec(*this);
}