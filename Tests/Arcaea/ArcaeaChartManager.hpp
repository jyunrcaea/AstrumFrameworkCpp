#pragma once
#include <iostream>
#include "ArcaeaChartParser.hpp"
#include "../../Singletons/AstrumSingleton.hpp"
#include "../../Singletons/AstrumChrono.hpp"
#include "../../Resources/AstrumSound.hpp"

namespace Arcaea {
	class ChartManager : public AstrumSingleton<ChartManager>
	{
		friend class AstrumSingleton<ChartManager>;

	public:
		void Setup(const std::filesystem::path& filePath) {
			Arcaea::ChartParser parser(filePath);
			chart = parser.ToParse();
			nextNoteIndex = 0;
		}

		void Play(const std::filesystem::path& audioPath) {
			AstrumSound(audioPath).Play();
			playedTime = AstrumChrono::GetRunningTime() - (chart.AudioOffset * 0.001);
		}

		const Arcaea::ChartData& GetChart() {
			return chart;
		}

		const std::vector<Arcaea::NoteData>& GetNoteData() const {
			return chart.Notes;
		}

		float GetCurrentOffset() const {
			return static_cast<float>(AstrumChrono::GetRunningTime() - playedTime) * 1000.f;
		}

		float GetNoteSpeed() const {
			return noteSpeed;
		}

		void PrintChart() const {
			std::cout << std::format("Audio Offset: {}\n", chart.AudioOffset);
			for (auto& info : chart.Notes) {
				std::cout << "Type: ";
				switch (info.NoteType) {
				case Arcaea::NoteType::Arc:
					std::cout << "Arc";
					break;
				case Arcaea::NoteType::Hold:
					std::cout << "Hold";
					break;
				case Arcaea::NoteType::Tap:
					std::cout << "Tap";
					break;
				case Arcaea::NoteType::Trace:
					std::cout << "Trace";
					break;
				case Arcaea::NoteType::ArcTap:
					std::cout << "ArcTap";
					break;
				default:
					break;
				}
				std::cout << ", Data:";
				for (auto v : info.Data) {
					std::cout << ' ' << v;
				}
				std::cout << std::endl;
			}
		}

	private:
		Arcaea::ChartData chart;
		int nextNoteIndex = 0;
		double playedTime = -1.f;
		float noteSpeed = 1000;
	};
}