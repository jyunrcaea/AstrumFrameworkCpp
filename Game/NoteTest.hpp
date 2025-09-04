#pragma once
#include <iostream>
#include <format>
#include <string>
#include <memory>
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "../Astrum/Singletons/AstrumTextureCache.hpp"
#include "InGame/InGameSceneObject.hpp"
#include  "Selector/SelectorSceneObject.hpp"
#include "Loading/LoadingSceneObject.hpp"
#include "SceneManager.hpp"

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
			std::make_shared<Loading::SceneObject>()
		);
		Game::SceneManager::LoadingScene->LoadScene([](auto*) {
			AstrumFramework::GetRootObject()->AddObject(
				std::make_shared<Selector::SceneObject>()
			);
		});
		AstrumFramework::Run();
	}
};