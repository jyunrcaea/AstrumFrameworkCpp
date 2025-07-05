#pragma once

#include "IAstrumObjectList.hpp"
#include <unordered_set>
#include <vector>
#include <functional>
#include <memory>

class AstrumObjectList : public IAstrumObjectList {
public:
    explicit AstrumObjectList(std::shared_ptr<IAstrumObject> owner);

    bool Add(std::shared_ptr<IAstrumObject> obj) override;
    bool Remove(std::shared_ptr<IAstrumObject> obj) override;
    void Clear() override;
    bool Contains(std::shared_ptr<IAstrumObject> obj) const override;
    int Count() const override;
    void ForEach(const std::function<void(std::shared_ptr<IAstrumObject>)>& func) override;
    std::vector<std::shared_ptr<IAstrumObject>> ToArray() const override;

private:
    void Update() const;

    std::shared_ptr<IAstrumObject> owner;
    std::unordered_set<std::shared_ptr<IAstrumObject>> objectSet;
    mutable std::vector<std::shared_ptr<IAstrumObject>> objectArray;
    mutable bool changed{ false };
};