#pragma once
#include "IAstrumStateGraph.hpp"
#include "AstrumStateBuilder.hpp"

class AstrumStateGraph : public IAstrumStateGraph
{
public:
	/// <summary>
	/// 상태 그래프에 새로운 상태를 추가합니다.
	/// </summary>
	/// <param name="name">추가할 상태의 이름입니다.</param>
	/// <returns>상태가 성공적으로 추가되면 true, 이미 존재하면 false를 반환합니다.</returns>
	virtual bool AddStateName(const std::string& name) override;
	/// <summary>
	/// 상태 그래프에 새로운 상태를 추가하고 콜백 함수를 설정합니다.
	/// </summary>
	/// <param name="name">추가할 상태의 이름입니다.</param>
	/// <param name="callback">상태 변화 시 호출될 콜백 함수입니다.</param>
	/// <returns>상태가 성공적으로 추가되면 true, 이미 존재하면 false를 반환합니다.</returns>
	virtual bool AddStateName(const std::string& name, const std::function<void(AstrumStateType)>& callback) override;
	/// <summary>
	/// 상태 그래프에 여러 상태들을 한 번에 추가합니다.
	/// </summary>
	/// <param name="names">추가할 상태 이름들의 초기화 리스트입니다.</param>
	virtual void AddStateNames(const std::initializer_list<std::string>& names) override;

	/// <summary>
	/// 한 상태에서 다른 상태로 전환되는 조건 간선을 추가합니다.
	/// </summary>
	/// <typeparam name="FromType">출발 상태 타입입니다. std::string으로 변환 가능해야 합니다.</typeparam>
	/// <typeparam name="ToType">도착 상태 타입입니다. std::string으로 변환 가능해야 합니다.</typeparam>
	/// <typeparam name="ConditionType">조건 함수 타입입니다. std::function&lt;bool()&gt;으로 변환 가능해야 합니다.</typeparam>
	/// <param name="from">출발 상태의 이름입니다.</param>
	/// <param name="to">도착 상태의 이름입니다.</param>
	/// <param name="condition">상태 전환 조건을 판별하는 함수입니다.</param>
	template<typename FromType, typename ToType, typename ConditionType>
	requires std::convertible_to<FromType, std::string>&& std::convertible_to<ToType, std::string>&& std::convertible_to<ConditionType, std::function<bool()>>
	void AddConditionWay(FromType&& from, ToType&& to, ConditionType&& condition) {
		stateGraph[from].emplace_back(std::forward<FromType>(from), std::forward<ToType>(to), std::forward<ConditionType>(condition));
	}
	/// <summary>
	/// 한 상태에서 다른 상태로 전환되는 조건 간선을 추가합니다.
	/// </summary>
	/// <param name="from">출발 상태의 이름입니다.</param>
	/// <param name="to">도착 상태의 이름입니다.</param>
	/// <param name="condition">상태 전환 조건을 판별하는 함수입니다.</param>
	virtual void AddConditionWay(const std::string& from,const std::string& to, const std::function<bool()>& condition) override;
	/// <summary>
	/// 특정 상태의 콜백 함수를 설정합니다.
	/// </summary>
	/// <param name="name">콜백을 설정할 상태의 이름입니다.</param>
	/// <param name="callback">설정할 콜백 함수입니다.</param>
	/// <returns>콜백이 성공적으로 설정되면 true, 상태가 없으면 false를 반환합니다.</returns>
	virtual bool SetCallback(const std::string& name, const std::function<void(AstrumStateType)>& callback) override;
	/// <summary>
	/// 특정 상태의 콜백 함수를 반환합니다.
	/// </summary>
	/// <param name="name">콜백을 조회할 상태의 이름입니다.</param>
	/// <returns>상태에 설정된 콜백 함수 참조입니다.</returns>
	virtual std::function<void(AstrumStateType)>& GetCallback(const std::string& name) override;
	/// <summary>
	/// 전체 상태 그래프를 반환합니다.
	/// </summary>
	/// <returns>상태 이름을 키로 하고 조건 간선들을 값으로 하는 그래프입니다.</returns>
	virtual const std::unordered_map<std::string, std::vector<ConditionLine>>& GetGraph() const override;
	/// <summary>
	/// 특정 상태에서 출발하는 모든 조건 간선을 반환합니다.
	/// </summary>
	/// <param name="from">조회할 출발 상태의 이름입니다.</param>
	/// <returns>출발 상태에서 나가는 조건 간선들의 벡터입니다.</returns>
	virtual const std::vector<ConditionLine>& GetLines(const std::string from) override;
	/// <summary>
	/// 특정 상태의 콜백 함수를 호출합니다.
	/// </summary>
	/// <param name="name">콜백을 호출할 상태의 이름입니다.</param>
	/// <param name="type">콜백에 전달할 상태 타입입니다.</param>
	/// <returns>콜백이 성공적으로 호출되면 true, 상태가 없으면 false를 반환합니다.</returns>
	virtual bool InvokeCallback(const std::string& name, AstrumStateType type) override;

	/// <summary>
	/// 특정 상태에 대한 상태 빌더를 생성합니다.
	/// </summary>
	/// <param name="name">빌더를 생성할 상태의 이름입니다.</param>
	/// <returns>생성된 상태 빌더입니다.</returns>
	AstrumStateBuilder MakeStateBuilder(const std::string& name);
private:
	std::unordered_map<std::string,std::vector<ConditionLine>> stateGraph;
	std::unordered_map<std::string, std::function<void(AstrumStateType)>> stateCallback;

public:
	/// <summary>
	/// AstrumStateGraph 객체의 공유 포인터를 생성합니다.
	/// </summary>
	/// <returns>새로 생성된 AstrumStateGraph 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumStateGraph> MakeShared() { return std::make_shared<AstrumStateGraph>(); }
};