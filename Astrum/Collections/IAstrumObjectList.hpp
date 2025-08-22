#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "../Objects/IAstrumObject.hpp"

namespace Astrum {
	struct IObject;

	struct IObjectList {
		virtual ~IObjectList() = default;
		virtual bool Add(const std::shared_ptr<IObject>& obj) = 0;
		virtual bool Remove(const std::shared_ptr<IObject>& obj) = 0;
		virtual void Clear() = 0;
		virtual bool Contains(const std::shared_ptr<IObject>& obj) const = 0;
		virtual int Count() const = 0;
		virtual void ForEach(const std::function<void(const std::shared_ptr<IObject>&)>& func) = 0;
		virtual std::vector<std::shared_ptr<IObject>> ToArray() const = 0;
	};
}