#pragma once
#include "AstrumVector4.hpp"

struct AstrumColor {
    float Red, Green, Blue, Alpha;

    constexpr AstrumColor(float r = 0, float g = 0, float b = 0, float a = 1.0f)
        : Red(r), Green(g), Blue(b), Alpha(a) {
    }

    operator AstrumVector4() const { return AstrumVector4(Red, Green, Blue, Alpha); }

    static const AstrumColor White;
    static const AstrumColor Black;
    static const AstrumColor Gray;
    static const AstrumColor Silver;
    static const AstrumColor LightGray;
    static const AstrumColor DarkGray;

    // === 보라 계열 ===
    static const AstrumColor Purple;
    static const AstrumColor Violet;
    static const AstrumColor Lilac;
    static const AstrumColor Lavender;
    static const AstrumColor Orchid;
    static const AstrumColor Plum;
    static const AstrumColor Amethyst;

    // === 남보라 / 파랑 계열 ===
    static const AstrumColor Periwinkle;
    static const AstrumColor LightPeriwinkle;
    static const AstrumColor PureBlue;
    static const AstrumColor LightBlue;
    static const AstrumColor SkyBlue;
    static const AstrumColor RoyalBlue;
    static const AstrumColor MidnightBlue;
    static const AstrumColor Navy;
    static const AstrumColor Indigo;

    // === 청록 계열 ===
    static const AstrumColor Cyan;
    static const AstrumColor Teal;
    static const AstrumColor Turquoise;
    static const AstrumColor LightSeaGreen;
    static const AstrumColor Aquamarine;
    static const AstrumColor MediumTurquoise;
    static const AstrumColor PaleTurquoise;
    static const AstrumColor DarkCyan;

    // === 초록 계열 ===
    static const AstrumColor Lime;
    static const AstrumColor PureGreen;
    static const AstrumColor ForestGreen;
    static const AstrumColor DarkGreen;
    static const AstrumColor MintGreen;

    // === 연두 계열 ===
    static const AstrumColor YellowGreen;
    static const AstrumColor GreenYellow;
    static const AstrumColor Chartreuse;
    static const AstrumColor GrassGreen;
    static const AstrumColor YellowishGreen;

    // === 노랑 계열 ===
    static const AstrumColor Yellow;
    static const AstrumColor Turbo;
    static const AstrumColor MoonYellow;
    static const AstrumColor VividYellow;
    static const AstrumColor GoldenYellow;
    static const AstrumColor Lemon;
    static const AstrumColor Mustard;

    // === 주황 계열 ===
    static const AstrumColor Orange;
    static const AstrumColor DarkOrange;
    static const AstrumColor Coral;
    static const AstrumColor Tomato;
    static const AstrumColor Peach;

    // === 빨강 계열 ===
    static const AstrumColor PureRed;
    static const AstrumColor DarkRed;
    static const AstrumColor Crimson;
    static const AstrumColor Firebrick;
    static const AstrumColor Scarlet;

    // === 갈색 계열 ===
    static const AstrumColor Brown;
    static const AstrumColor SaddleBrown;
    static const AstrumColor Sienna;
    static const AstrumColor Chocolate;
    static const AstrumColor Peru;
    static const AstrumColor Tan;

    // === 분홍 계열 ===
    static const AstrumColor Pink;
    static const AstrumColor LightPink;
    static const AstrumColor HotPink;
    static const AstrumColor DeepPink;
    static const AstrumColor PaleVioletRed;
};

inline constexpr AstrumColor AstrumColor::White = AstrumColor(1.0f, 1.0f, 1.0f);
inline constexpr AstrumColor AstrumColor::Black = AstrumColor(0.0f, 0.0f, 0.0f);
inline constexpr AstrumColor AstrumColor::Gray = AstrumColor(0.498f, 0.498f, 0.498f);
inline constexpr AstrumColor AstrumColor::Silver = AstrumColor(0.753f, 0.753f, 0.753f);
inline constexpr AstrumColor AstrumColor::LightGray = AstrumColor(0.827f, 0.827f, 0.827f);
inline constexpr AstrumColor AstrumColor::DarkGray = AstrumColor(0.247f, 0.247f, 0.247f);

