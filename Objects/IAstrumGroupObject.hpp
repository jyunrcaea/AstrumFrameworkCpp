#pragma once
#include "../Collections/AstrumObjectList.hpp"
#include <memory>

class IAstrumGroupObject {
public:
	virtual AstrumObjectList& GetObjectList() abstract;

    inline bool AddObject(std::shared_ptr<IAstrumObject> const obj) { return GetObjectList().Add(obj); }
    inline void AddObjects(const std::initializer_list<std::shared_ptr<IAstrumObject>>& objects) { GetObjectList().AddRange(objects); }
    inline bool RemoveObject(std::shared_ptr<IAstrumObject> const obj) { return GetObjectList().Remove(obj); }
    inline void ClearAllObjects() { GetObjectList().Clear(); }
    inline bool IsContainsObject(std::shared_ptr<IAstrumObject> const obj) { return GetObjectList().Contains(obj); }
    inline int GetObjectCount() { return GetObjectList().Count(); }
};