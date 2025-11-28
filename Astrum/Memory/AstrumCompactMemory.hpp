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
	/// 저장된 크기를 반환합니다.
	/// </summary>
	/// <returns>크기 값</returns>
	size_t GetSize() const { return size; }

	bool operator<(const AstrumCompactMemory& other) const {
		return pointer < other.pointer;
	}

	bool operator==(const AstrumCompactMemory& other) const {
		return pointer == other.pointer;
	}

private:
	void* pointer = nullptr;
	const size_t size = 0;
	const size_t alignment = alignof(std::max_align_t);

	/// <summary>
	/// 지정된 주소에서 시작하는 메모리 영역 블록을 정의합니다.
	/// </summary>
	/// <param name="offset">시작 포인터</param>
	/// <param name="size">크기(바이트)</param>
	/// <param name="align">정렬(바이트)</param>
	AstrumCompactMemory(void* offset, size_t size, size_t align);

	/// <summary>
	/// 객체의 데이터를 지정된 메모리 위치로 이동합니다.
	/// </summary>
	/// <param name="destination">객체 데이터가 이동될 대상 메모리 포인터. 유효한 크기의 메모리를 가리켜야 합니다</param>
	void Relocate(void* const destination);
};