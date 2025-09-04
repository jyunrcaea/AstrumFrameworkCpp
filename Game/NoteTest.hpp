#pragma once
#include <iostream>
#include <format>
#include <string>
#include <memory>
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "../Astrum/Singletons/AstrumTextureCache.hpp"
#include "InGame/SceneObject.hpp"
#include  "Selector/SceneObject.hpp"

class Program
{
	friend int main();

private:
	static void Main() {
		AstrumFramework::Initialize();
		AstrumChrono::SetFramerate(300);

		AstrumFontsCache::SetDefaultRelativeDirectory(L"Game/Assets/fonts");
		AstrumTextureCache::SetDefaultRelativeDirectory(L"Game/Assets/img");

		AstrumFramework::GetRootObject()->AddObject(
			//std::make_shared<InGame::SceneObject>()
			std::make_shared<Selector::SceneObject>()
		);
#if _DEBUG
		Arcaea::ChartManager::Instance().PrintChart();
#endif
		AstrumFramework::Run();
	}
};