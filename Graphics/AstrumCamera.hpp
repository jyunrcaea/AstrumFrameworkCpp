#pragma once
#include "../Objects/AstrumObject.hpp"
#include "../Units/AstrumMatrix.hpp"

enum class AstrumCameraProjectionType : unsigned char
{
	AstrumCameraProjectionType_None = 0,
	// 원근 (3차원)
	AstrumCameraProjectionType_Perspective,
	// 직교 (2차원)
	AstrumCameraProjectionType_Ortho,
};

class AstrumCamera : public AstrumObject
{
public:
	//기본값은 직교입니다.
	AstrumCamera();

	void Update() override;

	void SetProjectionType(AstrumCameraProjectionType type);
	AstrumCameraProjectionType GetProjectionType() const { return projectionType; }

	const AstrumMatrix& GetViewMatrix() const { return viewMatrix; }
	const AstrumMatrix& GetProjectionMatrix() const { return projectionMatrix; }

protected:
	AstrumMatrix viewMatrix;
	AstrumMatrix projectionMatrix;

	void UpdateCameraView();

private:
	float viewDistance = 1000.f;
	float viewAngle = 90.f;
	AstrumCameraProjectionType projectionType = AstrumCameraProjectionType::AstrumCameraProjectionType_Ortho;
};