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

	class DataManager : public Astrum::Singleton<DataManager>
	{
		friend class Astrum::Singleton<DataManager>;
	public:
		std::shared_ptr<Astrum::ShaderSetup> GetIllusionShader() {
			using namespace Astrum;
			if (nullptr == shader) {
				shader = ShaderSetup::MakeShared();
				ShaderCache::SetDefaultRelativeDirectory("./Game/Shaders/");
				shader->VertexShader = ShaderCache::LoadVertexShader(L"Illusion.fx", "IllusionVS");
				shader->PixelShader = ShaderCache::LoadPixelShader(L"Illusion.fx", "IllusionPS");
				shader->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
				shader->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);
			}
			return shader;
		}

		std::shared_ptr<Astrum::ConstantBufferComponent> GetIllusionConstantBufferComponent(Astrum::IObject* owner) {
			using namespace Astrum;
			auto constantBuffer = ConstantBufferComponent::MakeShared(
				SimpleConstantBuffer::MakeShared([this, owner](ConstantBuffer* buffer) {
					Vector4 data{ static_cast<float>(Window::GetWidth()), static_cast<float>(Window::GetHeight()), owner->GetRotation().GetZ(), 0.4f };
					buffer->UpdateConstantBuffer(data);
					buffer->SetPixelShaderConstantBuffer(2);
					}, sizeof(Vector4))
			);
			return constantBuffer;
		}

	private:
		std::shared_ptr<Astrum::ShaderSetup> shader = nullptr;
	};
}