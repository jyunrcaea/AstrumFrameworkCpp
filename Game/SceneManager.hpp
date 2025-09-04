#pragma once
#include "Loading/LoadingSceneObject.hpp"
#include "InGame/InGameSceneObject.hpp"
#include "Result/ResultSceneObject.hpp"
#include "Selector/SelectorSceneObject.hpp"

namespace Game {
	class SceneManager
	{
	public:
		inline static class Loading::SceneObject* LoadingScene = nullptr;
		inline static class InGame::SceneObject* InGameScene = nullptr;
		inline static class Result::SceneObject* ResultScene = nullptr;
		inline static class Selector::SceneObject* SelectorScene = nullptr;
	};
}