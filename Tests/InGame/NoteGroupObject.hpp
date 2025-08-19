#pragma once
#include "DataManager.hpp"
#include "NoteObject.hpp"
#include "HoldNoteObject.hpp"
#include "ArcObject.hpp"
#include "TraceObject.hpp"
#include "SkyNoteObject.hpp"

namespace InGame {
	class NoteGroupObject : public AstrumGroupObject
	{
	public:
		NoteGroupObject() {
			Arcaea::ChartManager::Instance().Setup(L"./Assets/songs/goodtek/2.aff");

			SetPositionZ(10);

			Position.SetY(2000.f);
			customShaderPipeline = AstrumShaderSetup::MakeShared();
			customShaderPipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
			customShaderPipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
			customShaderPipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Tests/CustomColorMesh.fx", "ColorMeshVS");
			customShaderPipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Tests/CustomColorMesh.fx", "ColorMeshPS");
		}

		virtual void Prepare() override {
			for (const auto& data : Arcaea::ChartManager::Instance().GetNoteData()) {
				GenerateNote(data);
			}
			AstrumGroupObject::Prepare();
		}

		virtual void Update() override {
			Position.AddY(static_cast<float>(AstrumChrono::GetDeltaTime() * -1000.0));

			AstrumGroupObject::Update();
		}

	private:
		void GenerateNote(const Arcaea::NoteData& data) {
			switch (data.NoteType) {
			case Arcaea::NoteType::Tap:
				AddObject(std::make_shared<NoteObject>(data));
				break;
			case Arcaea::NoteType::Hold:
				AddObject(std::make_shared<HoldNoteObject>(data));
				break;
			case Arcaea::NoteType::Arc:
				AddObject(std::make_shared<ArcObject>(data));
				break;
			case Arcaea::NoteType::Trace:
				AddObject(std::make_shared<TraceObject>(data));
				break;
			case Arcaea::NoteType::ArcTap:
				AddObject(std::make_shared<SkyNoteObject>(data));
				break;
			}
		}

		virtual void Draw() override {
			auto& defaultShaderPipeline = AstrumRenderer::Instance().DefaultShapeShaderPipeline;

			std::shared_ptr<IAstrumShaderSetup> temp{ std::move(defaultShaderPipeline) };
			defaultShaderPipeline = customShaderPipeline;
			AstrumGroupObject::Draw();
			defaultShaderPipeline = std::move(temp);
		}

	private:
		std::shared_ptr<AstrumRectangleObject> board = nullptr;
		std::shared_ptr<AstrumShaderSetup> customShaderPipeline;
	};
}