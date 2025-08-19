#pragma once
#include "DataManager.hpp"

namespace InGame
{
	class NoteBoardObject : public AstrumRectangleObject
	{
	public:
		NoteBoardObject() 
			: AstrumRectangleObject(NoteWidth * 4.f, AstrumWindow::GetHeight()) {}
	};
}