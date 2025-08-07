#pragma once
#include "../Units/AstrumMatrix.hpp"

enum class AstrumCameraProjectionType : unsigned char
{
	AstrumCameraProjectionType_None = 0,
	// 원근 (3차원)
	AstrumCameraProjectionType_Perspective,
	// 직교 (2차원)
	AstrumCameraProjectionType_Ortho,
};

// to do : not implement, and is not used yet.
class AstrumCamera
{
public:
	AstrumCamera();

	void SetProjectionType(AstrumCameraProjectionType type);
	AstrumCameraProjectionType GetProjectionType() const { return projectionType; }

	const AstrumMatrix& GetViewMatrix() const { return viewMatrix; }
	const AstrumMatrix& GetProjectionMatrix() const { return projectionMatrix; }

protected:
	AstrumMatrix viewMatrix;
	AstrumMatrix projectionMatrix;

	void UpdateCameraView();

private:
	float width;
	float height;
	float viewDistance = 1000.f;
	float viewAngle = 90.f;
	AstrumCameraProjectionType projectionType = AstrumCameraProjectionType::AstrumCameraProjectionType_None;
};