#pragma once
#include <unordered_set>
#include <vector>
#include <functional>
#include <memory>
#include <set>
#include "IAstrumObjectList.hpp"
#include "../Objects/IAstrumGroupObject.hpp"

struct IAstrumGroupObject;

//자식 객체를 담기 위한 컬렉션 (추가/삭제시 자동으로 부모를 할당/제거 해주며, 부모가 준비된 경우 추가하는 즉시 Prepare() 호출.)
class AstrumObjectList : public IAstrumObjectList {
public:
    explicit AstrumObjectList(IAstrumGroupObject* const owner);

    bool Add(const std::shared_ptr<IAstrumObject>& obj) override;
    void AddRange(const std::initializer_list<std::shared_ptr<IAstrumObject>>& objects);
    bool Remove(const std::shared_ptr<IAstrumObject>& obj) override;
    void Clear() override;
    bool Contains(const std::shared_ptr<IAstrumObject>& obj) const override;
    int Count() const override;
    void ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) override;
    std::vector<std::shared_ptr<IAstrumObject>> ToArray() const override;

private:
    void Update() const;

    IAstrumGroupObject* const owner;
    // 가장 최신의 변경사항이 적용되는 해시셋
    std::unordered_set<std::shared_ptr<IAstrumObject>> objectSet;
    // objectSet이 변경점이 생길때마다 복사를 받고, 순회(ForEach)에 사용되는 배열.
    // 이렇게 설계한 이유로는 vector가 순회가 매우 빠르며, 순회 도중에 객체가 추가/삭제시 해시셋에만 반영되므로 안정적인 순회가 가능해짐.
    mutable std::vector<std::shared_ptr<IAstrumObject>> objectArray;
    // objectSet에 변경사항이 생겼는지 여부
    mutable bool changed = false;
};