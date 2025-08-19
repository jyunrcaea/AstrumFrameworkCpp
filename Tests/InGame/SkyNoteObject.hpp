#pragma once
#include "DataManager.hpp"
#include "../../Objects/AstrumRectangleObject.hpp"

namespace InGame {
	class SkyNoteObject : public AstrumRectangleObject
	{
	public:
		SkyNoteObject(const Arcaea::NoteData& data) : AstrumRectangleObject(NoteWidth, 30, AstrumColor::Aquamarine) {
			const float startX = static_cast<float>(LeftX + (LeftX / 2.f) + (NoteWidth * 4.f) * data.Data[1]);
			Position.SetX(startX);

			Position.SetY(data.GetStartOffset() + 15);
		}

	private:
		float height = 0;
	};
}