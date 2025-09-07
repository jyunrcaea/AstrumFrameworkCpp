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

			//SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());
			
			const auto [halfWidth, halfHeight] = AstrumRenderer::Instance().GetHalfResolution();
			constexpr float Left = NoteWidth * -2.f;
			constexpr float Right = NoteWidth * 2.f;
			constexpr float ShrinkScale = 0.25f;
			constexpr float MinusCeilingY = 100.f;
			constexpr int n = 1000;

			std::vector<AstrumTextureVertex> vertices;
			vertices.reserve(static_cast<int>(n + 1) * 2);
			for (int i = 0; i <= n; i++) {
				const float percent = i / static_cast<float>(n);
				vertices.emplace_back(AstrumVector3{ std::lerp(Left * ShrinkScale, Right * ShrinkScale, percent), static_cast<float>(halfHeight) - MinusCeilingY, 0 }, AstrumVector2{ percent, 0 });
			}
			for (int i = 0; i <= n; i++) {
				const float percent = i / static_cast<float>(n);
				vertices.emplace_back(AstrumVector3{ static_cast<float>(std::lerp(-halfWidth, halfWidth, percent)), -static_cast<float>(halfHeight), 0 }, AstrumVector2{ percent, 1 });
			}

			std::vector<unsigned short> indices;
			indices.reserve((n+1) * 6);
			for (unsigned short i = 0; i < n; i++) {
				indices.push_back(i + 1);
				indices.push_back(i + n + 1);
				indices.push_back(i);

				indices.push_back(i + n + 2);
				indices.push_back(i + n + 1);
				indices.push_back(i + 1);
			}

			SetMaterialMesh(customMesh = AstrumTextureMesh::MakeShared(vertices, indices));
		}

	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteViewModelObject> noteViewModelObject = nullptr;
		std::shared_ptr<AstrumTextureMesh> customMesh = nullptr;
	};
}