#include "AstrumMaterialConstantBuffer.hpp"

namespace {
	using ushort = unsigned short;
}

AstrumMaterialConstantBuffer::AstrumMaterialConstantBuffer()
	: AstrumConstantBuffer(sizeof(AstrumMaterialData))
{
}

void AstrumMaterialConstantBuffer::SetColor(const AstrumVector4& color) { data.BaseColor = color; }
void AstrumMaterialConstantBuffer::SetOpacity(float opacity) { data.Opacity = opacity; }
void AstrumMaterialConstantBuffer::SetSize(unsigned short width, unsigned short height) { data.Width = width; data.Height = height; }
void AstrumMaterialConstantBuffer::SetSampleType(AstrumTextureSampleType type) { data.sampleType = type; }

AstrumVector4& AstrumMaterialConstantBuffer::GetColor() { return data.BaseColor; }
float& AstrumMaterialConstantBuffer::GetOpacity() { return data.Opacity; }
std::pair<ushort, ushort> AstrumMaterialConstantBuffer::GetSize() const { return { static_cast<ushort>(data.Width), static_cast<ushort>(data.Height) }; }
AstrumTextureSampleType& AstrumMaterialConstantBuffer::GetSampleType() { return data.sampleType; }

void AstrumMaterialConstantBuffer::UpdateBuffer() {
	Update(std::as_bytes(std::span{ &data, 1 }));

	AstrumRenderer::Instance().GetContext()->PSSetConstantBuffers(1, 1, buffer.GetAddressOf());
#if _DEBUG
	if (nullptr == buffer) throw AstrumException("Buffer be nullptr.");
#endif
}