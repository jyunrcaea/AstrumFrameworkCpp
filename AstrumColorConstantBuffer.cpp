#include "AstrumColorConstantBuffer.hpp"

AstrumColorConstantBuffer::AstrumColorConstantBuffer()
	: AstrumConstantBuffer(sizeof(AstrumVector4))
{
}

void AstrumColorConstantBuffer::UpdateBuffer() {
	Update(std::as_bytes(std::span{ &Data, 1 }));

	AstrumRenderer::Instance().GetContext()->PSSetConstantBuffers(0, 1, &buffer);
}