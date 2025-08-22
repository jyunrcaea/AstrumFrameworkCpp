#pragma once
#include "DataManager.hpp"
#include "../Arcaea/ArcaeaChartManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame {
	class HoldNoteObject : public Astrum::RectangleObject
	{
	public:
		HoldNoteObject(const Arcaea::NoteData& data) {
			using namespace Astrum;
			height = static_cast<float>(data.Data[1] - data.Data[0]);

			SetRectanglePolygons(RectanglePolygons::MakeShared(
				200,
				height,
				Color::LightSeaGreen
			));

			Position.SetX(static_cast<float>(LeftX + (NoteWidth / 2.f) + data.Data[2] * NoteWidth));
			Position.SetY(data.GetStartOffset() + height / 2.f);
		}

	private:
		float height = 0;
	};
}