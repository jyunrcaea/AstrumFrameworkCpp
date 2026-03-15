#pragma once
#include <memory>
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumRectanglePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

/// <summary>
/// 직사각형 도형을 나타내는 게임 객체입니다.
/// 직사각형 폴리곤으로 구성되며, 크기, 위치, 회전, 색상을 조정할 수 있습니다.
/// </summary>
class AstrumRectangleObject : public AstrumShapeObject
{
public:
    /// <summary>
    /// 기본 직사각형 객체를 생성합니다.
    /// </summary>
    AstrumRectangleObject();
    /// <summary>
    /// 기존 직사각형 폴리곤으로 직사각형 객체를 생성합니다.
    /// </summary>
    /// <param name="rectanglePolygon">사용할 직사각형 폴리곤입니다.</param>
    AstrumRectangleObject(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon);
    /// <summary>
    /// 너비, 높이, 색상을 지정하여 직사각형 객체를 생성합니다.
    /// </summary>
    /// <param name="width">직사각형의 너비입니다.</param>
    /// <param name="height">직사각형의 높이입니다.</param>
    /// <param name="color">직사각형의 색상입니다.</param>
    AstrumRectangleObject(float width, float height, const AstrumColor& color);

    /// <summary>
    /// 이 직사각형 객체의 폴리곤을 반환합니다.
    /// </summary>
    /// <returns>직사각형 폴리곤 공유 포인터입니다.</returns>
    std::shared_ptr<AstrumRectanglePolygons> GetRectanglePolygons() const;
    /// <summary>
    /// 직사각형 객체의 폴리곤을 설정합니다.
    /// </summary>
    /// <param name="rectanglePolygon">설정할 직사각형 폴리곤입니다.</param>
    void SetRectanglePolygons(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon);

    /// <summary>
    /// 직사각형의 모든 꼭짓점에 동일한 색상을 설정합니다.
    /// </summary>
    /// <param name="color">설정할 색상입니다.</param>
    void SetColor(const AstrumColor& color);
    /// <summary>
    /// 직사각형의 각 꼭짓점에 다른 색상을 설정합니다.
    /// </summary>
    /// <param name="leftTop">왼쪽 상단 꼭짓점의 색상입니다.</param>
    /// <param name="rightTop">오른쪽 상단 꼭짓점의 색상입니다.</param>
    /// <param name="leftBottom">왼쪽 하단 꼭짓점의 색상입니다.</param>
    /// <param name="rightBottom">오른쪽 하단 꼭짓점의 색상입니다.</param>
    void SetColor(const AstrumColor& leftTop, const AstrumColor& rightTop, const AstrumColor& leftBottom, const AstrumColor& rightBottom);
private:
    /// <summary>
    /// 이 직사각형 객체를 렌더링하기 위한 폴리곤 데이터입니다.
    /// </summary>
    std::shared_ptr<AstrumRectanglePolygons> rectanglePolygon = nullptr;

public:
    /// <summary>
    /// 기본 설정으로 AstrumRectangleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <returns>새로 생성된 AstrumRectangleObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumRectangleObject> MakeShared() { return std::make_shared<AstrumRectangleObject>(); }
    /// <summary>
    /// 직사각형 폴리곤을 지정하여 AstrumRectangleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="rectanglePolygon">사용할 직사각형 폴리곤입니다.</param>
    /// <returns>새로 생성된 AstrumRectangleObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumRectangleObject> MakeShared(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon) { 
        return std::make_shared<AstrumRectangleObject>(rectanglePolygon);
    }
    /// <summary>
    /// 너비, 높이, 색상을 지정하여 AstrumRectangleObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="width">직사각형의 너비입니다.</param>
    /// <param name="height">직사각형의 높이입니다.</param>
    /// <param name="color">직사각형의 색상입니다.</param>
    /// <returns>새로 생성된 AstrumRectangleObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumRectangleObject> MakeShared(float width, float height, const AstrumColor & color) {
        return std::make_shared<AstrumRectangleObject>(width, height, color);
    }
};