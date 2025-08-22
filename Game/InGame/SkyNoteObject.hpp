#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame {
	class SkyNoteObject : public Astrum::RectangleObject
	{
	public:
		SkyNoteObject(const Arcaea::NoteData& data) : Astrum::RectangleObject(NoteWidth, 30, Astrum::Color::Aquamarine) {
			const float startX = static_cast<float>(LeftX + (LeftX / 2.f) + (NoteWidth * 4.f) * data.Data[1]);
			Position.SetX(startX);

			Position.SetY(data.GetStartOffset() + 15);
		}

	private:
		float height = 0;
	};
}