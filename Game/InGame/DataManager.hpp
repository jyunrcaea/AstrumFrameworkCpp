#pragma once
#include "../../Astrum/Shaders/AstrumShaderSetup.hpp"
#include "../../Astrum/Components/AstrumConstantBufferComponent.hpp"
#include "../../Astrum/Objects/IAstrumObject.hpp"
#include "../../Astrum/Buffers/AstrumSimpleConstantBuffer.hpp"
#include "../../Astrum/Singletons/AstrumShaderCache.hpp"
#include "../../Astrum/Singletons/AstrumChrono.hpp"
#include "../../Astrum/Vectors/AstrumVector4.hpp"

namespace InGame {
	constexpr float NoteWidth = 200.f;
	constexpr float LeftX = NoteWidth * -3.f;

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
				AstrumVector4 data{ static_cast<float>(AstrumWindow::GetWidth()), static_cast<float>(AstrumWindow::GetHeight()), owner->GetRotation().GetZ(), 0.4f };
				buffer->UpdateConstantBuffer(data);
				buffer->SetVertexShaderConstantBuffer(2);
				//buffer->SetPixelShaderConstantBuffer(2);
			}, sizeof(AstrumVector4));
		}

	private:
		std::shared_ptr<AstrumShaderSetup> shader = nullptr;
	};
}