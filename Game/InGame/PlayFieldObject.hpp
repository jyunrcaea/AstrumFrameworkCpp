#pragma once
#include <memory>
#include "DataManager.hpp"
#include "NoteBoardObject.hpp"
#include "NoteGroupObject.hpp"

namespace InGame {
	class PlayFieldObject : public AstrumGroupObject
	{
	public:
		PlayFieldObject() {
			SetPositionZ(100);

			AddObject(boardObject = std::make_shared<NoteBoardObject>());
			boardObject->SetPositionZ(0);

			AddObject(groupObject = std::make_shared<NoteGroupObject>());
			groupObject->SetPositionZ(-1);
		}

	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteGroupObject> groupObject = nullptr;
	};
}