#pragma once
#include <vector>
#include <memory>
#include "AstrumMaterial.hpp"
#include "IAstrumMaterialObject.h"

struct IAstrumFrameAnimationComponent
{
	virtual ~IAstrumFrameAnimationComponent() = default;

	virtual IAstrumMaterialObject* GetMaterialObjectOwner() const = 0;
	virtual std::vector<std::shared_ptr<AstrumMaterial>>& GetFrames() = 0;

	void SetFrame(int index, const std::shared_ptr<AstrumMaterial>& material);
	void AddFrame(const std::shared_ptr<AstrumMaterial>& material);
	size_t GetFrameCount();
};