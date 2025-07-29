#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "AstrumChrono.hpp"
#include "AstrumGroupObject.hpp"
#include "AstrumRectangleObject.hpp"
#include "AstrumCircleObject.hpp"

class TestRectangleObject : public AstrumRectangleObject
{
public:
	TestRectangleObject() : AstrumRectangleObject(200, 100, AstrumColor::LightBlue) {
		Position.SetX(-500);
	}
};

class TestCircleObject : public AstrumCircleObject
{
public:
	TestCircleObject() : AstrumCircleObject({AstrumVector3::Origin, AstrumColor::LightBlue }, 50) {
		Position.SetX(0);
	}
};

class TestRectObject : public AstrumRectangleObject
{
public:
	TestRectObject() {
		SetRectanglePolygons(AstrumRectanglePolygons::MakeShared(
			{ AstrumVector3(-100, -100), AstrumColor::LightPeriwinkle },
			{ AstrumVector3(100, 100), AstrumColor::Coral },
			{ AstrumVector3(-100, -100), AstrumColor::Periwinkle },
			{ AstrumVector3(100, -100), AstrumColor::MidnightBlue }
		));
		Position.SetX(500);
	}
};

class TestShapeScene : public AstrumGroupObject
{
public:
	TestShapeScene() {
		AddObjects({
			std::make_shared<TestRectangleObject>(),
			std::make_shared<TestCircleObject>(),
			std::make_shared<TestRectObject>(),
		});
	}
};