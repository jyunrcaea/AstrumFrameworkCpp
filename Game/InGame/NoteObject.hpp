#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"
#include "../Arcaea/ArcaeaChart.hpp"

namespace InGame {
	class NoteObject : public Astrum::RectangleObject
	{
	public:
		NoteObject(const Arcaea::NoteData& data) : Astrum::RectangleObject(NoteWidth, 40, Astrum::Color::SkyBlue) {
			Position.SetX(static_cast<float>(LeftX + (NoteWidth / 2.f) + data.Data[1] * NoteWidth));
			Position.SetY(data.GetStartOffset() + 20);
		}
	};
}