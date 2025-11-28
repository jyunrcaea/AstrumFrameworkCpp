#pragma once
#include <memory>
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Collections/IAstrumComponentList.hpp"
#include "../Components/IAstrumComponent.hpp"
#include "../DI/IAstrumDependencyInjectionService.hpp"

struct IAstrumComponent;
struct IAstrumComponentList;
struct IAstrumGroupObject;
struct IAstrumDependencyInjectionService;

/// <summary>
/// 게임 객체의 기본 인터페이스입니다.
/// 위치, 회전, 크기 등의 변환 정보와 컴포넌트를 관리합니다.
/// </summary>
struct IAstrumObject : public std::enable_shared_from_this<IAstrumObject> {
    /// <summary>
    /// IAstrumObject 인터페이스를 소멸합니다.
    /// </summary>
    virtual ~IAstrumObject() = default;

    /// <summary>
    /// 객체를 준비합니다.
    /// </summary>
    virtual void Prepare() = 0;
    /// <summary>
    /// 객체를 업데이트합니다. 매 프레임마다 호출됩니다.
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// 객체를 해제합니다.
    /// </summary>
    virtual void Release() = 0;
    /// <summary>
    /// 객체를 그립니다.
    /// </summary>
    virtual void Draw() = 0;

    /// <summary>
    /// 객체의 상대 위치를 반환합니다. (부모 기준)
    /// </summary>
    /// <returns>상대 위치 벡터 참조입니다.</returns>
    virtual AstrumObservedVector3& GetPosition() = 0;
    /// <summary>
    /// 객체의 상대 회전을 반환합니다. (부모 기준)
    /// </summary>
    /// <returns>상대 회전 벡터 참조입니다. (오일러 각도, 단위: 도)</returns>
    virtual AstrumObservedVector3& GetRotation() = 0;
    /// <summary>
    /// 객체의 상대 크기를 반환합니다.
    /// </summary>
    /// <returns>상대 크기 벡터 참조입니다.</returns>
    virtual AstrumObservedVector3& GetScale() = 0;

    /// <summary>
    /// 객체의 절대 위치를 반환합니다. (월드 기준)
    /// </summary>
    /// <returns>절대 위치 벡터입니다.</returns>
    virtual const AstrumVector3& GetAbsolutePosition() = 0;
    /// <summary>
    /// 객체의 절대 회전을 반환합니다. (월드 기준)
    /// </summary>
    /// <returns>절대 회전 벡터입니다. (오일러 각도, 단위: 도)</returns>
    virtual const AstrumVector3& GetAbsoluteRotation() = 0;
    /// <summary>
    /// 객체의 절대 크기를 반환합니다.
    /// </summary>
    /// <returns>절대 크기 벡터입니다.</returns>
    virtual const AstrumVector3& GetAbsoluteScale() = 0;

    /// <summary>
    /// 객체의 위치를 설정합니다. (관찰 벡터 사본)
    /// </summary>
    /// <param name="vec">설정할 위치 벡터입니다.</param>
    void SetPosition(const AstrumObservedVector3& vec);
    /// <summary>
    /// 객체의 회전을 설정합니다. (관찰 벡터 사본)
    /// </summary>
    /// <param name="vec">설정할 회전 벡터입니다.</param>
    void SetRotation(const AstrumObservedVector3& vec);
    /// <summary>
    /// 객체의 크기를 설정합니다. (관찰 벡터 사본)
    /// </summary>
    /// <param name="vec">설정할 크기 벡터입니다.</param>
    void SetScale(const AstrumObservedVector3& vec);
    /// <summary>
    /// 객체의 위치를 설정합니다.
    /// </summary>
    /// <param name="vec">설정할 위치 벡터입니다.</param>
    void SetPosition(const AstrumVector3& vec);
    /// <summary>
    /// 객체의 회전을 설정합니다.
    /// </summary>
    /// <param name="vec">설정할 회전 벡터입니다.</param>
    void SetRotation(const AstrumVector3& vec);
    /// <summary>
    /// 객체의 크기를 설정합니다.
    /// </summary>
    /// <param name="vec">설정할 크기 벡터입니다.</param>
    void SetScale(const AstrumVector3& vec);
    /// <summary>
    /// 객체의 위치를 설정합니다. (우측값 참조)
    /// </summary>
    /// <param name="vec">설정할 위치 벡터입니다.</param>
    void SetPosition(AstrumVector3&& vec);
    /// <summary>
    /// 객체의 회전을 설정합니다. (우측값 참조)
    /// </summary>
    /// <param name="vec">설정할 회전 벡터입니다.</param>
    void SetRotation(AstrumVector3&& vec);
    /// <summary>
    /// 객체의 크기를 설정합니다. (우측값 참조)
    /// </summary>
    /// <param name="vec">설정할 크기 벡터입니다.</param>
    void SetScale(AstrumVector3&& vec);

    /// <summary>
    /// 객체의 위치를 설정합니다. (개별 좌표)
    /// </summary>
    /// <param name="x">X 좌표입니다.</param>
    /// <param name="y">Y 좌표입니다.</param>
    /// <param name="z">Z 좌표입니다.</param>
    void SetPosition(float x, float y, float z);
    /// <summary>
    /// 객체의 X 위치만 설정합니다.
    /// </summary>
    /// <param name="x">X 좌표입니다.</param>
    void SetPositionX(float x);
    /// <summary>
    /// 객체의 Y 위치만 설정합니다.
    /// </summary>
    /// <param name="y">Y 좌표입니다.</param>
	void SetPositionY(float y);
    /// <summary>
    /// 객체의 Z 위치만 설정합니다.
    /// </summary>
    /// <param name="z">Z 좌표입니다.</param>
	void SetPositionZ(float z);

