#pragma once
#include "../DataManager.hpp"
#include "../../Arcaea/ArcaeaChartManager.hpp"
#include "../../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame {
	class HoldNoteViewObject : public AstrumRectangleObject
	{
	public:
		HoldNoteViewObject(const Arcaea::NoteData& data) {
			height = static_cast<float>(data.Data[1] - data.Data[0]);

			SetRectanglePolygons(AstrumRectanglePolygons::MakeShared(
				NoteWidth,
				height,
				AstrumColor::LightSeaGreen
			));

			Position.SetX(static_cast<float>(LeftX - (NoteWidth * 0.5f) + data.Data[2] * NoteWidth));
			Position.SetY(data.GetStartOffset() + height * 0.5f);
		}

	private:
		float height = 0;
	};
}