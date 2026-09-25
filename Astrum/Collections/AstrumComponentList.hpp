#pragma once
#include <memory>
#include "IAstrumComponentList.hpp"
#include "AstrumIterationSafeVector.hpp"
#include "../AstrumException.hpp"

struct IAstrumComponent;
struct IAstrumObject;

class AstrumComponentList : public IAstrumComponentList
{
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
	/// 컴포넌트를 컬렉션에 추가합니다. 순회 도중에 추가하면 진행 중인 순회에는 포함되지 않고 다음 순회부터 포함됩니다.
	/// </summary>
	/// <param name="component">추가할 컴포넌트입니다. nullptr이거나 중복된 컴포넌트는 추가되지 않습니다.</param>
	/// <returns>컴포넌트가 성공적으로 추가되면 true, 중복 또는 nullptr이면 false를 반환합니다.</returns>
	virtual bool Add(const std::shared_ptr<IAstrumComponent>& component) override;
	/// <summary>
	/// 컬렉션에서 컴포넌트를 제거합니다. 순회 도중에 제거하면 진행 중인 순회에서도 즉시 건너뜁니다.
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
	/// 컬렉션의 모든 컴포넌트에 대해 주어진 함수를 실행합니다. (인터페이스용. 성능이 중요하면 Iterate()를 사용하세요.)
	/// 순회 도중(중첩 순회 포함)에 컴포넌트가 추가/삭제되어도 안전하며, 순회 도중 삭제된 컴포넌트는 건너뜁니다.
	/// </summary>
	/// <param name="func">각 컴포넌트에 대해 실행할 함수입니다.</param>
	virtual void ForEach(const std::function<void(const std::shared_ptr<IAstrumComponent>&)>& func) override;

	/// <summary>
	/// 순회 도중에 추가/삭제해도 안전한 순회 범위를 반환합니다. std::function을 거치지 않아 인라이닝됩니다.
	/// 예: for (IAstrumComponent* component : Components.Iterate()) component->Update();
	/// (순회 도중 삭제된 컴포넌트는 건너뛰며, 추가된 컴포넌트는 다음 순회부터 포함됩니다.)
	/// </summary>
	AstrumIterationSafeVector<IAstrumComponent>::Range Iterate() { return components.Iterate(); }

	/// <summary>
	/// 컬렉션에 포함된 컴포넌트의 개수를 반환합니다.
	/// </summary>
	size_t Count() const { return components.Count(); }

	/// <summary>
	/// 컬렉션의 모든 컴포넌트를 배열로 변환하여 반환합니다.
	/// </summary>
	/// <returns>컬렉션의 컴포넌트들을 포함한 벡터 복사본입니다.</returns>
	virtual std::vector<std::shared_ptr<IAstrumComponent>> ToArray() const override;
private:
	IAstrumObject* const owner;
	AstrumIterationSafeVector<IAstrumComponent> components;
};
