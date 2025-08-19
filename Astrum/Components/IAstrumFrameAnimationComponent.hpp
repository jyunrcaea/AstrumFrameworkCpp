#pragma once
#include "../Objects/IAstrumObject.hpp"
#include <vector>
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"

struct IAstrumFrameAnimationComponent
{
	virtual ~IAstrumFrameAnimationComponent() = default;

	virtual IAstrumMaterialObject* GetMaterialObjectOwner() const = 0;
	virtual std::vector<std::shared_ptr<AstrumMaterial>>& GetFrames() = 0;

	inline void SetFrame(int index, const std::shared_ptr<AstrumMaterial>& material) { GetFrames()[index] = material; }
	inline void AddFrame(const std::shared_ptr<AstrumMaterial>& material) { GetFrames().push_back(material); }
	inline size_t GetFrameCount() { return GetFrames().size(); }
};