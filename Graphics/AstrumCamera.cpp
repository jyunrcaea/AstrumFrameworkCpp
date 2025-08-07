#include "AstrumCamera.hpp"
#include "../Singletons/AstrumWindow.hpp"

AstrumCamera::AstrumCamera() 
	: width(static_cast<float>(AstrumWindow::GetWidth())), height(static_cast<float>(AstrumWindow::GetHeight()))
{ }

void AstrumCamera::SetProjectionType(AstrumCameraProjectionType type) {
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

void AstrumCamera::UpdateCameraView()
{
}
