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
            AstrumVector3(-800, -500),
            AstrumVector3(800, -500),
            AstrumColor::LightPeriwinkle
        );

        Position.SetZ(99);
    }
};

class LaneObject : public AstrumPolygonsObject {
public:
    LaneObject(int lane, uint8_t key) : keyBind(key) {
		const int leftTop = -100 + 50 * lane;
		const int leftBottom = -800 + 400 * lane;

        Polygons = AstrumPolygons::MakeSharedByRectangle(
            AstrumVector3(leftTop, 200),
            AstrumVector3(leftTop + 50, 200),
            AstrumVector3(leftBottom, -500),
            AstrumVector3(leftBottom + 400, -500),
            AstrumColor::Periwinkle
        );

        Position.SetZ(98);
    }

    virtual void Update() override {
		Visible = AstrumDirectInput::IsKeyPressed(keyBind);

        AstrumPolygonsObject::Update();
	}

private:
    uint8_t keyBind;
};

class NoteObject : public AstrumPolygonsObject {
    public:
    NoteObject(int lane) {
        const int leftTop = -100 + 50 * lane;
        const int leftBottom = -800 + 400 * lane;
        Polygons = AstrumPolygons::MakeSharedByRectangle(
            AstrumVector3(leftTop, 200),
            AstrumVector3(leftTop + 50, 200),
            AstrumVector3(leftBottom, -500),
            AstrumVector3(leftBottom + 400, -500),
            AstrumColor::LightPeriwinkle
        );
        Position.SetZ(97);
    }
    virtual void Update() override {
        // Logic for note movement and interaction
	}
}

class MainScene : public AstrumGroupObject {
public:
    MainScene() {
        AddObjects({
            std::make_shared<BackgroundObject>(),
            std::make_shared<BackBoardObject>(),

			std::make_shared<LaneObject>(0, DIK_D),
			std::make_shared<LaneObject>(1, DIK_F),
			std::make_shared<LaneObject>(2, DIK_J),
			std::make_shared<LaneObject>(3, DIK_K),
        });
    }
};