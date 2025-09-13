#pragma once
#include "../DataManager.hpp"
#include "../../../Astrum/Objects/AstrumRectangleObject.hpp"
#include "../../../Astrum/Singletons/AstrumRawInput.hpp"

namespace InGame {
	class LaneObject : public AstrumRectangleObject
	{
	public:
		// lane: 0~3
		LaneObject(int lane)
			: AstrumRectangleObject(NoteWidth, static_cast<float>(AstrumWindow::GetHeight()), AstrumColor{0.3f, 0.3f, 0.8f, 0.5f}), lane(lane) {
			Position.SetX(LeftX + (static_cast<float>(lane) + 0.5f) *NoteWidth);
			Position.SetZ(-10);
		}

		virtual void Update() override {
			SetVisible(AstrumRawInput::IsKeyPressed(DataManager::Instance().LaneBindKey[lane]));

			AstrumRectangleObject::Update();
		}

	private:
		int lane;
	};
}