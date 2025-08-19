#pragma once
#include <memory>
#include "DataManager.hpp"
#include "NoteBoardObject.hpp"
#include "NoteGroupObject.hpp"
#include "../../Components/AstrumConstantBufferComponent.hpp"
#include "../../Buffers/AstrumSimpleConstantBuffer.hpp"
#include "../../Shaders/AstrumShaderSetup.hpp"

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

			AddComponent(constantBuffer = AstrumConstantBufferComponent::MakeShared(
				AstrumSimpleConstantBuffer::MakeShared([this](AstrumConstantBuffer* buffer) {
					buffer->UpdateConstantBuffer(GetAbsoluteRotation());
					buffer->SetPixelShaderConstantBuffer(2);
				}, sizeof(AstrumVector3))
			));

			customShaderPipeline = AstrumShaderSetup::MakeShared();
			customShaderPipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
			customShaderPipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
			customShaderPipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Tests/CustomColorMesh.fx", "ColorMeshVS");
			customShaderPipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Tests/CustomColorMesh.fx", "ColorMeshPS");
		}

		virtual void Draw() override {
			auto& defaultShaderPipeline = AstrumRenderer::Instance().DefaultShapeShaderPipeline;

			std::shared_ptr<IAstrumShaderSetup> temp{ std::move(defaultShaderPipeline) };
			defaultShaderPipeline = customShaderPipeline;
			AstrumGroupObject::Draw();
			defaultShaderPipeline = std::move(temp);
		}
	private:
		std::shared_ptr<NoteBoardObject> boardObject = nullptr;
		std::shared_ptr<NoteGroupObject> groupObject = nullptr;
		std::shared_ptr<AstrumConstantBufferComponent> constantBuffer = nullptr;
		std::shared_ptr<AstrumShaderSetup> customShaderPipeline = nullptr;
	};
}