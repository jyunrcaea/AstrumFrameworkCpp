#pragma once
#define DI_GET(type, name) type*& name = DI.Reserve<type>(#name);
#define DI_SET(variable) DI.Add(#variable, variable);
#define ASTRUM_OBJECT(name) class name : public AstrumObject
#define ASTRUM_GROUP_OBJECT(name) class name : public AstrumGroupObject
#define ASTRUM_MATERIAL_OBJECT(name) class name : public AstrumMaterialObject
#define ASTRUM_PREPARE virtual void Prepare() override
#define ASTRUM_UPDATE virtual void Update() override
#define ASTRUM_RELEASE virtual void Release() override
#define ASTRUM_DRAW virtual void Draw() override

//#include "Objects/AstrumGroupObject.hpp"
//ASTRUM_OBJECT(MockObject) {
//	DI_GET(int, hello) // int*& hello = DI.Reserve<int>("hello");
//
//	std::string name = "hello world!";
//public:
//	ASTRUM_PREPARE { // virtual void Prepare() override
//		AstrumObject::Prepare();
//		DI_SET(name) // DI.Add("name", name);
//	}
//
//	ASTRUM_RELEASE { // virtual void Release() override
//		AstrumObject::Release();
//	}
//};