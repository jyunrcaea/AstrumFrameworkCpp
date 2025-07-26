#include "AstrumDrawableObject.hpp"
#include <DirectXMath.h>

AstrumDrawableObject::AstrumDrawableObject() : AstrumObject() { }

void AstrumDrawableObject::Draw() {
	if (false == Visible) return;

    AstrumRenderer::Instance().EnqueueRenderable(shared_from_this());
}

void AstrumDrawableObject::Render() {
	(CustomShaderPipeline ? CustomShaderPipeline : GetDefaultShaderPipeline())->SetShader();
}

// transform 업데이트
void AstrumDrawableObject::PreRender() {
	AstrumMatrix scaleMat, rotMat, transMat;

	// 여기서 그 절대 크기/회전/좌표가 사용되요
	scaleMat.Scaling(GetAbsoluteScale());
	rotMat.Rotation(GetAbsoluteRotation());
	transMat.Translation(GetAbsolutePosition());

	transformBuffer.World = scaleMat * rotMat * transMat;

	// to do : will move to camera class.
	//transformBuffer.Projection = DirectX::XMMatrixPerspectiveFovLH(
	//	DirectX::XM_PIDIV2, 1280.0f / 720.0f, 0.5f, 1000.0f);

	const int width = AstrumWindow::GetWidth();
	const int height = AstrumWindow::GetHeight();
	constexpr int viewDistance = 1000;
	transformBuffer.Projection = DirectX::XMMatrixOrthographicOffCenterLH(
		width * -0.5f, width * 0.5f, height * -0.5f, height * 0.5f, 0.f, viewDistance
	);

	transformBuffer.UpdateBuffer();
	Render();
}