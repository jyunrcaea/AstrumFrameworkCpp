#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

struct IAstrumDependencyInjectionService {
public:
	// 의존성을 예약합니다. 초기에는 nullptr이 담긴 포인터 변수의 참조를 갖게되며, 부모와 결합하는 순간 해당 포인터 변수는 유효한 부모 변수의 주소를 갖게됩니다.
	virtual void*& Reserve(const std::string& key) = 0;
	// 주어진 키로 등록된 의존 가능한 변수가 있는지 살펴 가져옵니다. 해당 키로 등록되지 않은 경우 nullptr이 반환됩니다.
	virtual void* Lookup(const std::string& key) const = 0;
	// 예약된 의존성을 즉시 해결합니다.
	virtual void Resolve(struct IAstrumObject* const owner) = 0;
};