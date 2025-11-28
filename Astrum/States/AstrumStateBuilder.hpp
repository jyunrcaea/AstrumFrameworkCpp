#pragma once
#include "IAstrumStateGraph.hpp"

struct IAstrumStateGraph;
enum AstrumStateType : char;

/// <summary>
/// 상태 그래프의 상태와 전환을 구성하는 빌더 클래스입니다.
/// 플루언트 인터페이스를 제공하여 상태 전환 규칙을 직관적으로 정의할 수 있습니다.
/// </summary>
class AstrumStateBuilder
{
	friend struct IAstrumStateGraph;

	/// <summary>
	/// 우측값 참조 생성자를 삭제하여 이동을 방지합니다.
	/// </summary>
	AstrumStateBuilder(AstrumStateBuilder&&) = delete;
public:
	/// <summary>
	/// 상태 빌더를 생성합니다.
	/// </summary>
	/// <param name="graph">이 상태가 속할 상태 그래프입니다.</param>
	/// <param name="name">상태의 이름입니다.</param>
	AstrumStateBuilder(IAstrumStateGraph* const graph,  const std::string& name);
	/// <summary>
	/// 상태 진입 시 호출될 콜백 함수를 설정합니다.
	/// </summary>
	/// <param name="callback">상태 진입 시 호출될 콜백 함수입니다. 
	/// 매개변수는 이전 상태의 타입입니다.</param>
	/// <returns>메서드 체이닝을 위해 이 빌더 객체의 참조를 반환합니다.</returns>
	AstrumStateBuilder& SetCallback(const std::function<void(AstrumStateType)>& callback);
	/// <summary>
	/// 조건이 참일 때 목표 상태로 이동하는 단방향 전환을 추가합니다.
	/// 조건이 거짓이 되어도 원래 상태로 돌아오지 않습니다.
	/// </summary>
	/// <param name="destination">목표 상태의 이름입니다.</param>
	/// <param name="condition">상태 전환 조건을 평가하는 함수입니다. 
	/// 참이면 전환이 발생합니다.</param>
	/// <returns>메서드 체이닝을 위해 이 빌더 객체의 참조를 반환합니다.</returns>
	AstrumStateBuilder& AddConditionWay(const std::string& destination, const std::function<bool()>& condition);
	/// <summary>
	/// 조건이 참인 동안 목표 상태에 머물러 있고, 조건이 거짓이 되면 원래 상태로 돌아오는 양방향 전환을 추가합니다.
	/// 이 메서드는 자동으로 목표 상태에서 출발 상태로 돌아오는 역방향 전환도 추가합니다.
	/// </summary>
	/// <param name="destination">목표 상태의 이름입니다.</param>
	/// <param name="condition">상태 전환 및 유지 조건을 평가하는 함수입니다. 
	/// 참이면 목표 상태로 전환되고 유지되며, 거짓이면 원래 상태로 돌아옵니다.</param>
	/// <returns>메서드 체이닝을 위해 이 빌더 객체의 참조를 반환합니다.</returns>
	AstrumStateBuilder& AddHoldConditionTwoWay(const std::string& destination, const std::function<bool()>& condition);
private:
	/// <summary>
	/// 이 빌더가 구성하는 출발 상태의 이름입니다.
	/// </summary>
	const std::string& departure;
	/// <summary>
	/// 이 상태가 속한 상태 그래프입니다.
	/// </summary>
	IAstrumStateGraph* const stateGraph;
};