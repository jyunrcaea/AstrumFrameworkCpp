#pragma once
#include <memory>
#include "IAstrumObject.hpp"
#include "../Collections/IAstrumObjectList.hpp"

namespace Astrum {
	struct IObjectList;

	struct IGroupObject : public virtual IObject {
	public:
		virtual ~IGroupObject() = default;
		virtual IObjectList& GetObjectList() = 0;

		inline bool AddObject(const std::shared_ptr<IObject>& obj) { return GetObjectList().Add(obj); }
		inline void AddObjects(const std::initializer_list<std::shared_ptr<IObject>>& objects) {
			for (const auto& obj : objects) {
				GetObjectList().Add(obj);
			}
		}
		inline bool RemoveObject(const std::shared_ptr<IObject>& obj) { return GetObjectList().Remove(obj); }
		inline void ClearAllObjects() { GetObjectList().Clear(); }
		inline bool IsContainsObject(const std::shared_ptr<IObject>& obj) { return GetObjectList().Contains(obj); }
		inline int GetObjectCount() { return GetObjectList().Count(); }
	};
}