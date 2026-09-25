#include "AstrumCompactAllocator.hpp"

void AstrumCompactAllocator::Initialize(size_t initialSize)
{
	if (memoryPool != nullptr) {
		AstrumException("In AstrumCompactAllocator::Initialize(size_t), memory pool is already initialized.").Alert();
		return;
	}
	if (initialSize == 0) {
		AstrumException("In AstrumCompactAllocator::Initialize(size_t), initialSize must be greater than 0.").Alert();
		return;
	}
	memoryPool = ::operator new(initialSize, std::align_val_t{ poolAlignment });
	poolCursor = memoryPool;
	totalSize = initialSize;
	remainSize = initialSize;
}

void AstrumCompactAllocator::Resize(size_t nextSize)
{
	// 살아있는 블록만 모읍니다. (만료된 포인터는 여기서 정리)
	std::vector<std::shared_ptr<AstrumCompactMemory>> blocks;
	blocks.reserve(allocatedPointers.size());
	for (const auto& weak : allocatedPointers) {
		if (auto block = weak.lock()) blocks.push_back(std::move(block));
	}

	// 메모리 정렬이 큰 순서(같으면 크기가 큰 순서)대로 배치하면, 각 블록의 크기가 자신의 정렬의 배수이므로
	// 첫 블록만 풀의 시작 주소에 맞추면 나머지는 추가적인 패딩이 필요없습니다. (strict weak ordering을 만족하는 비교)
	std::stable_sort(blocks.begin(), blocks.end(),
		[](const std::shared_ptr<AstrumCompactMemory>& a, const std::shared_ptr<AstrumCompactMemory>& b) {
			if (a->GetAlignment() != b->GetAlignment()) return a->GetAlignment() > b->GetAlignment();
			return a->GetAlignedSize() > b->GetAlignedSize();
		}
	);

	size_t usedSize = 0;
	for (const auto& block : blocks) usedSize += block->GetAlignedSize();
	nextSize = (std::max)(nextSize, usedSize);

	// 새 풀의 시작 주소는 가장 큰 정렬에 맞춰 할당합니다.
	const size_t nextAlignment = (std::max)(alignof(std::max_align_t), blocks.empty() ? size_t{ 0 } : blocks.front()->GetAlignment());
	void* const newPool = ::operator new(nextSize, std::align_val_t{ nextAlignment });
	char* newCursor = static_cast<char*>(newPool);

	for (const auto& block : blocks) {
		block->Relocate(newCursor);
		newCursor += block->GetAlignedSize();
	}

	if (nullptr != memoryPool) ::operator delete(memoryPool, std::align_val_t{ poolAlignment });
	memoryPool = newPool;
	poolAlignment = nextAlignment;
	poolCursor = newCursor;
	totalSize = nextSize;
	remainSize = totalSize - usedSize;

	allocatedPointers.assign(blocks.begin(), blocks.end());
}
