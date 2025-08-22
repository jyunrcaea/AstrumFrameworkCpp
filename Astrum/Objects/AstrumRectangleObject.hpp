#pragma once
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumRectanglePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

namespace Astrum
{
	// 직사각형 객체
	class RectangleObject : public ShapeObject
	{
	public:
		RectangleObject();
		RectangleObject(const std::shared_ptr<RectanglePolygons>& rectanglePolygon);
		RectangleObject(float width, float height, const Color& color);

		std::shared_ptr<RectanglePolygons> GetRectanglePolygons() const;
		void SetRectanglePolygons(const std::shared_ptr<RectanglePolygons>& rectanglePolygon);

		void SetColor(const Color& color);
		void SetColor(const Color& leftTop, const Color& rightTop, const Color& leftBottom, const Color& rightBottom);
	private:
		std::shared_ptr<RectanglePolygons> rectanglePolygon = nullptr;

	public:
		static std::shared_ptr<RectangleObject> MakeShared() { return std::make_shared<RectangleObject>(); }
		static std::shared_ptr<RectangleObject> MakeShared(const std::shared_ptr<RectanglePolygons>& rectanglePolygon) {
			return std::make_shared<RectangleObject>(rectanglePolygon);
		}
		static std::shared_ptr<RectangleObject> MakeShared(float width, float height, const Color& color) {
			return std::make_shared<RectangleObject>(width, height, color);
		}
	};
}