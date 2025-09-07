#include "SelectorSceneObject.hpp"
#include "../SceneManager.hpp"
#include "MusicBarListObject.hpp"
#include "MusicThumbnailObject.hpp"

namespace Selector {
	SceneObject::SceneObject() {
		Game::SceneManager::SelectorScene = this;

		SetPositionZ(100);
		AddObject(musicListObject = std::make_shared<MusicBarListObject>());
		musicListObject->SetPositionX(static_cast<float>(AstrumWindow::GetWidth()) * 0.3f);

		AddObject(musicThumbnailObject = std::make_shared<MusicThumbnailObject>());
		musicThumbnailObject->SetPositionX(static_cast<float>(AstrumWindow::GetWidth()) * -0.25f);
	}

	SceneObject::~SceneObject() {
		Game::SceneManager::SelectorScene = nullptr;
	}
}