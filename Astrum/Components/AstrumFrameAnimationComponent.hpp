#pragma once
#include "AstrumComponent.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "IAstrumFrameAnimationComponent.hpp"

/// <summary>
/// 프레임 기반 애니메이션을 구현하는 컴포넌트입니다.
/// 여러 재질(프레임)을 시간에 따라 순차적으로 표시하여 애니메이션 효과를 만듭니다.
/// 반복 재생, 역방향 재생, 재생 속도 제어를 지원합니다.
/// </summary>
class AstrumFrameAnimationComponent : public AstrumComponent, public IAstrumFrameAnimationComponent
{
public:
	/// <summary>
	/// 애니메이션을 업데이트합니다. 매 프레임마다 호출됩니다.
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// 컴포넌트의 소유 객체를 설정합니다.
	/// </summary>
	/// <param name="owner">소유 객체입니다.</param>
	virtual void SetOwner(IAstrumObject* owner) override;

	/// <summary>
	/// 프레임이 변경될 때마다 호출되는 콜백 함수입니다.
	/// 매개변수는 변경된 현재 프레임 인덱스입니다.
	/// </summary>
	std::function<void(unsigned short)> OnFrameChanged = nullptr;

	/// <summary>
	/// 현재 프레임 인덱스입니다. (0부터 시작)
	/// 프레임 개수와 같을 경우 애니메이션 재생이 끝났음을 의미합니다.
	/// 기본값은 0입니다.
	/// </summary>
	unsigned short FrameIndex = 0;
	/// <summary>
	/// 애니메이션 반복 여부입니다.
	/// true이면 마지막 프레임에 도달한 후 처음부터 다시 재생되고,
	/// false이면 마지막 프레임에서 멈춥니다.
	/// 기본값은 true입니다.
	/// </summary>
	bool Loop = true;
	/// <summary>
	/// 역방향 재생 여부입니다.
	/// true이면 마지막 프레임부터 첫 프레임으로 역순으로 재생됩니다.
	/// 기본값은 false입니다.
	/// </summary>
	bool Reverse = false;

	/// <summary>
	/// 한 프레임이 표시되는 시간(초)입니다.
	/// 기본값은 1.0f입니다.
	/// </summary>
	float TimePerFrame = 1.f;
	/// <summary>
	/// 애니메이션 재생 속도입니다.
	/// 1.0f는 정상 속도이고, 2.0f는 2배 속도, 0.5f는 절반 속도입니다.
	/// 기본값은 1.0f입니다.
	/// </summary>
	float PlaybackSpeed = 1.f;

	/// <summary>
	/// 애니메이션의 모든 프레임을 반환합니다.
	/// </summary>
	/// <returns>재질 프레임들의 벡터 참조입니다.</returns>
	std::vector<std::shared_ptr<AstrumMaterial>>& GetFrames();
	/// <summary>
	/// 이 애니메이션 컴포넌트를 소유하는 재질 객체를 반환합니다.
	/// </summary>
	/// <returns>소유 재질 객체 포인터입니다.</returns>
	IAstrumMaterialObject* GetMaterialObjectOwner() const;

private:
	/// <summary>
	/// 누적된 시간(초)입니다. 프레임 변경 시점을 결정하는데 사용됩니다.
	/// </summary>
	float sumTime = 0;
	/// <summary>
	/// 애니메이션을 구성하는 재질 프레임들입니다.
	/// </summary>
	std::vector<std::shared_ptr<AstrumMaterial>> frames;
	/// <summary>
	/// 이 컴포넌트를 소유하는 재질 객체입니다.
	/// </summary>
	IAstrumMaterialObject* materialOwner = nullptr;

public:
	/// <summary>
	/// AstrumFrameAnimationComponent 객체의 공유 포인터를 생성합니다.
	/// </summary>
	/// <returns>새로 생성된 AstrumFrameAnimationComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumFrameAnimationComponent> MakeShared() {
		return std::make_shared<AstrumFrameAnimationComponent>();
	}
	/// <summary>
	/// 초기 프레임들로 AstrumFrameAnimationComponent 객체의 공유 포인터를 생성합니다.
	/// </summary>
	/// <param name="frames">초기화할 재질 프레임들입니다.</param>
	/// <returns>새로 생성된 AstrumFrameAnimationComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumFrameAnimationComponent> MakeShared(const std::vector<std::shared_ptr<AstrumMaterial>>& frames) {
		auto component = std::make_shared<AstrumFrameAnimationComponent>();
		component->frames = frames;
		return component;
	}
	/// <summary>
	/// 초기 프레임들로 AstrumFrameAnimationComponent 객체의 공유 포인터를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="frames">초기화할 재질 프레임들입니다.</param>
	/// <returns>새로 생성된 AstrumFrameAnimationComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumFrameAnimationComponent> MakeShared(std::vector<std::shared_ptr<AstrumMaterial>>&& frames) {
		auto component = std::make_shared<AstrumFrameAnimationComponent>();
		component->frames = std::move(frames);
		return component;
	}
};