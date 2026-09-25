#pragma once
#include <memory>
#include "IAstrumComponentList.hpp"
#include "../AstrumException.hpp"

struct IAstrumComponent;
struct IAstrumObject;

class AstrumComponentList : public IAstrumComponentList, private std::vector<std::shared_ptr<IAstrumComponent>>
{
	using vec = std::vector<std::shared_ptr<IAstrumComponent>>;
	using iter = vec::iterator;
public:
	/// <summary>
	/// AstrumComponentList를 생성합니다.
	/// </summary>
	/// <param name="ownerObject">이 컬렉션의 소유 객체입니다.</param>
	AstrumComponentList(IAstrumObject* ownerObject);
	/// <summary>
	/// AstrumComponentList를 소멸합니다.
	/// </summary>
	~AstrumComponentList();
	/// <summary>
	/// 컴포넌트를 컬렉션에 추가합니다.
	/// </summary>
	/// <param name="component">추가할 컴포넌트입니다. nullptr이거나 중복된 컴포넌트는 추가되지 않습니다.</param>
	/// <returns>컴포넌트가 성공적으로 추가되면 true, 중복 또는 nullptr이면 false를 반환합니다.</returns>
	virtual bool Add(const std::shared_ptr<IAstrumComponent>& component) override;
	/// <summary>
	/// 컬렉션에서 컴포넌트를 제거합니다.
	/// </summary>
	/// <param name="component">제거할 컴포넌트입니다.</param>
	/// <returns>컴포넌트가 성공적으로 제거되면 true, 존재하지 않거나 nullptr이면 false를 반환합니다.</returns>
	virtual bool Remove(const std::shared_ptr<IAstrumComponent>& component) override;
	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 제거합니다.
	/// </summary>
	virtual void Clear() override;

	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 준비합니다.
	/// </summary>
	virtual void Prepare() override;
	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 업데이트합니다.
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 해제합니다.
	/// </summary>
	virtual void Release() override;

	/// <summary>
	/// 컬렉션의 모든 컴포넌트에 대해 주어진 함수를 실행합니다.
	/// 순회 도중(중첩 순회 포함)에 컴포넌트가 추가/삭제되어도 안전하며, 순회 도중 삭제된 컴포넌트는 건너뜁니다. (추가된 컴포넌트는 다음 순회부터 포함됩니다.)
	/// </summary>
	/// <param name="func">각 컴포넌트에 대해 실행할 함수입니다.</param>
	virtual void ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) override;

	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 배열로 변환하여 반환합니다.
	/// </summary>
	/// <returns>컬렉션의 컴포넌트들을 포함한 벡터 복사본입니다.</returns>
	virtual std::vector<std::shared_ptr<IAstrumComponent>> ToArray() const override;
	/// <summary>
	/// 컬렉션의 시작 반복자를 반환합니다. (주의: 반복자로 순회하는 도중에는 컴포넌트를 추가/삭제하면 안 됩니다. 안전한 순회는 ForEach()를 사용하세요.)
	/// </summary>
	/// <returns>시작 반복자입니다.</returns>
	iter begin() { return vec::begin(); }
	/// <summary>
	/// 컬렉션의 끝 반복자를 반환합니다.
	/// </summary>
	/// <returns>끝 반복자입니다.</returns>
	iter end() { return vec::end(); }
	/// <summary>
	/// 컬렉션의 역방향 시작 반복자를 반환합니다.
	/// </summary>
	/// <returns>역방향 시작 반복자입니다.</returns>
	auto rbegin() { return vec::rbegin(); }
	/// <summary>
	/// 컬렉션의 역방향 끝 반복자를 반환합니다.
	/// </summary>
	/// <returns>역방향 끝 반복자입니다.</returns>
	auto rend() { return vec::rend(); }
private:
	// 순회 중이 아닐 때만 스냅샷을 최신 상태로 갱신합니다.
	void RefreshSnapshot();

	IAstrumObject* const owner;
	// ForEach()에서 순회에 사용하는 복사본. 순회 도중에는 갱신하지 않으므로 순회 중 추가/삭제에도 안전합니다.
	vec snapshot;
	// 컴포넌트 목록에 변경사항이 생겼는지 여부
	bool changed = false;
	// 현재 진행 중인 순회(ForEach)의 깊이
	int iterationDepth = 0;
};