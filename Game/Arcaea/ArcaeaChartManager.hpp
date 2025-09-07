#pragma once
#include <iostream>
#include "ArcaeaChartParser.hpp"
#include "ArcaeaMusicData.hpp"
#include "../../Astrum/Singletons/AstrumSingleton.hpp"
#include "../../Astrum/Singletons/AstrumChrono.hpp"
#include "../../Astrum/Resources/AstrumSound.hpp"

namespace Arcaea {
	enum LaneType : unsigned char
	{
		Lane1 = 0,
		Lane2,
		Lane3,
		Lane4,
		SkyNote,
		End,
	};

	class ChartManager : public AstrumSingleton<ChartManager>
	{
		friend class AstrumSingleton<ChartManager>;

	public:
		void Setup(const std::filesystem::path& filePath) {
			Arcaea::ChartParser parser(filePath);
			chart = parser.ToParse();
			FillQueue();
			nextNoteIndex = 0;
		}
		void Setup(const MusicData* data, int level = 0) {
			if (1 == level) chart = std::move(*data->GetPresentChart());
			else if (2 == level) chart = std::move(*data->GetFutureChart());
			else chart = std::move(*data->GetPastChart());

			FillQueue();
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

		const Arcaea::NoteData* PeekNextNote(const LaneType type) {
			auto& q = noteQueue[static_cast<unsigned char>(type)];
			if (false == q.empty()) {
				return &q.front();
			}
			return nullptr;
		}
		std::unique_ptr<Arcaea::NoteData> PopNextNote(const LaneType type) {
			auto& q = noteQueue[static_cast<unsigned char>(type)];
			if (false == q.empty()) {
				auto ret = std::make_unique<Arcaea::NoteData>(std::move(q.front()));
				q.pop();
				return ret;
			}
			return nullptr;
		}
	private:
		Arcaea::ChartData chart;
		int nextNoteIndex = 0;
		float noteSpeed = 1000;
		double playedTime = -1.f;

		std::queue<Arcaea::NoteData> noteQueue[LaneType::End];
		void FillQueue() {
			for(auto& note : chart.Notes) {
				switch (note.NoteType) {
				case Arcaea::NoteType::Tap:
					noteQueue[static_cast<unsigned char>(note.Data[1]) - 1].push(note);
					break;
				case Arcaea::NoteType::Hold:
					noteQueue[static_cast<unsigned char>(note.Data[2]) - 1].push(note);
					break;
				case Arcaea::NoteType::Arc:
				case Arcaea::NoteType::Trace:
					break;
				case Arcaea::NoteType::ArcTap:
					noteQueue[LaneType::SkyNote].push(note);
					break;
				}
			}
		}
	};
}