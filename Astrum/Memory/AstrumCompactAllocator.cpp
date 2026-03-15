#include "AstrumCompactAllocator.hpp"

struct AstrumCompactMemoryPtrCompare {
	bool operator()(const std::shared_ptr<AstrumCompactMemory>& lhs, const std::shared_ptr<AstrumCompactMemory>& rhs) const {
		return lhs < rhs;
	}
};

void AstrumCompactAllocator::Initialize(size_t initialSize)
{
	if (memoryPool != nullptr) {
		AstrumException("In AstrumCompactAllocator::Initialize(size_t), memory pool is already initialized.").Alert();
	}
	if (initialSize == 0) {
		AstrumException("In AstrumCompactAllocator::Initialize(size_t), initialSize must be greater than 0.").Alert();
	}
	memoryPool = ::operator new(initialSize);
	poolCursor = memoryPool;
	totalSize = initialSize;
	remainSize = initialSize;
}

void AstrumCompactAllocator::Resize(size_t nextSize)
{
	void* newPool = ::operator new(nextSize);
	void* newCursor = newPool;

	// 메모리 정렬이 큰 순서대로 정렬하는 이유로는 Resize시 순서대로 재배치하면 추가적인 패딩이 필요없음.
	std::sort(allocatedPointers.begin(), allocatedPointers.end(),
		[](std::weak_ptr<AstrumCompactMemory> a, std::weak_ptr<AstrumCompactMemory> b) {
			if (a.expired()) return b.expired(); // expired인 경우 항상 뒤로
			else if (b.expired()) return false; // b가 expired인 경우 항상 뒤로
			return (*a.lock().get()) > (*b.lock().get()); // 패딩 우선, 이후 크기 내림차순
		}
	);
	// 만료된 포인터 제거
	for (long long i = static_cast<long long>(allocatedPointers.size()) - 1; i >= 0 && allocatedPointers[i].expired(); i--) {
		allocatedPointers.pop_back();
	}

	auto it = allocatedPointers.begin();
	// 첫 포인터는 정렬 안맞을수도 있음.
	if (it != allocatedPointers.end()) {
		if (size_t temp = std::numeric_limits<size_t>::max()
			; auto ptr = it->lock()) {
			std::align(ptr->GetAlignment(), ptr->GetAlignedSize(), newCursor, temp);
			ptr->Relocate(newCursor);
			newCursor = static_cast<void*>(static_cast<char*>(newCursor) + ptr->GetAlignedSize());
			++it;
		}
		else {
			it = allocatedPointers.erase(it);
		}
	}

	// 두번째부턴 이미 alignment로 정렬했으니 패딩 없이 순차 복사.
	while (it != allocatedPointers.end()) {
		if (auto ptr = it->lock()) {
			ptr->Relocate(newCursor);
			newCursor = static_cast<void*>(static_cast<char*>(newCursor) + ptr->GetAlignedSize());
			++it;
		}
		else {
			it = allocatedPointers.erase(it);
		}
	}

	::operator delete(memoryPool);
	memoryPool = newPool;
	poolCursor = newCursor;
	totalSize = nextSize;
	remainSize = totalSize - (static_cast<char*>(newCursor) - static_cast<char*>(newPool));
}