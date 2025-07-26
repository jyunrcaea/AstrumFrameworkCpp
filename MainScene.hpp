#pragma once
#include <iostream>
#include <string>
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
    BackgroundObject() : TextureObject(L"background.png") {
        Position.SetZ(10);
        
        float ratio = static_cast<float>(AstrumWindow::GetWidth()) / static_cast<float>(GetTexture()->GetWidth());
        Scale.SetX(ratio);
        Scale.SetY(ratio);
    }
};

class BoardObject : public TextureObject {
public:
    BoardObject() : TextureObject(L"board.png") {
        Position.SetZ(9);

        constexpr float ratio = static_cast<float>(1.0 / 3.0);
        Scale.SetX(ratio);
        Scale.SetY(ratio);
    }
};

class LaneObject : public TextureObject {
public:
    LaneObject(int index, uint8_t key) : TextureObject(std::format(L"lane{}.png", index)) {
        keybind = key;
        Position.SetZ(8);
        Visible = false;
    }

    virtual void Update() override {
        Visible = AstrumDirectInput::IsKeyPressed(keybind);

        TextureObject::Update();
    }

private:
    uint8_t keybind;
};

class BackBoardGroupObject : public AstrumGroupObject {
public:
    BackBoardGroupObject() {
        AddObjects({
            board = std::make_shared<BoardObject>(),
            lane1 = std::make_shared<LaneObject>(1, DIK_D),
            lane2 = std::make_shared<LaneObject>(2, DIK_F),
            lane3 = std::make_shared<LaneObject>(3, DIK_J),
            lane4 = std::make_shared<LaneObject>(4, DIK_K),
        });
    }

    virtual void Prepare() override {
        AstrumGroupObject::Prepare();

        float ratio = static_cast<float>(AstrumWindow::GetWidth()) / 1889.f;
        Scale.Reset(ratio, ratio, 1);
    }

private:
    using texobj = std::shared_ptr<TextureObject>;

    texobj board;
    texobj lane1;
    texobj lane2;
    texobj lane3;
    texobj lane4;
};

class MainScene : public AstrumGroupObject {
public:
    MainScene() {
        AddObjects({
            std::make_shared<BackgroundObject>(),
            std::make_shared<BackBoardGroupObject>()
        });
    }
};