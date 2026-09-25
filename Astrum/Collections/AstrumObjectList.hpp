#pragma once
#include <unordered_set>
#include <vector>
#include <functional>
#include <memory>
#include "IAstrumObjectList.hpp"
#include "../Objects/IAstrumGroupObject.hpp"

struct IAstrumGroupObject;

//자식 객체를 담기 위한 컬렉션 (추가/삭제시 자동으로 부모를 할당/제거 해주며, 부모가 준비된 경우 추가하는 즉시 Prepare() 호출.)
//객체는 추가된 순서를 유지하며, 이 순서대로 Update/Draw 됩니다. (같은 Z에서는 나중에 추가된 객체가 위에 그려짐)
class AstrumObjectList : public IAstrumObjectList {
public:
    /// <summary>
    /// AstrumObjectList를 생성합니다.
    /// </summary>
    /// <param name="owner">이 컬렉션의 소유 객체입니다. 추가되는 객체들의 부모로 설정됩니다.</param>
    explicit AstrumObjectList(IAstrumGroupObject* const owner);

    /// <summary>
    /// 컬렉션에 객체를 추가합니다. 추가된 객체의 부모를 자동으로 설정합니다.
    /// </summary>
    /// <param name="obj">추가할 객체입니다.</param>
    /// <returns>객체가 성공적으로 추가되면 true, 이미 존재하면 false를 반환합니다.</returns>
    bool Add(const std::shared_ptr<IAstrumObject>& obj) override;
    /// <summary>
    /// 컬렉션에 여러 객체들을 한 번에 추가합니다.
    /// </summary>
    /// <param name="list">추가할 객체들의 초기화 리스트입니다.</param>
    void AddRange(const std::initializer_list<std::shared_ptr<IAstrumObject>>& list);
    /// <summary>
    /// 컬렉션에서 객체를 제거합니다. 제거된 객체의 부모를 자동으로 제거합니다.
    /// </summary>
    /// <param name="obj">제거할 객체입니다.</param>
    /// <returns>객체가 성공적으로 제거되면 true, 없으면 false를 반환합니다.</returns>
    bool Remove(const std::shared_ptr<IAstrumObject>& obj) override;
    /// <summary>
    /// 컬렉션의 모든 객체를 제거합니다.
    /// </summary>
    void Clear() override;
    /// <summary>
    /// 컬렉션에 특정 객체가 포함되어 있는지 확인합니다.
    /// </summary>
    /// <param name="obj">확인할 객체입니다.</param>
    /// <returns>객체가 포함되어 있으면 true, 아니면 false를 반환합니다.</returns>
    bool Contains(const std::shared_ptr<IAstrumObject>& obj) const override;
    /// <summary>
    /// 컬렉션에 포함된 객체의 개수를 반환합니다.
    /// </summary>
    /// <returns>컬렉션의 객체 개수입니다.</returns>
    int Count() const override;
    /// <summary>
    /// 컬렉션의 모든 객체에 대해 추가된 순서대로 주어진 함수를 실행합니다.
    /// 순회 도중(중첩 순회 포함)에 객체가 추가/삭제되어도 안전하며, 순회 도중 삭제된 객체는 건너뜁니다. (추가된 객체는 다음 순회부터 포함됩니다.)
    /// </summary>
    /// <param name="func">각 객체에 대해 실행할 함수입니다.</param>
    void ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) override;
    /// <summary>
    /// 컬렉션의 특정 인덱스에 있는 객체를 반환합니다.
    /// </summary>
    /// <param name="index">객체의 인덱스입니다.</param>
    /// <returns>인덱스에 해당하는 객체 참조입니다.</returns>
	IAstrumObject& operator[](int index) override { return *objects[index]; }
    /// <summary>
    /// 컬렉션의 모든 객체를 배열로 변환하여 반환합니다.
    /// </summary>
    /// <returns>컬렉션의 객체들을 포함한 벡터입니다.</returns>
    std::vector<std::shared_ptr<IAstrumObject>> ToArray() const override;

private:
    // 순회 중이 아닐 때만 스냅샷을 최신 상태로 갱신합니다.
    void RefreshSnapshot();

    IAstrumGroupObject* const owner;
    // 가장 최신의 변경사항이 적용되는, 추가된 순서를 유지하는 목록
    std::vector<std::shared_ptr<IAstrumObject>> objects;
    // 빠른 포함 여부 확인을 위한 해시셋
    std::unordered_set<IAstrumObject*> objectSet;
    // objects에 변경점이 생길때마다 복사를 받고, 순회(ForEach)에 사용되는 배열.
    // 순회 도중에는 갱신하지 않으므로, 순회 도중에 객체가 추가/삭제되어도 (중첩 순회를 포함해) 안정적인 순회가 가능함.
    std::vector<std::shared_ptr<IAstrumObject>> snapshot;
    // objects에 변경사항이 생겼는지 여부
    bool changed = false;
    // 현재 진행 중인 순회(ForEach)의 깊이
    int iterationDepth = 0;
};
