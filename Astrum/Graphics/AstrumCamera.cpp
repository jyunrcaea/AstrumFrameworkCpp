#include "AstrumCamera.hpp"
#include "../Singletons/AstrumWindow.hpp"

AstrumCamera::AstrumCamera() { 
	UpdateCameraView();
}

void AstrumCamera::Update() {
	AstrumObject::Update();
	UpdateCameraView();
}

void AstrumCamera::SetProjectionType(AstrumCameraProjectionType type) {
	const float width = static_cast<float>(AstrumWindow::GetWidth());
	const float height = static_cast<float>(AstrumWindow::GetHeight());

	switch (projectionType = type) {
	case AstrumCameraProjectionType::AstrumCameraProjectionType_Perspective:
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(viewAngle), width / height, 0.5f, viewDistance);
		break;
	case AstrumCameraProjectionType::AstrumCameraProjectionType_Ortho:
		projectionMatrix = DirectX::XMMatrixOrthographicOffCenterLH(width * -0.5f, width * 0.5f, height * -0.5f, height * 0.5f, 0.f, viewDistance);
		break;
	case AstrumCameraProjectionType::AstrumCameraProjectionType_None:
	default:
		break;
	}
}

void AstrumCamera::UpdateCameraView() {
	SetProjectionType(projectionType);
}