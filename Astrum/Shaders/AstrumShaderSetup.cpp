#include "AstrumShaderSetup.hpp"

namespace Astrum
{
	ShaderSetup::ShaderSetup() { }

	ShaderSetup::~ShaderSetup() {
		for (auto& name : semanticNames) {
			delete[] name;
		}
	}

	void ShaderSetup::AddInputLayoutDescription(const std::string& semanticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, D3D11_INPUT_CLASSIFICATION classification, UINT instanceDataStepRate)
	{
		char* namePtr = new char[semanticName.size() + 1];
		std::copy(semanticName.begin(), semanticName.end(), namePtr);
		namePtr[semanticName.size()] = '\0';
		semanticNames.push_back(namePtr);

		D3D11_INPUT_ELEMENT_DESC desc{};
		desc.SemanticName = namePtr;
		desc.SemanticIndex = semanticIndex;
		desc.Format = format;
		desc.InputSlot = inputSlot;
		desc.InputSlotClass = classification;
		desc.InstanceDataStepRate = instanceDataStepRate;
		desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

		inputDescriptions.push_back(desc);
	}

	void ShaderSetup::SetShader() {
		auto* const device = Renderer::Instance().GetDevice();
		auto* const context = Renderer::Instance().GetContext();

		if (nullptr == inputLayout) {
			if (nullptr == VertexShader)
				throw Exception("VertexShader is null");

			ID3DBlob* blob = VertexShader->GetShaderBlob();
			if (FAILED(device->CreateInputLayout(
				inputDescriptions.data(),
				static_cast<unsigned int>(inputDescriptions.size()),
				blob->GetBufferPointer(),
				blob->GetBufferSize(),
				&inputLayout)))
			{
				throw Exception("CreateInputLayout failed.");
			}
		}

		if (VertexShader) VertexShader->SetShader();
		if (PixelShader) PixelShader->SetShader();
		if (HullShader) HullShader->SetShader();
		if (DomainShader) DomainShader->SetShader();
		if (GeometryShader) GeometryShader->SetShader();

		context->IASetInputLayout(inputLayout.Get());
	}
}