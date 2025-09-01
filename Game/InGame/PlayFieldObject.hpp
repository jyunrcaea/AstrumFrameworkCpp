#pragma once
#include <memory>
#include "DataManager.hpp"
#include "NoteBoardObject.hpp"
#include "ViewModels/NoteViewModelObject.hpp"
#include "../../Astrum/Objects/AstrumPostProcessGroupObject.hpp"

namespace InGame {
	class PlayFieldObject : public AstrumPostProcessGroupObject
	{
	public:
		PlayFieldObject() : AstrumPostProcessGroupObject(DataManager::Instance().GetIllusionConstantBuffer(this)) {
			SetPositionZ(100);

			AddObject(boardObject = std::make_shared<NoteBoardObject>());
			boardObject->SetPositionZ(0);

			AddObject(noteViewModelObject = std::make_shared<NoteViewModelObject>());
			noteViewModelObject->SetPositionZ(-1);

			SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());
		}

	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteViewModelObject> noteViewModelObject = nullptr;
	};
}