#pragma once
#include "AstrumMatrix.hpp"

// to do : not implement yet.
class AstrumCamera
{
public:
	AstrumCamera() = default;

	AstrumObservedVector3 Position;
	AstrumObservedVector3 Rotation;

	const AstrumMatrix& GetViewMatrix() const { return viewMatrix; }
	const AstrumMatrix& GetProjectionMatrix() const { return projectionMatrix; }

protected:
	AstrumMatrix viewMatrix;
	AstrumMatrix projectionMatrix;

	void UpdateCameraView();
};