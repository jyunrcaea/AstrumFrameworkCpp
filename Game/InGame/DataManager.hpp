#pragma once
#include "../Arcaea/ArcaeaMusicData.hpp"
#include "../../Astrum/Shaders/AstrumShaderSetup.hpp"
#include "../../Astrum/Components/AstrumConstantBufferComponent.hpp"
#include "../../Astrum/Objects/IAstrumObject.hpp"
#include "../../Astrum/Buffers/AstrumSimpleConstantBuffer.hpp"
#include "../../Astrum/Singletons/AstrumShaderCache.hpp"
#include "../../Astrum/Singletons/AstrumChrono.hpp"
#include "../../Astrum/Vectors/AstrumVector4.hpp"
#include "../../Astrum/Meshes/AstrumTextureMesh.hpp"

namespace InGame {
	constexpr float NoteWidth = 250.f;
	constexpr float LeftX = NoteWidth * -3.f;
	constexpr float SkyNoteY = 300.f;

	class DataManager : public AstrumSingleton<DataManager>
	{
		friend class AstrumSingleton<DataManager>;
	public:
		std::shared_ptr< AstrumShaderSetup> GetIllusionShader() {
			if (nullptr == shader) {
				shader = AstrumShaderSetup::MakeShared();
				AstrumShaderCache::SetDefaultRelativeDirectory("./Game/Shaders/");
				shader->VertexShader = AstrumShaderCache::LoadVertexShader(L"Illusion.fx", "IllusionVS");
				shader->PixelShader = AstrumShaderCache::LoadPixelShader(L"Illusion.fx", "IllusionPS");
				shader->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
				shader->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);
			}
			return shader;
		}

		std::shared_ptr<AstrumSimpleConstantBuffer> GetIllusionConstantBuffer(IAstrumObject* owner) {
			return AstrumSimpleConstantBuffer::MakeShared([this, owner](AstrumConstantBuffer* buffer) {
				AstrumVector4 data{ static_cast<float>(AstrumWindow::GetWidth()), static_cast<float>(AstrumWindow::GetHeight()), owner->GetRotation().GetZ(), 0.3f };
				buffer->UpdateConstantBuffer(data);
				buffer->SetVertexShaderConstantBuffer(2);
			}, sizeof(AstrumVector4));
		}

		std::pair<std::vector<AstrumTextureVertex>, std::vector<unsigned short>> GetIllusionMeshData() {
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
			indices.reserve((n + 1) * 6);
			for (unsigned short i = 0; i < n; i++) {
				indices.push_back(i + 1);
				indices.push_back(i + n + 1);
				indices.push_back(i);

				indices.push_back(i + n + 2);
				indices.push_back(i + n + 1);
				indices.push_back(i + 1);
			}

			// maybe it is apply RNVO in cpp 17 or higher, right?
			return { vertices, indices };
		}

		const Arcaea::MusicData* CurrentMusic = nullptr;
	private:
		std::shared_ptr<AstrumShaderSetup> shader = nullptr;
	};
}