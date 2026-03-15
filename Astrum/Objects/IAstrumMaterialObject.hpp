#pragma once
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"

class AstrumRenderMaterialComponent;

/// <summary>
/// 재질을 가지는 게임 객체의 인터페이스입니다.
/// 재질, 텍스처 메시, 텍스처를 관리하고 렌더링하기 위한 인터페이스를 제공합니다.
/// </summary>
struct IAstrumMaterialObject : public virtual IAstrumObject
{
	/// <summary>
	/// 이 재질 객체의 렌더 컴포넌트를 반환합니다.
	/// </summary>
	/// <returns>재질 렌더 컴포넌트 참조입니다.</returns>
	virtual AstrumRenderMaterialComponent& GetRenderMaterialComponent() const = 0;

	/// <summary>
	/// 이 재질 객체의 재질을 반환합니다.
	/// </summary>
	/// <returns>재질 공유 포인터입니다.</returns>
	std::shared_ptr<class AstrumMaterial> GetMaterial() const;
	/// <summary>
	/// 이 재질 객체에 재질을 설정합니다.
	/// </summary>
	/// <param name="material">설정할 재질입니다.</param>
	void SetMaterial(const std::shared_ptr<AstrumMaterial>& material);
	/// <summary>
	/// 이 재질 객체에 재질을 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="material">설정할 재질입니다.</param>
	void SetMaterial(std::shared_ptr<AstrumMaterial>&& material);

	/// <summary>
	/// 이 재질 객체의 텍스처 메시를 반환합니다.
	/// 텍스처 메시는 텍스처 좌표를 포함하는 메시입니다.
	/// </summary>
	/// <returns>텍스처 메시 공유 포인터입니다.</returns>
	std::shared_ptr<class AstrumTextureMesh> GetTextureMesh() const;
	/// <summary>
	/// 이 재질 객체의 텍스처 메시를 설정합니다.
	/// </summary>
	/// <param name="mesh">설정할 텍스처 메시입니다.</param>
	void SetTextureMesh(const std::shared_ptr<class AstrumTextureMesh>& mesh);
	/// <summary>
	/// 이 재질 객체의 텍스처 메시를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="mesh">설정할 텍스처 메시입니다.</param>
	void SetTextureMesh(std::shared_ptr<class AstrumTextureMesh>&& mesh);

	/// <summary>
	/// 이 재질 객체에서 사용하는 텍스처를 반환합니다.
	/// </summary>
	/// <returns>텍스처 공유 포인터입니다.</returns>
	std::shared_ptr<IAstrumTexture> GetTexture() const;
	/// <summary>
	/// 이 재질 객체에서 사용하는 텍스처의 너비를 반환합니다.
	/// </summary>
	/// <returns>텍스처 너비(픽셀)입니다.</returns>
	unsigned int GetTextureWidth() const;
	/// <summary>
	/// 이 재질 객체에서 사용하는 텍스처의 높이를 반환합니다.
	/// </summary>
	/// <returns>텍스처 높이(픽셀)입니다.</returns>
	unsigned int GetTextureHeight() const;
};