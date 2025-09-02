#pragma once
#include <memory>
#include <algorithm>
#include "../../Astrum/Resources/AstrumSound.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"
#include "ArcaeaChart.hpp"
#include "ArcaeaChartParser.hpp"

namespace Arcaea {
	struct MusicData
	{
		MusicData(std::filesystem::path&& folder) {
			name = std::move(folder.filename());
			thumbnailTexture = std::move(AstrumTextureCache::Load(std::filesystem::canonical(folder / L"base.jpg")));
			originSound = std::move(AstrumSound::MakeShared(std::filesystem::canonical(folder / L"base.ogg")));
			
			if (auto from = folder / L"0.aff"; std::filesystem::exists(from)) {
				pastChart = std::make_unique<ChartData>(ChartParser(std::move(from)).ToParse());
			}
			if (auto from = folder / L"1.aff"; std::filesystem::exists(from)) {
				presentChart = std::make_unique<ChartData>(ChartParser(std::move(from)).ToParse());
			}
			if (auto from = folder / L"2.aff"; std::filesystem::exists(from)) {
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
	};
}