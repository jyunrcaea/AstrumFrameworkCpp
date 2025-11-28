#pragma once
#include "IAstrumAABBColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../Singletons/AstrumRawInput.hpp"
#include "../Singletons/AstrumRenderer.hpp"

/// <summary>
/// 충돌체 유형을 나타내는 열거형입니다.
/// </summary>
enum AstrumColliderType
{
	/// <summary>
	/// 충돌체가 없음을 나타냅니다.
	/// </summary>
	AstrumColliderType_None = 0,
	/// <summary>
	/// AABB(축 정렬 경계 상자) 충돌체입니다.
	/// </summary>
	AstrumColliderType_AABB,
	/// <summary>
	/// 원형 충돌체입니다.
	/// </summary>
	AstrumColliderType_Circle,
	/// <summary>
	/// OBB(방향 경계 상자) 충돌체입니다.
	/// </summary>
	AstrumColliderType_OBB,
	/// <summary>
	/// 충돌체 유형의 개수입니다. (열거형 끝 표시)
	/// </summary>
	AstrumColliderType_Count
};

/// <summary>
/// 충돌 감지를 수행하는 컴포넌트의 인터페이스입니다.
/// 더블 디스패치 디자인 패턴을 사용하여 다양한 충돌체 타입 간의 충돌을 안전하게 감지합니다.
/// </summary>
struct IAstrumColliderComponent
{
public:
	/// <summary>
	/// IAstrumColliderComponent 인터페이스를 소멸합니다.
	/// </summary>
	virtual ~IAstrumColliderComponent() = default;

	/// <summary>
	/// 이 충돌체의 유형을 반환합니다.
	/// </summary>
	/// <returns>충돌체 유형입니다.</returns>
	virtual AstrumColliderType GetColliderType() const = 0;

	/// <summary>
	/// 다른 충돌체와의 겹침을 확인합니다.
	/// 더블 디스패치 디자인 패턴을 사용하여 타입 안전하게 적절한 충돌 로직을 적용합니다.
	/// </summary>
	/// <param name="other">비교할 다른 충돌체입니다.</param>
	/// <returns>겹치면 true, 겹치지 않으면 false를 반환합니다.</returns>
	virtual bool IsOverlap(IAstrumColliderComponent* other) = 0;
	/// <summary>
	/// AABB 충돌체와의 겹침을 확인합니다.
	/// </summary>
	/// <param name="other">비교할 AABB 충돌체입니다.</param>
	/// <returns>겹치면 true, 겹치지 않으면 false를 반환합니다.</returns>
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) = 0;
	/// <summary>
	/// OBB 충돌체와의 겹침을 확인합니다.
	/// </summary>
	/// <param name="other">비교할 OBB 충돌체입니다.</param>
	/// <returns>겹치면 true, 겹치지 않으면 false를 반환합니다.</returns>
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) = 0;
	/// <summary>
	/// 원형 충돌체와의 겹침을 확인합니다.
	/// </summary>
	/// <param name="other">비교할 원형 충돌체입니다.</param>
	/// <returns>겹치면 true, 겹치지 않으면 false를 반환합니다.</returns>
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) = 0;

	/// <summary>
	/// 지정된 점과의 겹침을 확인합니다.
	/// </summary>
	/// <param name="point">확인할 점의 좌표입니다.</param>
	/// <returns>점이 충돌체 내부에 있으면 true, 아니면 false를 반환합니다.</returns>
	virtual bool IsOverlapToPoint(AstrumVector2 point) = 0;
	/// <summary>
	/// 마우스 포인터와의 겹침을 확인합니다.
	/// 렌더러의 해상도 절반을 빼서 중앙 기준 좌표로 변환한 후 확인합니다.
	/// </summary>
	/// <returns>마우스 포인터가 충돌체 내부에 있으면 true, 아니면 false를 반환합니다.</returns>
	bool IsOverlapToMousePointer() { 
#if _DEBUG && FALSE
		std::cout << "Mouse Position: " << AstrumRawInput::GetMousePosition() << ", Half Resolution: " << AstrumRenderer::Instance().GetHalfResolution() << ", Adjusted Position: " << (AstrumRawInput::GetMousePosition() - AstrumRenderer::Instance().GetHalfResolution()) << std::endl;
#endif	
		return IsOverlapToPoint(static_cast<AstrumVector2>(AstrumRawInput::GetMousePosition() - AstrumRenderer::Instance().GetHalfResolution()));
	}
};