#pragma once
#include "AstrumObjectList.hpp"
#include <memory>

class IAstrumGroupObject {
public:
	virtual AstrumObjectList& GetObjectList() abstract;

    bool AddObject(shared_ptr<IAstrumObject> const obj);
    void AddObjects(const std::initializer_list<shared_ptr<IAstrumObject>>& objects);
    bool RemoveObject(shared_ptr<IAstrumObject> const obj);
    void ClearAllObjects();
    bool IsContainsObject(shared_ptr<IAstrumObject> const obj);
    int GetObjectCount();
};