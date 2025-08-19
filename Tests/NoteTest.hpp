#pragma once
#include <iostream>
#include <format>
#include <string>
#include <memory>
#include "../Singletons/AstrumFramework.hpp"
#include "InGame/SceneObject.hpp"

class Program
{
	friend int main();

private:
	static void Main() {
		AstrumFramework::Initialize();
		AstrumFramework::GetRootObject()->AddObject(
			std::make_shared<InGame::SceneObject>()
		);
#if _DEBUG
		Arcaea::ChartManager::Instance().PrintChart();
#endif
		AstrumFramework::Run();
	}
};