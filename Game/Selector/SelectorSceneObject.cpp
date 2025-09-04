#include "SelectorSceneObject.hpp"
#include "../SceneManager.hpp"

namespace Selector {
	SceneObject::SceneObject() {
		Game::SceneManager::SelectorScene = this;

		SetPositionZ(100);
		AddObject(musicListObject = std::make_shared<MusicBarListObject>());
		musicListObject->SetPositionX(static_cast<float>(AstrumWindow::GetWidth()) * 0.3f);
	}

	SceneObject::~SceneObject() {
		Game::SceneManager::SelectorScene = nullptr;
	}
}