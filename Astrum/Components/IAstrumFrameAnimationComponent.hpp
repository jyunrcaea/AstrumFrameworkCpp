#pragma once
#include "../Objects/IAstrumObject.hpp"
#include <vector>
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"

/// <summary>
/// 프레임 애니메이션을 구현하는 컴포넌트의 인터페이스입니다.
/// 여러 재질(프레임)을 순차적으로 표시하여 애니메이션 효과를 만듭니다.
/// </summary>
struct IAstrumFrameAnimationComponent
{
	/// <summary>
	/// IAstrumFrameAnimationComponent 인터페이스를 소멸합니다.
	/// </summary>
	virtual ~IAstrumFrameAnimationComponent() = default;

	/// <summary>
	/// 이 프레임 애니메이션 컴포넌트의 소유 재질 객체를 반환합니다.
	/// </summary>
	/// <returns>소유 재질 객체 포인터입니다.</returns>
	virtual IAstrumMaterialObject* GetMaterialObjectOwner() const = 0;
	/// <summary>
	/// 프레임 목록을 반환합니다.
	/// </summary>
	/// <returns>재질 프레임들의 벡터 참조입니다.</returns>
	virtual std::vector<std::shared_ptr<AstrumMaterial>>& GetFrames() = 0;

	/// <summary>
	/// 지정된 인덱스의 프레임을 설정합니다.
	/// </summary>
	/// <param name="index">설정할 프레임 인덱스입니다.</param>
	/// <param name="material">설정할 재질입니다.</param>
	inline void SetFrame(int index, const std::shared_ptr<AstrumMaterial>& material) { GetFrames()[index] = material; }
	/// <summary>
	/// 새로운 프레임을 애니메이션에 추가합니다.
	/// </summary>
	/// <param name="material">추가할 재질 프레임입니다.</param>
	inline void AddFrame(const std::shared_ptr<AstrumMaterial>& material) { GetFrames().push_back(material); }
	/// <summary>
	/// 애니메이션의 총 프레임 개수를 반환합니다.
	/// </summary>
	/// <returns>프레임 개수입니다.</returns>
	inline size_t GetFrameCount() { return GetFrames().size(); }
};