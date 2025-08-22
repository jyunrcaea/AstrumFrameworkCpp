#pragma once
#include "../Objects/AstrumObject.hpp"
#include "../Units/AstrumMatrix.hpp"

namespace Astrum
{
	enum class CameraProjectionType : unsigned char
	{
		CameraProjectionType_None = 0,
		// 원근 (3차원)
		CameraProjectionType_Perspective,
		// 직교 (2차원)
		CameraProjectionType_Ortho,
	};

	class Camera : public Object
	{
	public:
		//기본값은 직교입니다.
		Camera();

		void Update() override;

		void SetProjectionType(CameraProjectionType type);
		CameraProjectionType GetProjectionType() const { return projectionType; }

		const Matrix& GetViewMatrix() const { return viewMatrix; }
		const Matrix& GetProjectionMatrix() const { return projectionMatrix; }

	protected:
		Matrix viewMatrix;
		Matrix projectionMatrix;

		void UpdateCameraView();

	private:
		float viewDistance = 1000.f;
		float viewAngle = 90.f;
		CameraProjectionType projectionType = CameraProjectionType::CameraProjectionType_Ortho;
	};
}