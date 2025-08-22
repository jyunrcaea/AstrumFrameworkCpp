#pragma once
#include "../Vectors/AstrumVector4.hpp"

namespace Astrum
{
	struct Color {
		float Red, Green, Blue, Alpha;

		constexpr Color(float r = 0, float g = 0, float b = 0, float a = 1.0f)
			: Red(r), Green(g), Blue(b), Alpha(a) {
		}

		operator Vector4() const { return Vector4(Red, Green, Blue, Alpha); }
		explicit Color(const Vector4& vec) : Red(vec.X), Green(vec.Y), Blue(vec.Z), Alpha(vec.W) { }

		static const Color White;
		static const Color Black;
		static const Color Gray;
		static const Color Silver;
		static const Color LightGray;
		static const Color DarkGray;

		// === 보라 계열 ===
		static const Color Purple;
		static const Color Violet;
		static const Color Lilac;
		static const Color Lavender;
		static const Color Orchid;
		static const Color Plum;
		static const Color Amethyst;

		// === 남보라 / 파랑 계열 ===
		static const Color Periwinkle;
		static const Color LightPeriwinkle;
		static const Color PureBlue;
		static const Color LightBlue;
		static const Color SkyBlue;
		static const Color RoyalBlue;
		static const Color MidnightBlue;
		static const Color Navy;
		static const Color Indigo;

		// === 청록 계열 ===
		static const Color Cyan;
		static const Color Teal;
		static const Color Turquoise;
		static const Color LightSeaGreen;
		static const Color Aquamarine;
		static const Color MediumTurquoise;
		static const Color PaleTurquoise;
		static const Color DarkCyan;

		// === 초록 계열 ===
		static const Color Lime;
		static const Color PureGreen;
		static const Color ForestGreen;
		static const Color DarkGreen;
		static const Color MintGreen;

		// === 연두 계열 ===
		static const Color YellowGreen;
		static const Color GreenYellow;
		static const Color Chartreuse;
		static const Color GrassGreen;
		static const Color YellowishGreen;

		// === 노랑 계열 ===
		static const Color Yellow;
		static const Color Turbo;
		static const Color MoonYellow;
		static const Color VividYellow;
		static const Color GoldenYellow;
		static const Color Lemon;
		static const Color Mustard;

		// === 주황 계열 ===
		static const Color Orange;
		static const Color DarkOrange;
		static const Color Coral;
		static const Color Tomato;
		static const Color Peach;

		// === 빨강 계열 ===
		static const Color PureRed;
		static const Color DarkRed;
		static const Color Crimson;
		static const Color Firebrick;
		static const Color Scarlet;

		// === 갈색 계열 ===
		static const Color Brown;
		static const Color SaddleBrown;
		static const Color Sienna;
		static const Color Chocolate;
		static const Color Peru;
		static const Color Tan;

		// === 분홍 계열 ===
		static const Color Pink;
		static const Color LightPink;
		static const Color HotPink;
		static const Color DeepPink;
		static const Color PaleVioletRed;
	};

	inline constexpr Color Color::White = Color(1.0f, 1.0f, 1.0f);
	inline constexpr Color Color::Black = Color(0.0f, 0.0f, 0.0f);
	inline constexpr Color Color::Gray = Color(0.498f, 0.498f, 0.498f);
	inline constexpr Color Color::Silver = Color(0.753f, 0.753f, 0.753f);
	inline constexpr Color Color::LightGray = Color(0.827f, 0.827f, 0.827f);
	inline constexpr Color Color::DarkGray = Color(0.247f, 0.247f, 0.247f);

	// === 보라 계열 ===
	inline constexpr Color Color::Purple = Color(0.502f, 0.0f, 0.502f);
	inline constexpr Color Color::Violet = Color(0.498f, 0.0f, 1.0f);
	inline constexpr Color Color::Lilac = Color(0.784f, 0.635f, 0.784f);
	inline constexpr Color Color::Lavender = Color(0.902f, 0.902f, 1.0f);
	inline constexpr Color Color::Orchid = Color(0.855f, 0.439f, 0.839f);
	inline constexpr Color Color::Plum = Color(0.867f, 0.627f, 0.867f);
	inline constexpr Color Color::Amethyst = Color(0.6f, 0.4f, 0.8f);

	// === 남보라 / 파랑 계열 ===
	inline constexpr Color Color::Periwinkle = Color(0.502f, 0.502f, 1.0f);
	inline constexpr Color Color::LightPeriwinkle = Color(0.8f, 0.8f, 1.0f);
	inline constexpr Color Color::PureBlue = Color(0.0f, 0.0f, 1.0f);
	inline constexpr Color Color::LightBlue = Color(0.678f, 0.847f, 0.902f);
	inline constexpr Color Color::SkyBlue = Color(0.529f, 0.808f, 0.922f);
	inline constexpr Color Color::RoyalBlue = Color(0.255f, 0.412f, 0.882f);
	inline constexpr Color Color::MidnightBlue = Color(0.098f, 0.098f, 0.439f);
	inline constexpr Color Color::Navy = Color(0.0f, 0.0f, 0.502f);
	inline constexpr Color Color::Indigo = Color(0.294f, 0.0f, 0.51f);

