#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame
{
	class NoteBoardObject : public Astrum::RectangleObject
	{
	public:
		NoteBoardObject() : Astrum::RectangleObject(NoteWidth * 4.f, static_cast<float>(Astrum::Window::GetHeight()), Astrum::Color::LightGray) {
		}
	};
}