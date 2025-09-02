#pragma once
#include <memory>
#include <algorithm>
#include "../../Astrum/Resources/AstrumSound.hpp"
#include "../../Astrum/Resources/AstrumTexture.hpp"
#include "ArcaeaChart.hpp"
#include "ArcaeaChartParser.hpp"

namespace Arcaea {
	struct MusicData
	{
		MusicData(std::filesystem::path folder) {
			auto full = folder.is_absolute() ? folder : (DefaultRelativePath / folder);
			name = std::move(full.filename());
			thumbnailTexture = std::move(AstrumTexture::MakeShared(full / L"base.jpg"));
			originSound = std::move(AstrumSound::MakeShared(full / L"base.ogg"));
			
			if (auto from = full / L"0.aff"; std::filesystem::exists(from)) {
				pastChart = std::make_unique<ChartData>(ChartParser(std::move(from)).ToParse());
			}
			if (auto from = full / L"1.aff"; std::filesystem::exists(from)) {
				presentChart = std::make_unique<ChartData>(ChartParser(std::move(from)).ToParse());
			}
			if (auto from = full / L"2.aff"; std::filesystem::exists(from)) {
				futureChart = std::make_unique<ChartData>(ChartParser(std::move(from)).ToParse());
			}

		}

	public:
		std::wstring name;
		std::shared_ptr<AstrumTexture> thumbnailTexture = nullptr;
		std::shared_ptr<AstrumSound> originSound = nullptr;
		std::unique_ptr<ChartData> pastChart = nullptr;
		std::unique_ptr<ChartData> presentChart = nullptr;
		std::unique_ptr<ChartData> futureChart = nullptr;

	public:
		inline static std::filesystem::path DefaultRelativePath = L"Game/Assets/songs";
	};
}