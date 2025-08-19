#pragma once
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Resources/AstrumTexture.hpp"

struct IAstrumMaterialObject
{
	virtual std::shared_ptr<class AstrumRenderMaterialComponent> GetRenderMaterialComponent() const = 0;

	std::shared_ptr<class AstrumMaterial> GetMaterial() const;
	void SetMaterial(const std::shared_ptr<class AstrumMaterial>& material);
	std::shared_ptr<class AstrumTextureMesh> GetTextureMesh() const;
	void SetTextureMesh(const std::shared_ptr<class AstrumTextureMesh>& mesh);
	std::shared_ptr<class AstrumTexture> GetTexture() const;
};