#pragma once
#include <iostream>
#include <string>
#include "AstrumChrono.hpp"
#include "AstrumGroupObject.hpp"
#include "AstrumMaterialObject.hpp"
#include "AstrumTextureManager.hpp"

class TextureObject : public AstrumMaterialObject {
public:
    TextureObject(const std::wstring& path) : AstrumMaterialObject(AstrumTextureManager::Instance().Load(path)) {

    }
};


class BackgroundObject : public TextureObject {
public:
    BackgroundObject() : TextureObject(L"background.png") {
        Position.SetZ(10);
        
        float ratio = static_cast<float>(AstrumWindow::Instance().GetWidth()) / static_cast<float>(GetTexture()->GetWidth());
        Scale.SetX(ratio);
        Scale.SetY(ratio);
    }
};

class BoardObject : public TextureObject {
public:
    BoardObject() : TextureObject(L"board.png") {
        Position.SetZ(9);

        float ratio = static_cast<float>(AstrumWindow::Instance().GetWidth()) / static_cast<float>(GetTexture()->GetWidth());
        Scale.SetX(ratio);
        Scale.SetY(ratio);
    }
};

class LaneObject : public TextureObject {
public:
    LaneObject(int index, uint8_t key) : TextureObject(std::format(L"lane{}.png", index)) {
        keybind = key;

        float ratio = static_cast<float>(AstrumWindow::Instance().GetWidth()) / static_cast<float>(GetTexture()->GetWidth());
        Scale.SetX(ratio);
        Scale.SetY(ratio);

        Visible = false;
    }

    virtual void Update() override {
        Visible = AstrumDirectInput::Instance().IsKeyPressed(keybind);

        TextureObject::Update();
    }

private:
    uint8_t keybind;
};

class MainScene : public AstrumGroupObject {
public:
    MainScene() {
        //AddObjects({
        //    std::make_shared<BackgroundObject>(),
        //    std::make_shared<BoardObject>(),

        //    std::make_shared<LaneObject>(1, DIK_D),
        //    std::make_shared<LaneObject>(2, DIK_F),
        //    std::make_shared<LaneObject>(3, DIK_J),
        //    std::make_shared<LaneObject>(4, DIK_K),
        //});
    }
};