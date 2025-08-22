#include "AstrumCamera.hpp"
#include "../Singletons/AstrumWindow.hpp"

namespace Astrum
{
	Camera::Camera() {
		UpdateCameraView();
	}

	void Camera::Update() {
		Object::Update();
		UpdateCameraView();
	}

	void Camera::SetProjectionType(CameraProjectionType type) {
		const float width = static_cast<float>(Window::GetWidth());
		const float height = static_cast<float>(Window::GetHeight());

		switch (projectionType = type) {
		case CameraProjectionType::CameraProjectionType_Perspective:
			projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(viewAngle), width / height, 0.5f, viewDistance);
			break;
		case CameraProjectionType::CameraProjectionType_Ortho:
			projectionMatrix = DirectX::XMMatrixOrthographicOffCenterLH(width * -0.5f, width * 0.5f, height * -0.5f, height * 0.5f, 0.f, viewDistance);
			break;
		case CameraProjectionType::CameraProjectionType_None:
		default:
			break;
		}
	}

	void Camera::UpdateCameraView() {
		SetProjectionType(projectionType);
	}
}