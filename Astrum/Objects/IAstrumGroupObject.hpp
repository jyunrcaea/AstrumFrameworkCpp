#pragma once
#include <memory>
#include "IAstrumObject.hpp"
#include "../Collections/IAstrumObjectList.hpp"

struct IAstrumObjectList;

    /// <summary>
    /// 자식 객체들을 포함할 수 있는 그룹 객체의 인터페이스입니다.
    /// IAstrumObject를 상속받아 게임 객체의 기본 기능을 유지하면서,
    /// 자식 객체 관리 기능을 추가합니다.
    /// </summary>
struct IAstrumGroupObject : public virtual IAstrumObject {
public:
    /// <summary>
    /// IAstrumGroupObject 인터페이스를 소멸합니다.
    /// </summary>
    virtual ~IAstrumGroupObject() = default;
    /// <summary>
    /// 이 그룹 객체의 자식 객체 리스트를 반환합니다.
    /// </summary>
    /// <returns>자식 객체 리스트 참조입니다.</returns>
	virtual IAstrumObjectList& GetObjectList() = 0;

    /// <summary>
    /// 그룹 객체에 자식 객체를 추가합니다.
    /// </summary>
    /// <param name="obj">추가할 자식 객체입니다.</param>
    /// <returns>자식 객체가 성공적으로 추가되면 true, 실패하면 false를 반환합니다.</returns>
    inline bool AddObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Add(obj); }
    /// <summary>
    /// 그룹 객체에 여러 자식 객체들을 한 번에 추가합니다.
    /// </summary>
    /// <param name="objects">추가할 자식 객체들의 초기화 리스트입니다.</param>
    inline void AddObjects(const std::initializer_list<std::shared_ptr<IAstrumObject>>& objects) { 
        for (const auto& obj : objects) {
            GetObjectList().Add(obj);
        }
    }
    /// <summary>
    /// 그룹 객체에서 자식 객체를 제거합니다.
    /// </summary>
    /// <param name="obj">제거할 자식 객체입니다.</param>
    /// <returns>자식 객체가 성공적으로 제거되면 true, 없으면 false를 반환합니다.</returns>
    inline bool RemoveObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Remove(obj); }
    /// <summary>
    /// 그룹 객체의 모든 자식 객체를 제거합니다.
    /// </summary>
    inline void ClearAllObjects() { GetObjectList().Clear(); }
    /// <summary>
    /// 그룹 객체가 특정 자식 객체를 포함하는지 확인합니다.
    /// </summary>
    /// <param name="obj">확인할 자식 객체입니다.</param>
    /// <returns>자식 객체가 포함되어 있으면 true, 없으면 false를 반환합니다.</returns>
    inline bool IsContainsObject(const std::shared_ptr<IAstrumObject>& obj) { return GetObjectList().Contains(obj); }
    /// <summary>
    /// 그룹 객체의 자식 객체 개수를 반환합니다.
    /// </summary>
    /// <returns>자식 객체의 개수입니다.</returns>
    inline int GetObjectCount() { return GetObjectList().Count(); }
};