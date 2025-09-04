#include "LoadingSceneObject.hpp"
#include "../SceneManager.hpp"

namespace Loading {
	SceneObject::SceneObject() {
		Game::SceneManager::LoadingScene = this;

		AddObject(slideObject = std::make_shared<SlideBackgroundObject>());
	}

	SceneObject::~SceneObject() {
		Game::SceneManager::LoadingScene = nullptr;
	}
}