#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"
#include "../Arcaea/ArcaeaChart.hpp"

namespace InGame {
	class NoteObject : public AstrumRectangleObject
	{
	public:
		NoteObject(const Arcaea::NoteData& data) : AstrumRectangleObject(NoteWidth, 40, AstrumColor::SkyBlue) {
			Position.SetX(static_cast<float>(LeftX + (NoteWidth / 2.f) + data.Data[1] * NoteWidth));
			Position.SetY(data.GetStartOffset() + 20);
		}
	};
}