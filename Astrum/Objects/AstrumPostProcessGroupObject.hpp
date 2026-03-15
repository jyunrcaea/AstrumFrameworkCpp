#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Components/AstrumPostProcessRenderComponent.hpp"
#include "../Graphics/AstrumSimpleRenderable.hpp"

/// <summary>
/// 포스트 프로세싱 효과를 적용하는 그룹 객체입니다.
/// 렌더 타겟에 자식 객체들을 렌더링한 후, 커스텀 셰이더를 사용하여 추가 처리를 수행합니다.
/// 블룸, 블러, 색상 보정 등의 효과를 구현할 수 있습니다.
/// </summary>
class AstrumPostProcessGroupObject : public AstrumGroupObject
{
public:
	/// <summary>
	/// 기본 포스트 프로세싱 그룹 객체를 생성합니다.
	/// </summary>
	AstrumPostProcessGroupObject();
	/// <summary>
	/// 상수 버퍼를 지정하여 포스트 프로세싱 그룹 객체를 생성합니다.
	/// </summary>
	/// <param name="constantBuffer">사용할 상수 버퍼입니다.</param>
	AstrumPostProcessGroupObject(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer);
	/// <summary>
	/// 상수 버퍼를 지정하여 포스트 프로세싱 그룹 객체를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="constantBuffer">사용할 상수 버퍼입니다.</param>
	AstrumPostProcessGroupObject(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer);

	/// <summary>
	/// 포스트 프로세싱 효과를 적용하여 그룹 객체를 그립니다.
	/// 렌더 타겟에 자식들을 렌더링 후, 셰이더를 적용하여 최종 결과를 출력합니다.
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// 현재 설정된 커스텀 셰이더 파이프라인을 반환합니다.
	/// </summary>
	/// <returns>커스텀 셰이더 파이프라인 공유 포인터입니다.</returns>
	std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const;
	/// <summary>
	/// 포스트 프로세싱에 사용할 커스텀 셰이더 파이프라인을 설정합니다.
	/// </summary>
	/// <param name="customShaderPipeline">설정할 셰이더 파이프라인입니다.</param>
	void SetCustomShaderPipeline(const std::shared_ptr<IAstrumShaderSetup>& customShaderPipeline) { renderComponent->SetCustomShaderPipeline(customShaderPipeline); }
	/// <summary>
	/// 포스트 프로세싱에 사용할 커스텀 셰이더 파이프라인을 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="customShaderPipeline">설정할 셰이더 파이프라인입니다.</param>
	void SetCustomShaderPipeline(std::shared_ptr<IAstrumShaderSetup>&& customShaderPipeline) { renderComponent->SetCustomShaderPipeline(std::move(customShaderPipeline)); }

	/// <summary>
	/// 렌더링에 사용하는 상수 버퍼를 반환합니다.
	/// </summary>
	/// <returns>상수 버퍼 공유 포인터입니다.</returns>
	std::shared_ptr<IAstrumConstantBuffer> GetConstantBuffer() const { return renderComponent->ConstantBuffer; }
	/// <summary>
	/// 렌더링에 사용할 상수 버퍼를 설정합니다.
	/// </summary>
	/// <param name="constantBuffer">설정할 상수 버퍼입니다.</param>
	void SetConstantBuffer(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer) { renderComponent->ConstantBuffer = constantBuffer; }
	/// <summary>
	/// 렌더링에 사용할 상수 버퍼를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="constantBuffer">설정할 상수 버퍼입니다.</param>
	void SetConstantBuffer(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer) { renderComponent->ConstantBuffer = std::move(constantBuffer); }

	/// <summary>
	/// 포스트 프로세싱에 사용되는 메시를 반환합니다.
	/// </summary>
	/// <returns>메시 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumTextureMesh> GetMaterialMesh() const { return renderComponent->Mesh; }
	/// <summary>
	/// 포스트 프로세싱에 사용할 메시를 설정합니다.
	/// </summary>
	/// <param name="mesh">설정할 메시입니다.</param>
	void SetMaterialMesh(const std::shared_ptr<AstrumTextureMesh>& mesh) { renderComponent->Mesh = mesh; }
	/// <summary>
	/// 포스트 프로세싱에 사용할 메시를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="mesh">설정할 메시입니다.</param>
	void SetMaterialMesh(std::shared_ptr<AstrumTextureMesh>&& mesh) { renderComponent->Mesh = std::move(mesh); }
private:
	/// <summary>
	/// 자식 객체들을 렌더링할 렌더 타겟입니다.
	/// 창의 크기로 초기화됩니다.
	/// </summary>
	std::shared_ptr<AstrumRenderTarget> renderTarget = AstrumRenderTarget::MakeShared(AstrumWindow::GetWidth(), AstrumWindow::GetHeight());
	/// <summary>
	/// 포스트 프로세싱 렌더링을 수행하는 컴포넌트입니다.
	/// </summary>
	std::shared_ptr<AstrumPostProcessRenderComponent> renderComponent = AstrumPostProcessRenderComponent::MakeShared();

	/// <summary>
	/// 렌더 타겟을 바인딩하는 렌더링 작업입니다.
	/// </summary>
	std::shared_ptr<AstrumSimpleRenderable> bindRenderTarget = nullptr;
	/// <summary>
	/// 렌더 타겟을 언바인딩하는 렌더링 작업입니다.
	/// </summary>
	std::shared_ptr<AstrumSimpleRenderable> unbindRenderTarget = nullptr;

public:
	/// <summary>
	/// AstrumPostProcessGroupObject의 공유 포인터를 생성합니다.
	/// </summary>
	/// <returns>새로 생성된 AstrumPostProcessGroupObject 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumPostProcessGroupObject> MakeShared() { return std::make_shared<AstrumPostProcessGroupObject>(); }
	/// <summary>
	/// 상수 버퍼를 지정하여 AstrumPostProcessGroupObject의 공유 포인터를 생성합니다.
	/// </summary>
	/// <param name="constantBuffer">사용할 상수 버퍼입니다.</param>
	/// <returns>새로 생성된 AstrumPostProcessGroupObject 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumPostProcessGroupObject> MakeShared(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer) { return std::make_shared<AstrumPostProcessGroupObject>(constantBuffer); }
	/// <summary>
	/// 상수 버퍼를 지정하여 AstrumPostProcessGroupObject의 공유 포인터를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="constantBuffer">사용할 상수 버퍼입니다.</param>
	/// <returns>새로 생성된 AstrumPostProcessGroupObject 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumPostProcessGroupObject> MakeShared(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer) { return std::make_shared<AstrumPostProcessGroupObject>(std::move(constantBuffer)); }
};