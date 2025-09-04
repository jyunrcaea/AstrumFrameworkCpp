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
		MusicData(std::filesystem::path&& path) {
			name = std::move(path.filename());
			folder = std::filesystem::canonical(std::move(path));			
		}

	public:
		const std::wstring& GetName() const { return name; }
		const std::filesystem::path& GetFolderPath() const { return folder; }
		std::shared_ptr<AstrumTexture> GetThumbnailTexture() const { return AstrumTextureCache::Load(folder / L"base.jpg"); }
		std::shared_ptr<AstrumSound> GetSound() const { return AstrumSound::MakeShared(folder / L"base.ogg"); }
		std::unique_ptr<Arcaea::ChartData> GetPastChart() const { return std::make_unique<ChartData>(ChartParser(folder / L"0.aff").ToParse()); }
		std::unique_ptr<Arcaea::ChartData> GetPresentChart() const { return std::make_unique<ChartData>(ChartParser(folder / L"1.aff").ToParse()); }
		std::unique_ptr<Arcaea::ChartData> GetFutureChart() const { return std::make_unique<ChartData>(ChartParser(folder / L"2.aff").ToParse()); }

	private:
		std::wstring name;
		std::filesystem::path folder;
	};
}