    /// <summary>
    /// 객체의 회전을 설정합니다. (개별 각도)
    /// </summary>
    /// <param name="x">X축 회전(도)입니다.</param>
    /// <param name="y">Y축 회전(도)입니다.</param>
    /// <param name="z">Z축 회전(도)입니다.</param>
    void SetRotation(float x, float y, float z);
    /// <summary>
    /// 객체의 X축 회전만 설정합니다.
    /// </summary>
    /// <param name="x">X축 회전(도)입니다.</param>
	void SetRotationX(float x);
    /// <summary>
    /// 객체의 Y축 회전만 설정합니다.
    /// </summary>
    /// <param name="y">Y축 회전(도)입니다.</param>
	void SetRotationY(float y);
    /// <summary>
    /// 객체의 Z축 회전만 설정합니다.
    /// </summary>
    /// <param name="z">Z축 회전(도)입니다.</param>
	void SetRotationZ(float z);

    /// <summary>
    /// 객체의 크기를 설정합니다. (개별 축)
    /// </summary>
    /// <param name="x">X축 크기입니다.</param>
    /// <param name="y">Y축 크기입니다.</param>
    /// <param name="z">Z축 크기입니다.</param>
    void SetScale(float x, float y, float z);
    /// <summary>
    /// 객체의 X축 크기만 설정합니다.
    /// </summary>
    /// <param name="x">X축 크기입니다.</param>
	void SetScaleX(float x);
    /// <summary>
    /// 객체의 Y축 크기만 설정합니다.
    /// </summary>
    /// <param name="y">Y축 크기입니다.</param>
	void SetScaleY(float y);
    /// <summary>
    /// 객체의 Z축 크기만 설정합니다.
    /// </summary>
    /// <param name="z">Z축 크기입니다.</param>
	void SetScaleZ(float z);

    /// <summary>
    /// 객체의 부모를 반환합니다.
    /// </summary>
    /// <returns>부모 객체 포인터입니다. 부모가 없으면 nullptr입니다.</returns>
    virtual IAstrumGroupObject* GetParent() const = 0;
    /// <summary>
    /// 객체의 부모를 설정합니다.
    /// </summary>
    /// <param name="parent">설정할 부모 객체 포인터입니다.</param>
    /// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
    virtual bool SetParent(IAstrumGroupObject* const parent) = 0;
    /// <summary>
    /// 객체의 부모를 제거합니다.
    /// </summary>
    /// <param name="parent">제거할 부모 객체 포인터입니다.</param>
    /// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
    virtual bool ClearParent(IAstrumGroupObject* const parent) = 0;

    /// <summary>
    /// 객체에 붙어있는 컴포넌트 리스트를 반환합니다.
    /// </summary>
    /// <returns>컴포넌트 리스트 참조입니다.</returns>
    virtual IAstrumComponentList& GetComponents() = 0;

    /// <summary>
    /// 객체에 컴포넌트를 추가합니다.
    /// </summary>
    /// <param name="component">추가할 컴포넌트입니다.</param>
    /// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
    bool AddComponent(const std::shared_ptr<struct IAstrumComponent>& component);
    /// <summary>
    /// 객체에서 컴포넌트를 제거합니다.
    /// </summary>
    /// <param name="component">제거할 컴포넌트입니다.</param>
    /// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
    bool RemoveComponent(const std::shared_ptr<struct IAstrumComponent>& component);
    /// <summary>
    /// 객체의 모든 컴포넌트를 제거합니다.
    /// </summary>
    void ClearComponent();

    /// <summary>
    /// 객체의 의존성 주입 서비스를 반환합니다.
    /// </summary>
    /// <returns>의존성 주입 서비스 참조입니다.</returns>
    virtual IAstrumDependencyInjectionService& GetDependencyInjectionService() = 0;

    /// <summary>
    /// 객체의 절대 위치를 업데이트합니다. 부모 변환을 반영합니다.
    /// </summary>
    virtual void UpdateAbsolutePosition() = 0;
    /// <summary>
    /// 객체의 절대 회전을 업데이트합니다. 부모 변환을 반영합니다.
    /// </summary>
    virtual void UpdateAbsoluteRotation() = 0;
    /// <summary>
    /// 객체의 절대 크기를 업데이트합니다. 부모 변환을 반영합니다.
    /// </summary>
    virtual void UpdateAbsoluteScale() = 0;

    /// <summary>
    /// 객체의 표시 여부를 설정합니다.
    /// </summary>
    /// <param name="enable">true이면 표시, false이면 숨김입니다.</param>
	virtual void SetVisible(bool enable) = 0;

    /// <summary>
    /// 객체가 준비되었는지 확인합니다.
    /// </summary>
    /// <returns>준비되었으면 true, 아니면 false를 반환합니다.</returns>
    virtual bool IsPrepared() const = 0;
    /// <summary>
    /// 객체가 현재 표시되고 있는지 확인합니다.
    /// </summary>
    /// <returns>표시되고 있으면 true, 숨겨져 있으면 false를 반환합니다.</returns>
	virtual bool IsVisible() const = 0;
};