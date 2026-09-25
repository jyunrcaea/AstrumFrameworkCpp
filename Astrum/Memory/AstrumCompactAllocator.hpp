#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <new>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include "AstrumCompactMemory.hpp"
#include "../AstrumException.hpp"

/// <summary>
/// 타입 T의 객체를 AstrumCompactAllocator가 다른 주소로 옮겨도(재배치) 안전한지 나타냅니다.
/// 기본값은 std::is_trivially_copyable_v&lt;T&gt; 입니다. (바이트 복사만으로 옮겨도 의미가 유지되는 타입)
/// 자기 자신의 주소(this)를 어딘가에 저장하지 않는 타입(예: this를 바인딩한 콜백이 없는 타입)이라면,
/// 이 템플릿을 true로 특수화하여 이동 생성자를 이용한 재배치를 허용할 수 있습니다.
/// (주의: 이동 생성자는 예외를 던지지 않아야 하며, 이동 생성자 안에서 AstrumCompactAllocator로 할당하면 안 됩니다.)
/// </summary>
template<typename T>
struct AstrumCompactRelocatable : std::bool_constant<std::is_trivially_copyable_v<T>> {};

template<typename T>
concept AstrumCompactable = std::is_destructible_v<T>
	&& std::is_nothrow_move_constructible_v<T>
	&& AstrumCompactRelocatable<T>::value;

template <typename ValueType>
requires AstrumCompactable<ValueType>
struct AstrumReplaceablePointer;

/// <summary>
/// 메모리 압축(compaction)을 지원하는 정적 할당자입니다. (주의: 멀티스레드를 고려하지 않았습니다.)(단일 스레드 전용)
/// 압축 시 객체는 다른 주소로 옮겨지므로, 재배치해도 안전한 타입(AstrumCompactRelocatable 참고)만 할당할 수 있습니다.
/// </summary>
class AstrumCompactAllocator {
	AstrumCompactAllocator() = delete;

	// 단순 복사로 이루어지는 재배치 (trivially copyable 타입)
	template<typename T>
	static void TrivialRelocate(void* source, void* destination) {
		std::memmove(destination, source, sizeof(T));
	}

	// 이동 생성자를 이용하는 재배치
	template<typename T>
	static void MoveRelocate(void* source, void* destination) {
		// 이동 생성
		std::construct_at(static_cast<T*>(destination), std::move(*static_cast<T*>(source)));
		// 힙 할당 아니므로 소멸자 호출만
		std::destroy_at(static_cast<T*>(source));
	}

public:
	/// <summary>
	/// 지정된 초기 크기로 내부 자원을 초기화합니다. (호출하지 않으면 첫 할당 시 기본 크기로 초기화됩니다.)
	/// </summary>
	/// <param name="initialSize">초기 할당 또는 예약할 크기</param>
	static void Initialize(size_t initialSize = DefaultInitialSize);

	/// <summary>
	/// 현재 확장 스케일을 반환합니다.
	/// </summary>
	/// <returns>확장 스케일 값</returns>
	inline static float GetExpandScale() { return expandScale; }
	/// <summary>
	/// 할당자의 확장 스케일을 설정합니다. 값이 1 미만이면 AstrumException을 발생시키고 Alert()를 호출합니다.
	/// </summary>
	/// <param name="value">확장 스케일 (1 이상이여야 함). 1 미만이면 예외 발생</param>
	inline static void SetExpandScale(float value) {
		if (value < 1) {
			AstrumException("In AstrumCompactAllocator::SetExpandScale(float), value must be equals or greater than 1.").Alert();
			return;
		}
		expandScale = value;
	}

	/// <summary>
	/// 현재 압축 임계값을 반환합니다.
	/// </summary>
	/// <returns>압축 임계값</returns>
	inline static float GetCompactionThreshold() { return compactionThreshold; }
	/// <summary>
	/// 압축 임계값을 설정합니다. (기본값은 0.1f(10%)입니다.) 값이 0보다 작으면 0으로 설정됩니다.
	/// </summary>
	/// <param name="value">새로운 압축 임계값</param>
	inline static void SetCompactionThreshold(float value) { compactionThreshold = (std::max)(0.0f, value); }

	/// <summary>
	/// 현재 전체 크기를 반환합니다.
	/// </summary>
	/// <returns>현재 전체 크기</returns>
	static size_t GetCurrentSize() { return totalSize; }
	/// <summary>
	/// 할당 가능한 남은 크기를 반환합니다. (해제된 블록의 크기를 포함하며, 정렬 패딩은 압축 전까지 사용 중으로 계산됩니다.)
	/// </summary>
	static size_t GetRemainSize() { return remainSize; }

	/// <summary>
	/// 즉시 메모리 압축을 수행합니다.
	/// </summary>
	inline static void Compact() { if (nullptr != memoryPool) Resize(totalSize); }

private:
	template <typename ValueType>
	requires AstrumCompactable<ValueType>
	friend struct AstrumReplaceablePointer;

