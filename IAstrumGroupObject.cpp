#include "IAstrumGroupObject.hpp"

bool IAstrumGroupObject::AddObject(shared_ptr<IAstrumObject> const obj) { return GetObjectList().Add(obj); }
void IAstrumGroupObject::AddObjects(const std::initializer_list<shared_ptr<IAstrumObject>>& objects) { GetObjectList().AddRange(objects); }
bool IAstrumGroupObject::RemoveObject(shared_ptr<IAstrumObject> const obj) { return GetObjectList().Remove(obj); }
void IAstrumGroupObject::ClearAllObjects() { GetObjectList().Clear(); }
bool IAstrumGroupObject::IsContainsObject(shared_ptr<IAstrumObject> const obj) { return GetObjectList().Contains(obj); }
int IAstrumGroupObject::GetObjectCount() { return GetObjectList().Count(); }