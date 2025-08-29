#pragma once
#include "../DataManager.hpp"
#include "../Views/NoteViewObject.hpp"
#include "../Views/HoldNoteViewObject.hpp"
#include "../Views/ArcViewObject.hpp"
#include "../Views/TraceLineViewObject.hpp"
#include "../Views/SkyNoteViewObject.hpp"
#include "../../Arcaea/ArcaeaChartManager.hpp"
#include "../../../Astrum/Singletons/AstrumChrono.hpp"
#include "../../../Astrum/Objects/AstrumGroupObject.hpp"

namespace InGame {
	class NoteViewModelObject : public AstrumGroupObject
	{
	public:
		NoteViewModelObject() {
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
		void GenerateNote(const Arcaea::NoteData& data);
	};
}