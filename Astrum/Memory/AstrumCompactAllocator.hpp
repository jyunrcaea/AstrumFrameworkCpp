#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <type_traits>
#include "AstrumCompactMemory.hpp"
#include "../AstrumException.hpp"

template<typename T>
concept AstrumCompactable = std::is_move_constructible_v<T> && std::is_destructible_v<T>;

template <typename ValueType>
requires AstrumCompactable<ValueType>
struct AstrumReplaceablePointer;

/// <summary>
/// 메모리 압축(compaction)을 지원하는 정적 할당자입니다. (주의: 멀티스레드를 고려하지 않았습니다.)(단일 스레드 전용)
/// </summary>
class AstrumCompactAllocator {
	AstrumCompactAllocator() = delete;

	// 단순 복사로 이루어지는 재할당
	template<typename T>
	static void TrivialRelocate(void* source, void* destination) {
		std::memmove(destination, source, sizeof(T));
	}

	// 이동 생성자를 이용하는 재할당
	template<typename T>
	static void MoveRelocate(void* source, void* destination) {
		// 이동 생성자
		new (static_cast<T*>(destination)) T(std::move(*static_cast<T*>(source)));
		// 힙 할당 아니므로 소멸자 호출만
		reinterpret_cast<T*>(source)->~T();
	}

public:
	/// <summary>
	/// 지정된 초기 크기로 내부 자원을 초기화합니다.
	/// </summary>
	/// <param name="initialSize">초기 할당 또는 예약할 크기</param>
	static void Initialize(size_t initialSize = 1024 * 1024);

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
	/// 즉시 메모리 압축을 수행합니다.
	/// </summary>
	inline static void Compact() { Resize(totalSize); }

private:
	template <typename ValueType>
	requires AstrumCompactable<ValueType>
	friend struct AstrumReplaceablePointer;

	/// <summary>
	/// 내부 풀에서 메모리 블록을 할당합니다. 요청한 크기를 만족할 수 없거나 남은 공간이 압축 임계값 이하로 떨어질 경우, 풀을 확장(Resize)하거나 압축할 수 있습니다.
	/// </summary>
	/// <param name="size">할당할 바이트 수. 큰 요청은 풀 확장을 유발할 수 있습니다</param>
	/// <returns>할당된 메모리 블록(포인터와 크기)을 나타내는 AstrumCompactMemory. 풀 커서는 size만큼 진행되고 remainSize는 감소합니다</returns>
	template <typename T>
	requires AstrumCompactable<T>
	static std::shared_ptr<AstrumCompactMemory> Allocate() {
		size_t tempSize = (std::numeric_limits<size_t>::max)();
		void* tempPtr = poolCursor;

		// 메모리 풀 변경을 염두해서, 주소는 임시로만.
		tempPtr = std::align(alignof(T), sizeof(T), tempPtr, tempSize);
		const size_t alignedSize = (sizeof(T) + alignof(T) - 1) / alignof(T) * alignof(T); // 정렬된 크기

		const size_t continuedSize = (static_cast<char*>(tempPtr) - static_cast<char*>(poolCursor)) + alignedSize; // 패딩 + 정렬된 크기 = 커서부터 할당 끝까지의 거리

		// 메모리가 부족하거나, 할당 이후 여유 메모리가 이미 임계값 미만 경우 더 큰 크기로 재배치
		if (const auto distance = static_cast<long long>(remainSize) - static_cast<long long>(continuedSize)
			; distance < 0 || distance < static_cast<size_t>(totalSize * compactionThreshold)) {
			Resize((std::max)(static_cast<size_t>(totalSize * expandScale + totalSize * compactionThreshold), totalSize + continuedSize));
		}
		// 남은 공간은 충분한데, 메모리 파편화로 인해 할당 불가능한 경우의 같은 크기의 재배치
		else if (static_cast<char*>(poolCursor) + continuedSize >= GetPoolEnd()) {
			Resize(totalSize);
		}

		// Resize 이후 메모리 풀이 더이상 변경되지 않으니, 여기서 alignedPtr를 계산하면 됨.
		void* const alignedPtr = std::align(alignof(T), sizeof(T), poolCursor, remainSize);
		// std::align이 poolCursor와 remainSize를 참조로 받지만, 수정하지 않음.
		poolCursor = static_cast<void*>(static_cast<char*>(poolCursor) + alignedSize);
		remainSize -= continuedSize;

		AstrumCompactMemory::RelocatorFunction relocator;
		if constexpr (std::is_trivially_move_constructible_v<T>) {
			relocator = &TrivialRelocate<T>;
		}
		else {
			relocator = &MoveRelocate<T>;
		}

		auto* const memoryPtr = new AstrumCompactMemory(alignedPtr, alignedSize, alignof(T), relocator);
		std::shared_ptr<AstrumCompactMemory> resultPtr(
			memoryPtr,
			// alignedPtr는 고정이 아니라서 쓰면 큰일남
			[memoryPtr](AstrumCompactMemory*) {
				// T*는 힙 메모리로 만든게 아니므로 소멸자만 호출
				static_cast<T*>(memoryPtr->Get())->~T();
				// remainSize 늘려야함
				remainSize += memoryPtr->GetAlignedSize();
				// memoryPtr은 힙으로 만들었으니 제거
				delete memoryPtr;
			}
		);
		allocatedPointers.emplace_back(resultPtr);
		return resultPtr;
	}
	
private:
	inline static float expandScale = 1.5f;
	inline static float compactionThreshold = 0.1f;
	inline static size_t totalSize = 0;
	inline static size_t remainSize = 0;
	inline static void* memoryPool = nullptr;
	inline static void* poolCursor = nullptr;
	inline static void* GetPoolEnd() { return static_cast<void*>(static_cast<char*>(memoryPool) + totalSize); }

	inline static std::vector<std::weak_ptr<AstrumCompactMemory>> allocatedPointers;

	static void Resize(size_t nextSize);
};