// === 보라 계열 ===
inline constexpr AstrumColor AstrumColor::Purple = AstrumColor(0.502f, 0.0f, 0.502f);
inline constexpr AstrumColor AstrumColor::Violet = AstrumColor(0.498f, 0.0f, 1.0f);
inline constexpr AstrumColor AstrumColor::Lilac = AstrumColor(0.784f, 0.635f, 0.784f);
inline constexpr AstrumColor AstrumColor::Lavender = AstrumColor(0.902f, 0.902f, 1.0f);
inline constexpr AstrumColor AstrumColor::Orchid = AstrumColor(0.855f, 0.439f, 0.839f);
inline constexpr AstrumColor AstrumColor::Plum = AstrumColor(0.867f, 0.627f, 0.867f);
inline constexpr AstrumColor AstrumColor::Amethyst = AstrumColor(0.6f, 0.4f, 0.8f);

// === 남보라 / 파랑 계열 ===
inline constexpr AstrumColor AstrumColor::Periwinkle = AstrumColor(0.502f, 0.502f, 1.0f);
inline constexpr AstrumColor AstrumColor::LightPeriwinkle = AstrumColor(0.8f, 0.8f, 1.0f);
inline constexpr AstrumColor AstrumColor::PureBlue = AstrumColor(0.0f, 0.0f, 1.0f);
inline constexpr AstrumColor AstrumColor::LightBlue = AstrumColor(0.678f, 0.847f, 0.902f);
inline constexpr AstrumColor AstrumColor::SkyBlue = AstrumColor(0.529f, 0.808f, 0.922f);
inline constexpr AstrumColor AstrumColor::RoyalBlue = AstrumColor(0.255f, 0.412f, 0.882f);
inline constexpr AstrumColor AstrumColor::MidnightBlue = AstrumColor(0.098f, 0.098f, 0.439f);
inline constexpr AstrumColor AstrumColor::Navy = AstrumColor(0.0f, 0.0f, 0.502f);
inline constexpr AstrumColor AstrumColor::Indigo = AstrumColor(0.294f, 0.0f, 0.51f);

// === 청록 계열 ===
inline const AstrumColor AstrumColor::Cyan = AstrumColor(0.0f, 1.0f, 1.0f);
inline const AstrumColor AstrumColor::Teal = AstrumColor(0.0f, 0.502f, 0.502f);
inline const AstrumColor AstrumColor::Turquoise = AstrumColor(0.251f, 0.878f, 0.816f);
inline const AstrumColor AstrumColor::LightSeaGreen = AstrumColor(0.125f, 0.698f, 0.667f);
inline const AstrumColor AstrumColor::Aquamarine = AstrumColor(0.498f, 1.0f, 0.831f);
inline const AstrumColor AstrumColor::MediumTurquoise = AstrumColor(0.282f, 0.82f, 0.8f);
inline const AstrumColor AstrumColor::PaleTurquoise = AstrumColor(0.686f, 0.933f, 0.933f);
inline const AstrumColor AstrumColor::DarkCyan = AstrumColor(0.0f, 0.545f, 0.545f);

// === 초록 계열 ===
inline const AstrumColor AstrumColor::Lime = AstrumColor(0.0f, 1.0f, 0.0f);
inline const AstrumColor AstrumColor::PureGreen = AstrumColor(0.0f, 0.502f, 0.0f);
inline const AstrumColor AstrumColor::ForestGreen = AstrumColor(0.133f, 0.545f, 0.133f);
inline const AstrumColor AstrumColor::DarkGreen = AstrumColor(0.0f, 0.392f, 0.0f);
inline const AstrumColor AstrumColor::MintGreen = AstrumColor(0.596f, 1.0f, 0.596f);

