#pragma once
#include "DataManager.hpp"
#include "NoteObject.hpp"
#include "HoldNoteObject.hpp"
#include "ArcObject.hpp"
#include "TraceObject.hpp"
#include "SkyNoteObject.hpp"
#include "../Arcaea/ArcaeaChartManager.hpp"
#include "../Astrum/Singletons/AstrumChrono.hpp"

namespace InGame {
	class NoteGroupObject : public AstrumGroupObject
	{
	public:
		NoteGroupObject() {
			Arcaea::ChartManager::Instance().Setup(L"./Game/Assets/songs/goodtek/2.aff");

			SetPositionZ(10);

			Position.SetY(2000.f);
		}

		virtual void Prepare() override {
			for (const auto& data : Arcaea::ChartManager::Instance().GetNoteData()) {
				GenerateNote(data);
			}
			AstrumGroupObject::Prepare();
		}

		virtual void Update() override {
			Position.AddY(static_cast<float>(AstrumChrono::GetDeltaTime() * -1000.0));

			AstrumGroupObject::Update();
		}

	private:
		void GenerateNote(const Arcaea::NoteData& data) {
			switch (data.NoteType) {
			case Arcaea::NoteType::Tap:
				AddObject(std::make_shared<NoteObject>(data));
				break;
			case Arcaea::NoteType::Hold:
				AddObject(std::make_shared<HoldNoteObject>(data));
				break;
			case Arcaea::NoteType::Arc:
				AddObject(std::make_shared<ArcObject>(data));
				break;
			case Arcaea::NoteType::Trace:
				AddObject(std::make_shared<TraceObject>(data));
				break;
			case Arcaea::NoteType::ArcTap:
				AddObject(std::make_shared<SkyNoteObject>(data));
				break;
			}
		}
	private:
	};
}