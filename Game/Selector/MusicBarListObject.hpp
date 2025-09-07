#pragma once
#include <vector>
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Singletons/AstrumRawInput.hpp"
#include "../Arcaea/ArcaeaMusicDataManager.hpp"
#include "MusicBarObject.hpp"

namespace Selector {
	class MusicBarListObject : public AstrumGroupObject
	{
	public:
		MusicBarListObject() {
			SetPositionZ(100);
			float offsetY = 0, zIndex = 0;
			const float paddingY = static_cast<float>(AstrumTextureCache::Load("songselect/song_cell_right_world.png")->GetHeight());
			for (const auto& data : Arcaea::MusicDataManager::GetMusics()) {
				auto child = std::make_shared<MusicBarObject>(data);
				AddObject(child);
				child->SetPositionY(offsetY);
				child->SetPositionZ(zIndex);
				offsetY -= paddingY;
				zIndex += 1.f;
			}
		}

		virtual void Update() override {
			if (auto wheel = AstrumRawInput::GetMouseWheelMovement(); 0 != wheel) {
				Position.AddY(static_cast<float>(wheel * -100));
			}
			if (AstrumRawInput::IsMouseClickNow()) {
				std::cout << AstrumRawInput::GetMousePosition() << '\n';
				std::cout << GetObjectList()[0].GetAbsolutePosition() << std::endl;
			}

			AstrumGroupObject::Update();
		}

	private:
	};
}