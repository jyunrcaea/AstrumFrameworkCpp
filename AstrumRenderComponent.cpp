#include "AstrumRenderComponent.hpp"

void AstrumRenderComponent::Render() {
	if (nullptr == GetOwner()) return;

	(CustomShaderPipeline ? CustomShaderPipeline : GetDefaultShaderPipeline())->SetShader();
}

void AstrumRenderComponent::PreRender() {
	if (nullptr == GetOwner()) return;

	AstrumMatrix scaleMat, rotMat, transMat;

	scaleMat.Scaling(GetOwner()->GetAbsoluteScale());
	rotMat.Rotation(GetOwner()->GetAbsoluteRotation());
	transMat.Translation(GetOwner()->GetAbsolutePosition());

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