#pragma once
#include <vector>
#include <memory>
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumCirclePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

/// <summary>
/// 원형 도형을 나타내는 게임 객체입니다.
/// 원형 폴리곤으로 구성되며, 중심, 반지름, 분할 수를 조정할 수 있습니다.
/// </summary>
class AstrumCircleObject : public AstrumShapeObject {
public:
    /// <summary>
    /// 기본 원형 객체를 생성합니다.
    /// </summary>
    AstrumCircleObject();
    /// <summary>
    /// 기존 원형 폴리곤으로 원형 객체를 생성합니다.
    /// </summary>
    /// <param name="circlePolygon">사용할 원형 폴리곤입니다.</param>
    AstrumCircleObject(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);
    /// <summary>
    /// 중심, 반지름, 분할 수를 지정하여 원형 객체를 생성합니다.
    /// </summary>
    /// <param name="center">원의 중심점 및 색상입니다.</param>
    /// <param name="radius">원의 반지름입니다.</param>
    /// <param name="segment">원을 몇 개의 삼각형으로 분할할지 결정합니다. 
    /// 기본값은 128이고, 값이 클수록 원이 더 부드럽게 보입니다.</param>
    AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment = 128);

    /// <summary>
    /// 이 원형 객체의 폴리곤을 반환합니다.
    /// </summary>
    /// <returns>원형 폴리곤 공유 포인터입니다.</returns>
    std::shared_ptr<AstrumCirclePolygons> GetCirclePolygons() const;
    /// <summary>
    /// 원형 객체의 폴리곤을 설정합니다.
    /// </summary>
    /// <param name="circlePolygon">설정할 원형 폴리곤입니다.</param>
    void SetCirclePolygons(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);

private:
    /// <summary>
    /// 이 원형 객체를 렌더링하기 위한 폴리곤 데이터입니다.
    /// </summary>
    std::shared_ptr<AstrumCirclePolygons> circlePolygon;

public:
    /// <summary>
    /// 기본 설정으로 AstrumCircleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <returns>새로 생성된 AstrumCircleObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumCircleObject> MakeShared() { return std::make_shared<AstrumCircleObject>(); }
    /// <summary>
    /// 원형 폴리곤을 지정하여 AstrumCircleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="circlePolygon">사용할 원형 폴리곤입니다.</param>
    /// <returns>새로 생성된 AstrumCircleObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumCircleObject> MakeShared(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon) { return std::make_shared<AstrumCircleObject>(circlePolygon); }
    /// <summary>
    /// 중심, 반지름, 분할 수를 지정하여 AstrumCircleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="center">원의 중심점 및 색상입니다.</param>
    /// <param name="radius">원의 반지름입니다.</param>
    /// <param name="segment">원을 몇 개의 삼각형으로 분할할지 결정합니다. 
    /// 기본값은 128이고, 값이 클수록 원이 더 부드럽게 보입니다.</param>
    /// <returns>새로 생성된 AstrumCircleObject 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumCircleObject> MakeShared(const AstrumVertexColor& center, float radius, const unsigned short segment = 128) { return std::make_shared<AstrumCircleObject>(center, radius, segment); }
};