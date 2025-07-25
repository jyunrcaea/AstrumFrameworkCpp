#pragma once
#include "AstrumMaterial.hpp"

struct IAstrumMaterialObject
{
	virtual std::shared_ptr<AstrumMaterial> GetMaterial() = 0;
	virtual void SetMaterial(const std::shared_ptr<AstrumMaterial>& material) = 0;

	virtual std::shared_ptr<AstrumTexture> GetTexture();
};