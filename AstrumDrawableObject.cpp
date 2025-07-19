#include "AstrumDrawableObject.hpp"
#include <DirectXMath.h>

AstrumDrawableObject::AstrumDrawableObject() : AstrumObject() { }

void AstrumDrawableObject::Draw() {
    AstrumRenderer::Instance().EnqueueRenderable(shared_from_this());
}

void AstrumDrawableObject::Render() { }

// 어디서 많이 봤죠
void AstrumDrawableObject::Rendering() {
	AstrumMatrix scaleMat, rotMat, transMat;

	// 여기서 그 절대 크기/회전/좌표가 사용되요
	scaleMat.Scaling(absoluteScale);
	rotMat.Rotation(absoluteRotation);
	transMat.Translation(absolutePosition);

	transformBuffer.World = scaleMat * rotMat * transMat;
	transformBuffer.Projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XM_PIDIV2, 1280.0f / 720.0f, 0.5f, 1000.0f);

	transformBuffer.UpdateBuffer();
	Render();
}