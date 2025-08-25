#pragma once
#include <memory>
#include "DataManager.hpp"
#include "NoteBoardObject.hpp"
#include "NoteGroupObject.hpp"
#include "../../Astrum/Objects/AstrumPostProcessGroupObject.hpp"

namespace InGame {
	class PlayFieldObject : public AstrumPostProcessGroupObject
	{
	public:
		PlayFieldObject() : AstrumPostProcessGroupObject(DataManager::Instance().GetIllusionConstantBuffer(this)) {
			SetPositionZ(100);

			AddObject(boardObject = std::make_shared<NoteBoardObject>());
			boardObject->SetPositionZ(0);

			AddObject(groupObject = std::make_shared<NoteGroupObject>());
			groupObject->SetPositionZ(-1);

			SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());

			const float halfHeight = static_cast<float>(AstrumWindow::GetHeight()) * 0.5f;
			SetMaterialMesh(AstrumTextureMesh::MakeShared(
				AstrumVector3 { -NoteWidth, halfHeight },
				AstrumVector3{ NoteWidth, halfHeight },
				AstrumVector3{ -3 * NoteWidth, -halfHeight },
				AstrumVector3{ 3 * NoteWidth, -halfHeight }
			));
		}

	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteGroupObject> groupObject = nullptr;
	};
}