#pragma once
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include "../Vectors/AstrumVector4.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Singletons/AstrumFramework.hpp"
#include "../Singletons/AstrumDirectInput.hpp"
#include "../Objects/AstrumRectangleObject.hpp"
#include "../Components/AstrumStateComponent.hpp"
#include "../Components/AstrumAnimatorComponent.hpp"
#include "../Animations/AstrumMovementAnimator.hpp"
#include "../Animations/AstrumAnimationFunctions.hpp"
#include "../Singletons/AstrumKeyBinder.hpp"
#include "../Arcaea/ArcaeaChartParser.hpp"

class Program
{
	friend int main();

private:
	void Main() {
		Arcaea::ArcaeaChartParser parser(L"./Assets/songs/infinityheaven/2.aff");
		auto patterns = parser.ToParse();
		
		std::cout << std::format("Audio Offset: {}\n", patterns.AudioOffset);
		for (auto& info : patterns.Notes) {
			std::cout << "Type: ";
			switch (info.NoteType) {
			case Arcaea::ArcaeaNoteType_Arc:
				std::cout << "Arc";
				break;
			case Arcaea::ArcaeaNoteType_Hold:
				std::cout << "Hold";
				break;
			case Arcaea::ArcaeaNoteType_Tap:
				std::cout << "Tap";
				break;
			case Arcaea::ArcaeaNoteType_Trace:
				std::cout << "Trace";
				break;
			default:
				break;
			}
			std::cout << "Data:";
			for (auto v : info.Data) {
				std::cout << ' ' << v;
			}
			std::cout << std::endl;
		}

		//AstrumFramework::Initialize();
		//AstrumFramework::GetRootObject()->AddObjects({

		//});
		//AstrumFramework::Run();
	}
};