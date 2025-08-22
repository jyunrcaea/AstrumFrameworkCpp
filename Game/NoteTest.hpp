#pragma once
#include <iostream>
#include <format>
#include <string>
#include <memory>
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "InGame/SceneObject.hpp"

class Program
{
	friend int main();

private:
	static void Main() {
		using namespace Astrum;
		Framework::Initialize();
		Chrono::SetFramerate(300);
		Framework::GetRootObject()->AddObject(
			std::make_shared<InGame::SceneObject>()
		);
#if _DEBUG
		Arcaea::ChartManager::Instance().PrintChart();
#endif
		Framework::Run();
	}
};