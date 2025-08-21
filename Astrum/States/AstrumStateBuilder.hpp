#pragma once
#include "IAstrumStateGraph.hpp"

struct IAstrumStateGraph;

class AstrumStateBuilder
{
	friend struct IAstrumStateGraph;

	AstrumStateBuilder(AstrumStateBuilder&&) = delete;
public:
	AstrumStateBuilder(IAstrumStateGraph* const graph,  const std::string& name);
	AstrumStateBuilder& SetCallback(const std::function<void(enum AstrumStateType)>& callback);
	// 조건이 맞을때 도착 정점으로 이동하는 단방향 간선을 추가합니다.
	AstrumStateBuilder& AddConditionWay(const std::string& destination, const std::function<bool()>& condition);
	// 조건이 맞는 동안 도착 정점에 이동하며, 도착 정점에서 조건이 거짓일때 출발 정점으로 돌아오는 간선 또한 추가합니다.
	AstrumStateBuilder& AddHoldConditionTwoWay(const std::string& destination, const std::function<bool()>& condition);
private:
	const std::string& departure;
	IAstrumStateGraph* const stateGraph;
};