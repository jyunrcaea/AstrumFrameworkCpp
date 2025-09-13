#pragma once
#include <memory>
#include "DataManager.hpp"
#include "NoteBoardObject.hpp"
#include "ViewModels/NoteViewModelObject.hpp"
#include "Views/LaneObject.hpp"
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

			//SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());
			const auto [vertices, indices] = DataManager::Instance().GetIllusionMeshData();
			SetMaterialMesh(customMesh = AstrumTextureMesh::MakeShared(vertices, indices));

			AddObjects({
				lanes[0] = std::make_shared<LaneObject>(0),
				lanes[1] = std::make_shared<LaneObject>(1),
				lanes[2] = std::make_shared<LaneObject>(2),
				lanes[3] = std::make_shared<LaneObject>(3)
			});
		}

	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteViewModelObject> noteViewModelObject = nullptr;
		std::shared_ptr<LaneObject> lanes[4] = { nullptr, nullptr, nullptr, nullptr };
		std::shared_ptr<AstrumTextureMesh> customMesh = nullptr;
	};
}