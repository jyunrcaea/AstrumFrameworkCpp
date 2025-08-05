#pragma once
#include <memory>
#include "IAstrumObject.hpp"
#include "../Collections/IAstrumObjectList.hpp"

struct IAstrumObjectList;

struct IAstrumGroupObject : public virtual IAstrumObject {
public:
    virtual ~IAstrumGroupObject() = default;
	virtual IAstrumObjectList& GetObjectList() = 0;

    inline bool AddObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Add(obj); }
    inline void AddObjects(const std::initializer_list<std::shared_ptr<IAstrumObject>>& objects) { 
        for (const auto& obj : objects) {
            GetObjectList().Add(obj);
        }
    }
    inline bool RemoveObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Remove(obj); }
    inline void ClearAllObjects() { GetObjectList().Clear(); }
    inline bool IsContainsObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Contains(obj); }
    inline int GetObjectCount() { return GetObjectList().Count(); }
};