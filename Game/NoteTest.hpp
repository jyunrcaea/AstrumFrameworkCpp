#pragma once
#include <iostream>
#include <format>
#include <string>
#include <memory>
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "InGame/SceneObject.hpp"
#include "../Astrum/Singletons/AstrumTextureCache.hpp"

class Program
{
	friend int main();

private:
	static void Main() {
		AstrumFramework::Initialize();
		AstrumChrono::SetFramerate(300);

		AstrumTextureCache::SetDefaultRelativeDirectory("Game/Assets/img");

		AstrumFramework::GetRootObject()->AddObject(
			std::make_shared<InGame::SceneObject>()
		);
#if _DEBUG
		Arcaea::ChartManager::Instance().PrintChart();
#endif
		AstrumFramework::Run();
	}
};