#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "AstrumChrono.hpp"
#include "AstrumGroupObject.hpp"
#include "AstrumMaterialObject.hpp"
#include "AstrumTextureCache.hpp"

class TextureObject : public AstrumMaterialObject {
public:
    TextureObject(const std::wstring& path) : AstrumMaterialObject(AstrumTextureCache::Load(path)) {

    }
};

class BackgroundObject : public TextureObject {
public:
    BackgroundObject() : TextureObject(L"base_light.jpg") {
        Position.SetZ(100);
    }

    virtual void Prepare() override {
        TextureObject::Prepare();

        const float ratio = (std::max)(
            static_cast<float>(AstrumWindow::GetWidth()) / static_cast<float>(GetTexture()->GetWidth()),
            static_cast<float>(AstrumWindow::GetHeight()) / static_cast<float>(GetTexture()->GetHeight())
        );
        Scale.SetX(ratio);
        Scale.SetY(ratio);
    }

};

class BackBoardObject : public AstrumPolygonsObject {
public:
    BackBoardObject() {
        Polygons = AstrumPolygons::MakeSharedByRectangle(
            AstrumVector3(-100, 200),
            AstrumVector3(100, 200),
            AstrumVector3(800, -500),
            AstrumVector3(-800, -500),
            AstrumColor::LightPeriwinkle
        );
    }
};

class NoteObject : public AstrumPolygonsObject {
public:
    NoteObject() {
        Polygons = AstrumPolygons::MakeSharedByRectangle(
            AstrumVector3(-100, 200),
            AstrumVector3(100, 200),
            AstrumVector3(800, -500),
            AstrumVector3(-800, -500),
            AstrumColor::Periwinkle
        );


    }
};

class MainScene : public AstrumGroupObject {
public:
    MainScene() {
        AddObjects({
            std::make_shared<BackgroundObject>(),
            std::make_shared<BackBoardObject>()
        });
    }
};