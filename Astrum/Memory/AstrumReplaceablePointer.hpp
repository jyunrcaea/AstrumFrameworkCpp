#pragma once
#include <memory>
#include "AstrumCompactMemory.hpp"
#include "AstrumCompactAllocator.hpp"

/// <summary>
/// 관리형 동적 할당 포인터입니다. 내부적으로 AstrumCompactAllocator를 사용하여 메모리를 할당하고 해제합니다. 포인터가 가리키는 메모리 블록은 필요에 따라 이동될 수 있습니다.
/// </summary>
/// <typeparam name="T">포인터의 타입입니다.</typeparam>
template<typename T>
struct AstrumReplaceablePointer : public std::shared_ptr<AstrumCompactMemory> {
public:
	
	template <typename... Args>
	AstrumReplaceablePointer(Args... args)
		: std::shared_ptr<AstrumCompactMemory>(std::make_shared<AstrumCompactMemory>(AstrumCompactAllocator::Allocate(sizeof(T)), &AstrumReplaceablePointer::Free)) {
		new (this->get()->Get()) T(std::forward<Args>(args)...);
	}

	T* GetReplaceablePointer() const {
		return static_cast<T*>(this->get()->Get());
	}
	T* operator*() const {
		return static_cast<T*>(this->get()->Get());
	}

private:
	void Free() {
		delete static_cast<T*>(this->get()->Get());
		AstrumCompactAllocator::Free(*this->get()); // to do: check
	}
};
