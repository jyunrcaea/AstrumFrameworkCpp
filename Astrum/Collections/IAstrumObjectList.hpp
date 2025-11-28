#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "../Objects/IAstrumObject.hpp"

struct IAstrumObject;

struct IAstrumObjectList {
    /// <summary>
    /// IAstrumObjectList 인터페이스를 소멸합니다.
    /// </summary>
    virtual ~IAstrumObjectList() = default;
    /// <summary>
    /// 컬렉션에 객체를 추가합니다.
    /// </summary>
    /// <param name="obj">추가할 객체입니다.</param>
    /// <returns>객체가 성공적으로 추가되면 true, 이미 존재하면 false를 반환합니다.</returns>
    virtual bool Add(const std::shared_ptr<IAstrumObject>& obj) = 0;
    /// <summary>
    /// 컬렉션에서 객체를 제거합니다.
    /// </summary>
    /// <param name="obj">제거할 객체입니다.</param>
    /// <returns>객체가 성공적으로 제거되면 true, 없으면 false를 반환합니다.</returns>
    virtual bool Remove(const std::shared_ptr<IAstrumObject>& obj) = 0;
    /// <summary>
    /// 컬렉션의 모든 객체를 제거합니다.
    /// </summary>
    virtual void Clear() = 0;
    /// <summary>
    /// 컬렉션에 특정 객체가 포함되어 있는지 확인합니다.
    /// </summary>
    /// <param name="obj">확인할 객체입니다.</param>
    /// <returns>객체가 포함되어 있으면 true, 아니면 false를 반환합니다.</returns>
    virtual bool Contains(const std::shared_ptr<IAstrumObject>& obj) const = 0;
    /// <summary>
    /// 컬렉션에 포함된 객체의 개수를 반환합니다.
    /// </summary>
    /// <returns>컬렉션의 객체 개수입니다.</returns>
    virtual int Count() const = 0;
    /// <summary>
    /// 컬렉션의 모든 객체에 대해 주어진 함수를 실행합니다.
    /// </summary>
    /// <param name="func">각 객체에 대해 실행할 함수입니다.</param>
    virtual void ForEach(const std::function<void(const std::shared_ptr<IAstrumObject>&)>& func) = 0;
    /// <summary>
    /// 컬렉션의 특정 인덱스에 있는 객체를 반환합니다.
    /// </summary>
    /// <param name="index">객체의 인덱스입니다.</param>
    /// <returns>인덱스에 해당하는 객체 참조입니다.</returns>
	virtual IAstrumObject& operator[](int index) = 0;
    /// <summary>
    /// 컬렉션의 모든 객체를 배열로 변환하여 반환합니다.
    /// </summary>
    /// <returns>컬렉션의 객체들을 포함한 벡터입니다.</returns>
    virtual std::vector<std::shared_ptr<IAstrumObject>> ToArray() const = 0;
};