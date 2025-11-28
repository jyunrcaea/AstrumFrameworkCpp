#pragma once
#include <memory>
#include <new>
#include <utility>
#include "AstrumCompactMemory.hpp"
#include "AstrumCompactAllocator.hpp"

/// <summary>
/// 관리형 동적 할당 포인터입니다. 내부적으로 AstrumCompactAllocator를 사용하여 메모리를 할당하고 해제합니다. 포인터가 가리키는 메모리 블록은 필요에 따라 이동될 수 있습니다.
/// </summary>
/// <typeparam name="T">포인터의 타입입니다.</typeparam>
template <typename ValueType>
requires AstrumCompactable<ValueType>
struct AstrumReplaceablePointer {
public:
	AstrumReplaceablePointer() : memoryBlockPtr(AstrumCompactAllocator::Allocate<ValueType>()) {
		new (memoryBlockPtr->Get()) ValueType();
	}

	template <typename First, typename... Rest>
	AstrumReplaceablePointer(First&& first, Rest&&... rest) : memoryBlockPtr(AstrumCompactAllocator::Allocate<ValueType>()) {
		//new (memoryBlockPtr->Get()) ValueType(std::forward<ParameterTypes>(parameters)...);
		std::construct_at(
			static_cast<ValueType*>(memoryBlockPtr->Get()),
			std::forward<First>(first),
			std::forward<Rest>(rest)...
		);
	}

	/// <summary>
	/// 주소가 언제든 바뀔수 있는 포인터를 반환합니다.
	/// </summary>
	/// <returns></returns>
	ValueType* GetReplaceablePointer() const {
		return static_cast<ValueType*>(memoryBlockPtr->Get());
	}
	ValueType* operator*() const {
		return static_cast<ValueType*>(memoryBlockPtr->Get());
	}

private:
	std::shared_ptr<struct AstrumCompactMemory> memoryBlockPtr;
};