// === 연두 계열 ===
inline const AstrumColor AstrumColor::YellowGreen = AstrumColor(0.604f, 0.804f, 0.196f);
inline const AstrumColor AstrumColor::GreenYellow = AstrumColor(0.678f, 1.0f, 0.184f);
inline const AstrumColor AstrumColor::Chartreuse = AstrumColor(0.498f, 1.0f, 0.0f);
inline const AstrumColor AstrumColor::GrassGreen = AstrumColor(0.459f, 0.651f, 0.290f);
inline const AstrumColor AstrumColor::YellowishGreen = AstrumColor(0.627f, 0.69f, 0.212f);

// === 노랑 계열 ===
inline const AstrumColor AstrumColor::Yellow = AstrumColor(1.0f, 1.0f, 0.0f);
inline const AstrumColor AstrumColor::Turbo = AstrumColor(1.0f, 0.8f, 0.129f);
inline const AstrumColor AstrumColor::MoonYellow = AstrumColor(0.941f, 0.769f, 0.125f);
inline const AstrumColor AstrumColor::VividYellow = AstrumColor(1.0f, 0.89f, 0.008f);
inline const AstrumColor AstrumColor::GoldenYellow = AstrumColor(1.0f, 0.549f, 0.0f);
inline const AstrumColor AstrumColor::Lemon = AstrumColor(1.0f, 0.973f, 0.0f);
inline const AstrumColor AstrumColor::Mustard = AstrumColor(1.0f, 0.859f, 0.345f);

// === 주황 계열 ===
inline const AstrumColor AstrumColor::Orange = AstrumColor(1.0f, 0.498f, 0.0f);
inline const AstrumColor AstrumColor::DarkOrange = AstrumColor(1.0f, 0.549f, 0.0f);
inline const AstrumColor AstrumColor::Coral = AstrumColor(1.0f, 0.498f, 0.314f);
inline const AstrumColor AstrumColor::Tomato = AstrumColor(1.0f, 0.388f, 0.278f);
inline const AstrumColor AstrumColor::Peach = AstrumColor(1.0f, 0.855f, 0.725f);

// === 빨강 계열 ===
inline const AstrumColor AstrumColor::PureRed = AstrumColor(1.0f, 0.0f, 0.0f);
inline const AstrumColor AstrumColor::DarkRed = AstrumColor(0.545f, 0.0f, 0.0f);
inline const AstrumColor AstrumColor::Crimson = AstrumColor(0.863f, 0.078f, 0.235f);
inline const AstrumColor AstrumColor::Firebrick = AstrumColor(0.698f, 0.133f, 0.133f);
inline const AstrumColor AstrumColor::Scarlet = AstrumColor(1.0f, 0.141f, 0.0f);

// === 갈색 계열 ===
inline const AstrumColor AstrumColor::Brown = AstrumColor(0.647f, 0.165f, 0.165f);
inline const AstrumColor AstrumColor::SaddleBrown = AstrumColor(0.545f, 0.271f, 0.075f);
inline const AstrumColor AstrumColor::Sienna = AstrumColor(0.627f, 0.322f, 0.176f);
inline const AstrumColor AstrumColor::Chocolate = AstrumColor(0.824f, 0.412f, 0.118f);
inline const AstrumColor AstrumColor::Peru = AstrumColor(0.804f, 0.522f, 0.247f);
inline const AstrumColor AstrumColor::Tan = AstrumColor(0.824f, 0.706f, 0.549f);

// === 분홍 계열 ===
inline const AstrumColor AstrumColor::Pink = AstrumColor(1.0f, 0.753f, 0.796f);
inline const AstrumColor AstrumColor::LightPink = AstrumColor(1.0f, 0.714f, 0.757f);
inline const AstrumColor AstrumColor::HotPink = AstrumColor(1.0f, 0.412f, 0.706f);
inline const AstrumColor AstrumColor::DeepPink = AstrumColor(1.0f, 0.078f, 0.576f);
inline const AstrumColor AstrumColor::PaleVioletRed = AstrumColor(0.859f, 0.439f, 0.576f);