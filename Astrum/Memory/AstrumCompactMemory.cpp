#include "AstrumCompactMemory.hpp"

#include "AstrumCompactAllocator.hpp"

AstrumCompactMemory::AstrumCompactMemory(void* offset, size_t size, size_t align)
	: pointer(offset), size(size), alignment(align) {
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
		std::memmove(destination, pointer, size);
	}
	pointer = destination;
}