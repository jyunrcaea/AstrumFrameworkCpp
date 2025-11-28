#pragma once
#include <cstring>
#include "../AstrumException.hpp"

/// <summary>
/// AstrumCompactAllocator에서 할당된 메모리 블록을 가리키는 구조체입니다. 포인터는 언제든지 변할 수 있습니다.
/// </summary>
struct AstrumCompactMemory {
	friend class AstrumCompactAllocator;

public:
	/// <summary>
	/// 저장된 포인터를 반환합니다. 시작 주소입니다.
	/// </summary>
	/// <returns>저장된 void* 포인터</returns>
	void* Get() const { return pointer; }
	/// <summary>
	/// 저장된 포인터를 반환합니다. 시작 주소입니다.
	/// </summary>
	/// <returns>저장된 void* 포인터</returns>
	void* operator*() const { return pointer; }

	/// <summary>
	/// 저장된 크기를 반환합니다. 정렬이 적용된 크기입니다. (풀에서 정렬을 맞추기 위해 사용한 크기는 이보다 클수 있지만, 한번 이상 압축 이후에는 이 크기에 맞게 됩니다.)
	/// </summary>
	/// <returns>크기 값</returns>
	size_t GetAlignedSize() const { return alignedSize; }
	/// <summary>
	/// 정렬 크기를 가져옵니다.
	/// </summary>
	/// <returns>정렬 값</returns>
	size_t GetAlignment() const { return alignment; }

	/// <summary>
	/// 정렬이 낮은 순서대로 비교합니다. 같은 정렬일 경우 크기로 비교합니다. 포인터 값이 nullptr인 경우 항상 작다고 간주합니다.
	/// </summary>
	/// <param name="other">비교할 대상</param>
	bool operator<(const AstrumCompactMemory& other) const {
		if (nullptr == pointer) return pointer < other.pointer;
		else if (other.pointer == nullptr) return false; // this는 유효한 포인터

		if (alignment == other.alignment) {
			return alignedSize < other.alignedSize;
		}

		return alignment < other.alignment;
	}
	/// <summary>
	/// 정렬이 큰 순서대로 비교합니다. 같은 정렬일 경우 크기로 비교합니다.
	/// </summary>
	/// <param name="other">비교할 대상</param>
	bool operator>(const AstrumCompactMemory& other) const {
		if (nullptr == pointer) return pointer > other.pointer;
		else if (other.pointer == nullptr) return true; // this는 유효한 포인터

		if (alignment == other.alignment) {
			return alignedSize > other.alignedSize;
		}

		return alignment > other.alignment;
	}

	/// <summary>
	/// 포인터 간 비교를 수행합니다.
	/// </summary>
	/// <param name="other">비교할 대상</param>
	bool operator==(const AstrumCompactMemory& other) const {
		return pointer == other.pointer;
	}

	using RelocatorFunction = void(*)(void* source, void* destination);
private:

	void* pointer = nullptr;
	const size_t alignedSize = 0;
	const size_t alignment = alignof(std::max_align_t);
	RelocatorFunction relocator = nullptr;

	/// <summary>
	/// 지정된 주소에서 시작하는 메모리 영역 블록을 정의합니다.
	/// </summary>
	/// <param name="offset">시작 포인터</param>
	/// <param name="size">크기(바이트)</param>
	/// <param name="align">정렬(바이트)</param>
	AstrumCompactMemory(void* offset, size_t size, size_t align, RelocatorFunction relocator);

	/// <summary>
	/// 객체의 데이터를 지정된 메모리 위치로 이동합니다.
	/// </summary>
	/// <param name="destination">객체 데이터가 이동될 대상 메모리 포인터. 유효한 크기의 메모리를 가리켜야 합니다</param>
	void Relocate(void* const destination);
};