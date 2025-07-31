#pragma once
#include "../Objects/IAstrumObject.hpp"
#include <functional>
#include <vector>
#include <memory>

struct IAstrumObjectList {
    virtual ~IAstrumObjectList() = default;
    virtual bool Add(const std::shared_ptr<IAstrumObject>& obj) = 0;
    virtual bool Remove(const std::shared_ptr<IAstrumObject>& obj) = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const std::shared_ptr<IAstrumObject>& obj) const = 0;
    virtual int Count() const = 0;
    virtual void ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) = 0;
    virtual std::vector<std::shared_ptr<IAstrumObject>> ToArray() const = 0;
};