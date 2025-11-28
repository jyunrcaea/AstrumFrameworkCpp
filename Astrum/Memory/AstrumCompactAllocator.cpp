#include "AstrumCompactAllocator.hpp"

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

template <typename T>
AstrumCompactMemory AstrumCompactAllocator::Allocate()
{
	void* aligned = std::align(alignof(T), sizeof(T), poolCursor, remainSize);

	if (size > remainSize || (remainSize - size) < static_cast<size_t>(totalSize * compactionThreshold)) {
		Resize(std::max(static_cast<size_t>(totalSize * expandScale), totalSize + size));
	}
	else if (static_cast<char*>(poolCursor) + size >= static_cast<char*>(memoryPool) + totalSize) {
		Resize(totalSize);
	}

	void* result = poolCursor;
	poolCursor = static_cast<void*>(static_cast<char*>(poolCursor) + size);
	remainSize -= size;
	return *allocatedPointers.insert(AstrumCompactMemory{ result, size }).first;
}

void AstrumCompactAllocator::Free(AstrumCompactMemory& memoryBlock)
{
	auto it = allocatedPointers.find(memoryBlock);
	if (it != allocatedPointers.end()) {
		allocatedPointers.erase(it);
		remainSize += memoryBlock.GetSize();
		memoryBlock.Relocate(nullptr);
	}
	else {
		AstrumException("In AstrumCompactAllocator::Free(AstrumCompactMemory&), memoryBlock not found in allocated pointers.").Alert();
	}
}

void AstrumCompactAllocator::Resize(size_t nextSize)
{
	void* newPool = ::operator new(nextSize);
	void* newCursor = 0;

	for (auto memoryBlock : allocatedPointers) {
		memoryBlock.Relocate(newCursor);
		newCursor = static_cast<void*>(static_cast<char*>(newCursor) + memoryBlock.GetSize());
	}

	::operator delete(memoryPool);
	memoryPool = newPool;
	poolCursor = newCursor;
	totalSize = nextSize;
}