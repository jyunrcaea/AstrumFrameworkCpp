#include "AstrumCompactMemory.hpp"

#include "AstrumCompactAllocator.hpp"

AstrumCompactMemory::AstrumCompactMemory(void* offset, size_t alignedSize, size_t align, RelocatorFunction relocator)
	: pointer(offset), alignedSize(alignedSize), alignment(align), relocator(relocator)
{
	if (nullptr == offset) {
		AstrumException("In AstrumCompactMemory(void*, size_t), offset can't be nullptr.").Alert();
	}
	if (align == 0) {
		AstrumException("In AstrumCompactMemory(void*, size_t), alignment must be greater than 0.").Alert();
	}
	if ((align & (align - 1)) != 0) {
		AstrumException("In AstrumCompactMemory(void*, size_t), alignment must be a power of 2.").Alert();
	}
}

void AstrumCompactMemory::Relocate(void* const destination)
{
	if (pointer == destination)	return;
	if (destination != nullptr) {
		relocator(pointer, destination);
	}
	pointer = destination;
}