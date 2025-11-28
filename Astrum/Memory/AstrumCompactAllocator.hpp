#pragma once
#include <set>
#include "AstrumCompactMemory.hpp"
#include "../AstrumException.hpp"

/// <summary>
/// 메모리 압축(compaction)을 지원하는 정적 할당자입니다.
/// </summary>
class AstrumCompactAllocator {
	AstrumCompactAllocator() = delete;

public:
	/// <summary>
	/// 지정된 초기 크기로 내부 자원을 초기화합니다.
	/// </summary>
	/// <param name="initialSize">초기 할당 또는 예약할 크기</param>
	static void Initialize(size_t initialSize = 8192);

	/// <summary>
	/// 현재 확장 스케일을 반환합니다.
	/// </summary>
	/// <returns>확장 스케일 값</returns>
	static float GetExpandScale() { return expandScale; }
	/// <summary>
	/// 할당자의 확장 스케일을 설정합니다. 값이 0 이하면 AstrumException을 발생시키고 Alert()를 호출합니다.
	/// </summary>
	/// <param name="value">확장 스케일 (0보다 커야 함). 0 이하면 예외 발생</param>
	static void SetExpandScale(float value) { 
		if (value <= 0) {
			AstrumException("In AstrumCompactAllocator::SetExpandScale(float), value must be greater than 0.").Alert();
		}
		expandScale = value;
	}

	/// <summary>
	/// 현재 압축 임계값을 반환합니다.
	/// </summary>
	/// <returns>압축 임계값</returns>
	static float GetCompactionThreshold() { return compactionThreshold; }
	/// <summary>
	/// 압축 임계값을 설정합니다.
	/// </summary>
	/// <param name="value">새로운 압축 임계값</param>
	static void SetCompactionThreshold(float value) { compactionThreshold = value; }

	/// <summary>
	/// 현재 전체 크기를 반환합니다.
	/// </summary>
	/// <returns>현재 전체 크기</returns>
	static size_t GetCurrentSize() { return totalSize; }

private:
	friend struct AstrumReplaceablePointer;

	/// <summary>
	/// 내부 풀에서 메모리 블록을 할당합니다. 요청한 크기를 만족할 수 없거나 남은 공간이 압축 임계값 이하로 떨어질 경우, 풀을 확장(Resize)하거나 압축할 수 있습니다.
	/// </summary>
	/// <param name="size">할당할 바이트 수. 큰 요청은 풀 확장을 유발할 수 있습니다</param>
	/// <returns>할당된 메모리 블록(포인터와 크기)을 나타내는 AstrumCompactMemory. 풀 커서는 size만큼 진행되고 remainSize는 감소합니다</returns>
	template <typename T>
	static AstrumCompactMemory Allocate();
	/// <summary>
	/// 할당된 AstrumCompactMemory 블록을 해제하고, 할당자 정보를 업데이트하며, 블록을 nullptr로 이동합니다. 블록을 찾을 수 없으면 AstrumException을 발생시킵니다.
	/// </summary>
	/// <param name="memoryBlock">해제할 AstrumCompactMemory 참조. 할당자의 나머지 크기에 추가되고 nullptr로 이동합니다</param>
	static void Free(AstrumCompactMemory& memoryBlock);
	
private:
	inline static float expandScale = 1.5f;
	inline static float compactionThreshold = 0.2f;
	inline static size_t totalSize = 0;
	inline static size_t remainSize = 0;
	inline static void* memoryPool = nullptr;
	inline static void* poolCursor = nullptr;

	inline static std::set<AstrumCompactMemory> allocatedPointers;

	static void Resize(size_t nextSize);
};