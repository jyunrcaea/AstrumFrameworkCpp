#pragma once
#include <vector>
#include <memory>

namespace Astrum {
	class Material;
	struct IMaterialObject;

	struct IFrameAnimationComponent
	{
		virtual ~IFrameAnimationComponent() = default;

		virtual IMaterialObject* GetMaterialObjectOwner() const = 0;
		virtual std::vector<std::shared_ptr<Material>>& GetFrames() = 0;

		inline void SetFrame(int index, const std::shared_ptr<Material>& material) { GetFrames()[index] = material; }
		inline void AddFrame(const std::shared_ptr<Material>& material) { GetFrames().push_back(material); }
		inline size_t GetFrameCount() { return GetFrames().size(); }
	};
}