	// === 청록 계열 ===
	inline constexpr Color Color::Cyan = Color(0.0f, 1.0f, 1.0f);
	inline constexpr Color Color::Teal = Color(0.0f, 0.502f, 0.502f);
	inline constexpr Color Color::Turquoise = Color(0.251f, 0.878f, 0.816f);
	inline constexpr Color Color::LightSeaGreen = Color(0.125f, 0.698f, 0.667f);
	inline constexpr Color Color::Aquamarine = Color(0.498f, 1.0f, 0.831f);
	inline constexpr Color Color::MediumTurquoise = Color(0.282f, 0.82f, 0.8f);
	inline constexpr Color Color::PaleTurquoise = Color(0.686f, 0.933f, 0.933f);
	inline constexpr Color Color::DarkCyan = Color(0.0f, 0.545f, 0.545f);

	// === 초록 계열 ===
	inline constexpr Color Color::Lime = Color(0.0f, 1.0f, 0.0f);
	inline constexpr Color Color::PureGreen = Color(0.0f, 0.502f, 0.0f);
	inline constexpr Color Color::ForestGreen = Color(0.133f, 0.545f, 0.133f);
	inline constexpr Color Color::DarkGreen = Color(0.0f, 0.392f, 0.0f);
	inline constexpr Color Color::MintGreen = Color(0.596f, 1.0f, 0.596f);

	// === 연두 계열 ===
	inline constexpr Color Color::YellowGreen = Color(0.604f, 0.804f, 0.196f);
	inline constexpr Color Color::GreenYellow = Color(0.678f, 1.0f, 0.184f);
	inline constexpr Color Color::Chartreuse = Color(0.498f, 1.0f, 0.0f);
	inline constexpr Color Color::GrassGreen = Color(0.459f, 0.651f, 0.290f);
	inline constexpr Color Color::YellowishGreen = Color(0.627f, 0.69f, 0.212f);

	// === 노랑 계열 ===
	inline constexpr Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
	inline constexpr Color Color::Turbo = Color(1.0f, 0.8f, 0.129f);
	inline constexpr Color Color::MoonYellow = Color(0.941f, 0.769f, 0.125f);
	inline constexpr Color Color::VividYellow = Color(1.0f, 0.89f, 0.008f);
	inline constexpr Color Color::GoldenYellow = Color(1.0f, 0.549f, 0.0f);
	inline constexpr Color Color::Lemon = Color(1.0f, 0.973f, 0.0f);
	inline constexpr Color Color::Mustard = Color(1.0f, 0.859f, 0.345f);

	// === 주황 계열 ===
	inline constexpr Color Color::Orange = Color(1.0f, 0.498f, 0.0f);
	inline constexpr Color Color::DarkOrange = Color(1.0f, 0.549f, 0.0f);
	inline constexpr Color Color::Coral = Color(1.0f, 0.498f, 0.314f);
	inline constexpr Color Color::Tomato = Color(1.0f, 0.388f, 0.278f);
	inline constexpr Color Color::Peach = Color(1.0f, 0.855f, 0.725f);

	// === 빨강 계열 ===
	inline constexpr Color Color::PureRed = Color(1.0f, 0.0f, 0.0f);
	inline constexpr Color Color::DarkRed = Color(0.545f, 0.0f, 0.0f);
	inline constexpr Color Color::Crimson = Color(0.863f, 0.078f, 0.235f);
	inline constexpr Color Color::Firebrick = Color(0.698f, 0.133f, 0.133f);
	inline constexpr Color Color::Scarlet = Color(1.0f, 0.141f, 0.0f);

	// === 갈색 계열 ===
	inline constexpr Color Color::Brown = Color(0.647f, 0.165f, 0.165f);
	inline constexpr Color Color::SaddleBrown = Color(0.545f, 0.271f, 0.075f);
	inline constexpr Color Color::Sienna = Color(0.627f, 0.322f, 0.176f);
	inline constexpr Color Color::Chocolate = Color(0.824f, 0.412f, 0.118f);
	inline constexpr Color Color::Peru = Color(0.804f, 0.522f, 0.247f);
	inline constexpr Color Color::Tan = Color(0.824f, 0.706f, 0.549f);

	// === 분홍 계열 ===
	inline constexpr Color Color::Pink = Color(1.0f, 0.753f, 0.796f);
	inline constexpr Color Color::LightPink = Color(1.0f, 0.714f, 0.757f);
	inline constexpr Color Color::HotPink = Color(1.0f, 0.412f, 0.706f);
	inline constexpr Color Color::DeepPink = Color(1.0f, 0.078f, 0.576f);
	inline constexpr Color Color::PaleVioletRed = Color(0.859f, 0.439f, 0.576f);
}