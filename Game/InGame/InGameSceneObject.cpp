#include "InGameSceneObject.hpp"
#include "../SceneManager.hpp"

namespace InGame {
	SceneObject::SceneObject() {
		Game::SceneManager::InGameScene = this;

		SetPositionZ(100);
		AddObject(std::make_shared<PlayFieldObject>());
	}

	SceneObject::~SceneObject() {
		Game::SceneManager::InGameScene = nullptr;
	}
}