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
	// 예약된 포인터 변수의 저장소 (주소가 변하지 않도록 unique_ptr로 보관)
	std::vector<std::unique_ptr<void*>> reservedPointers;
protected:
	// 예약된 키 -> 포인터 변수. 해결된 이후에도 지우지 않고, Prepare()마다 다시 해결합니다.
	// (객체가 다른 부모로 옮겨지면 새 부모 트리를 기준으로 다시 연결됩니다.)
	std::unordered_map<std::string, void**> reservedDictionary;
private:
	// share variable map
	std::unordered_map<std::string, void*> cachedDictionary;

public:
	virtual void*& Reserve(const std::string& key) override {
		auto it = reservedDictionary.find(key);
		if (it == reservedDictionary.end()) {
			it = reservedDictionary.emplace(key, reservedPointers.emplace_back(std::make_unique<void*>(nullptr)).get()).first;
		}

		return *it->second;
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
	void* Lookup(const std::string& key) const override {
		const auto it = cachedDictionary.find(key);
		if (it == cachedDictionary.end()) return nullptr;
		return it->second;
	}

	/// <summary>
	/// 예약된 모든 의존성을 현재 부모 트리를 기준으로 (다시) 해결합니다. 가장 가까운 조상에 등록된 변수가 연결되며, 찾지 못하면 nullptr이 됩니다.
	/// Prepare()마다 호출되므로, 객체를 다른 부모로 옮긴 뒤 다시 준비하면 새 부모의 변수로 연결됩니다.
	/// </summary>
	/// <param name="owner">해결을 시작할 객체(자식 쪽에서 호출될 때 이 객체의 부모 트리에서 키를 탐색합니다)</param>
	virtual void Resolve(IAstrumObject* const owner) override {
		// Key-Value traversal
		for (auto& [key, pointer] : reservedDictionary) {
			*pointer = nullptr;
			// Ancestors traversal
			for (auto* parent = owner->GetParent(); parent != nullptr; parent = parent->GetParent()) {
				if (auto* const cached = parent->GetDependencyInjectionService().Lookup(key)) {
					*pointer = cached;
					break;
				}
			}
		}
	}
};