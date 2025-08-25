#include "AstrumShaderSetup.hpp"

AstrumShaderSetup::AstrumShaderSetup() { }

AstrumShaderSetup::~AstrumShaderSetup() {
    for (auto& name : semanticNames) {
		delete[] name;
	}
}

void AstrumShaderSetup::AddInputLayoutDescription(const std::string& semanticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, D3D11_INPUT_CLASSIFICATION classification, UINT instanceDataStepRate)
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

void AstrumShaderSetup::SetShader() {
    auto* const device = AstrumRenderer::Instance().GetDevice();
    auto* const context = AstrumRenderer::Instance().GetContext();

    if (nullptr == inputLayout) {
        if (nullptr == VertexShader)
            throw AstrumException("VertexShader is null");

        ID3DBlob* blob = VertexShader->GetShaderBlob();
        if (FAILED(device->CreateInputLayout(
            inputDescriptions.data(),
            static_cast<unsigned int>(inputDescriptions.size()),
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            &inputLayout)))
        {
            throw AstrumException("CreateInputLayout failed.");
        }
    }

    if (VertexShader) VertexShader->SetShader();
    if (PixelShader) PixelShader->SetShader();
    if (HullShader) HullShader->SetShader();
    if (DomainShader) DomainShader->SetShader();
    if (GeometryShader) GeometryShader->SetShader();

    context->IASetInputLayout(inputLayout.Get());
}