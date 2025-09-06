#pragma once
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"

class AstrumRenderMaterialComponent;

struct IAstrumMaterialObject : public virtual IAstrumObject
{
	virtual AstrumRenderMaterialComponent& GetRenderMaterialComponent() const = 0;

	std::shared_ptr<class AstrumMaterial> GetMaterial() const;
	void SetMaterial(const std::shared_ptr<AstrumMaterial>& material);
	void SetMaterial(std::shared_ptr<AstrumMaterial>&& material);

	std::shared_ptr<class AstrumTextureMesh> GetTextureMesh() const;
	void SetTextureMesh(const std::shared_ptr<class AstrumTextureMesh>& mesh);
	void SetTextureMesh(std::shared_ptr<class AstrumTextureMesh>&& mesh);

	std::shared_ptr<IAstrumTexture> GetTexture() const;
	unsigned int GetTextureWidth() const;
	unsigned int GetTextureHeight() const;
};