	static constexpr size_t DefaultInitialSize = 1024 * 1024;

	/// <summary>
	/// 내부 풀에서 T 하나를 담을 메모리 블록을 할당합니다. (객체를 생성하지는 않습니다.)
	/// 할당 이후 남는 공간이 압축 임계값 미만이면 풀을 확장하고, 남은 공간은 충분하지만 커서 뒤 연속 공간이 부족하면 압축합니다.
	/// </summary>
	/// <returns>할당된 메모리 블록. 마지막 참조가 사라지면 T의 소멸자를 호출하고 공간을 반환합니다.</returns>
	template <typename T>
	requires AstrumCompactable<T>
	static std::shared_ptr<AstrumCompactMemory> Allocate() {
		constexpr size_t alignment = alignof(T);
		constexpr size_t alignedSize = (sizeof(T) + alignment - 1) / alignment * alignment; // 정렬된 크기

		if (nullptr == memoryPool) Initialize();

		const size_t reserve = static_cast<size_t>(totalSize * compactionThreshold);
		// 1. 할당 이후 여유 메모리가 임계값 미만이 되면 더 큰 크기로 재배치 (재배치하면서 압축도 함께 이루어짐)
		if (remainSize < PaddingAtCursor(alignment) + alignedSize + reserve) {
			Resize(GetGrowSize(alignment, alignedSize));
		}
		// 2. 남은 공간은 충분한데, 해제된 블록이 커서 앞쪽에 흩어져 있어 커서 뒤가 부족한 경우 같은 크기로 압축
		else if (false == FitsAtCursor(alignment, alignedSize)) {
			Resize(totalSize);
		}
		// 3. 압축 이후에도 정렬 패딩 때문에 부족한 드문 경우 확장
		if (false == FitsAtCursor(alignment, alignedSize)) {
			Resize(GetGrowSize(alignment, alignedSize));
		}

		// 이후 메모리 풀이 더이상 변경되지 않으니, 여기서 주소를 계산하면 됨.
		const size_t padding = PaddingAtCursor(alignment);
		void* const alignedPtr = static_cast<char*>(poolCursor) + padding;
		poolCursor = static_cast<char*>(alignedPtr) + alignedSize;
		remainSize -= padding + alignedSize;

		AstrumCompactMemory::RelocatorFunction relocator;
		if constexpr (std::is_trivially_copyable_v<T>) {
			relocator = &TrivialRelocate<T>;
		}
		else {
			relocator = &MoveRelocate<T>;
		}

		auto* const memoryPtr = new AstrumCompactMemory(alignedPtr, alignedSize, alignment, relocator);
		std::shared_ptr<AstrumCompactMemory> resultPtr(
			memoryPtr,
			// alignedPtr는 고정이 아니라서 쓰면 큰일남
			[](AstrumCompactMemory* memory) {
				// T*는 힙 메모리로 만든게 아니므로 소멸자만 호출
				std::destroy_at(static_cast<T*>(memory->Get()));
				// 해제된 공간은 다음 압축 때 회수됨
				remainSize += memory->GetAlignedSize();
				// memoryPtr은 힙으로 만들었으니 제거
				delete memory;
			}
		);
		allocatedPointers.emplace_back(resultPtr);
		return resultPtr;
	}

	// 커서 위치에서 alignment를 맞추기 위해 필요한 패딩 크기
	static size_t PaddingAtCursor(size_t alignment) {
		const auto address = reinterpret_cast<std::uintptr_t>(poolCursor);
		return (alignment - address % alignment) % alignment;
	}
	// 커서 뒤의 연속된 공간에 할당할 수 있는지 여부
	static bool FitsAtCursor(size_t alignment, size_t alignedSize) {
		const size_t tail = static_cast<size_t>(static_cast<char*>(GetPoolEnd()) - static_cast<char*>(poolCursor));
		return PaddingAtCursor(alignment) + alignedSize <= tail;
	}
	// 확장 시 다음 풀 크기: 새 블록(최대 패딩 포함)과 임계값 만큼의 여유가 항상 남도록 계산
	static size_t GetGrowSize(size_t alignment, size_t alignedSize) {
		const size_t reserve = static_cast<size_t>(totalSize * compactionThreshold);
		return (std::max)(static_cast<size_t>(totalSize * expandScale), totalSize + alignedSize + alignment) + reserve;
	}

private:
	inline static float expandScale = 1.5f;
	inline static float compactionThreshold = 0.1f;
	inline static size_t totalSize = 0;
	inline static size_t remainSize = 0;
	inline static size_t poolAlignment = alignof(std::max_align_t);
	inline static void* memoryPool = nullptr;
	inline static void* poolCursor = nullptr;
	inline static void* GetPoolEnd() { return static_cast<void*>(static_cast<char*>(memoryPool) + totalSize); }

	inline static std::vector<std::weak_ptr<AstrumCompactMemory>> allocatedPointers;

	static void Resize(size_t nextSize);
};
