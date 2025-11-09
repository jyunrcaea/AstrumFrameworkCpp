#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "IAstrumDependencyInjectionService.hpp"
#include "../Objects/IAstrumGroupObject.hpp"

/// <summary>
/// 게임 객체에 의존성 주입을 계층 구조로 제공해주기 위한 클래스입니다. 지연 결합을 사용합니다. (주의: 타입 검사를 수행하지 않습니다. 조심히 사용하세요.)
/// </summary>
class AstrumDependencyInjectionService : public IAstrumDependencyInjectionService {
private:
	// for preserve unique_ptr
	std::vector<std::unique_ptr<void*>> resolvedPointers;
protected:
	// disposable map. be removed when resolved.
	std::unique_ptr<std::unordered_map<std::string, void**>> resolvedDictionary = std::make_unique<std::unordered_map<std::string, void**>>();
private:
	// share variable map
	std::unordered_map<std::string, void*> cachedDictionary;

public:
	virtual void*& Reserve(const std::string& key) override {
		if (false == resolvedDictionary->contains(key)) {
			(*resolvedDictionary)[key] = resolvedPointers.emplace_back(std::make_unique<void*>(nullptr)).get();
		}

		return *(*resolvedDictionary)[key];
	}

	/// <summary>
	/// 의존성을 예약합니다. 초기에는 nullptr이 담긴 포인터 변수의 참조를 갖게되며, 의존성이 해결되는 순간 해당 포인터 변수는 유효한 부모 변수의 주소를 갖게됩니다.
	/// </summary>
	/// <typeparam name="ReferenceType">예약할 의존성의 타입. 부모가 등록할 타입과 일치하면 됩니다.</typeparam>
	/// <param name="key">의존성을 식별하기 위한 문자열 키</param>
	/// <returns>예약된 포인터 변수의 참조..</returns>
	template <typename ReferenceType>
	ReferenceType*& Reserve(const std::string& key) {
		return *reinterpret_cast<ReferenceType**>(&Reserve(key));
	}

	/// <summary>
	/// 의존 가능한 변수를 등록합니다. 등록을 먼저 한 이후 자식과 결합하세요.
	/// </summary>
	/// <typeparam name="ShareType">등록할 변수의 타입</typeparam>
	/// <param name="key">등록할 의존성의 키</param>
	/// <param name="variable">등록할 변수(참조). 자식 객체가 해당 키로 의존성을 가지면 이 변수의 주소를 반환합니다.</param>
	template <typename ShareType>
	void Add(const std::string& key, ShareType& variable) {
		cachedDictionary[key] = &variable;
	}
	/// <summary>
	/// 주어진 키로 등록된 변수가 있는지 (현재 객체에서만) 확인하고 가져옵니다.
	/// </summary>
	/// <param name="key">문자열 키</param>
	/// <returns>찾을수 없는 경우 nullptr을 가져옵니다.</returns>
	void* Lookup(const std::string& key) const {
		const auto it = cachedDictionary.find(key);
		if (it == cachedDictionary.end()) return nullptr;
		return it->second;
	}

	/// <summary>
	/// 예약된 의존성을 즉시 해결합니다. 이후 해결된 변수는 사라집니다.
	/// </summary>
	/// <param name="owner">해결을 시작할 객체(자식 쪽에서 호출될 때 이 객체의 부모 트리에서 키를 탐색합니다)</param>
	virtual void Resolve(IAstrumObject* const owner) override {
		// Ancestors traversal
		for (auto* parent = owner->GetParent(); false == resolvedDictionary->empty() && parent != nullptr; parent = parent->GetParent()) {
			// Key-Value traversal
			for (auto it = resolvedDictionary->begin(); it != resolvedDictionary->end();) {
				// Try resolve
				if (auto* const cached = parent->GetDependencyInjectionService().Lookup(it->first)) {
					*it->second = cached;
					it = resolvedDictionary->erase(it);
				}
				else it++;
			}
		}
	}
};