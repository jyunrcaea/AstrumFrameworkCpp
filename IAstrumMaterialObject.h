#pragma once
#include "AstrumMaterial.hpp"

struct IAstrumMaterialObject
{
	virtual AstrumMaterial& GetMaterial() const = 0;
	virtual void SetMaterial(const std::shared_ptr<AstrumMaterial>& material) = 0;
};