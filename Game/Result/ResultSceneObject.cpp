#include "ResultSceneObject.hpp"
#include "../SceneManager.hpp"

namespace Result {
	SceneObject::SceneObject() {
		Game::SceneManager::ResultScene = this;
	}

	SceneObject::~SceneObject() {
		Game::SceneManager::ResultScene = nullptr;
	}
}