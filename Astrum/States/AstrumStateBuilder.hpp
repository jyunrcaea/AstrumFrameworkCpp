#pragma once
#include "IAstrumStateGraph.hpp"

namespace Astrum
{
	struct IStateGraph;
	enum class EStateType : char;

	class StateBuilder
	{
		friend struct IStateGraph;

		StateBuilder(StateBuilder&&) = delete;
	public:
		StateBuilder(IStateGraph* const graph, const std::string& name);
		StateBuilder& SetCallback(const std::function<void(EStateType)>& callback);
		// 조건이 맞을때 도착 정점으로 이동하는 단방향 간선을 추가합니다.
		StateBuilder& AddConditionWay(const std::string& destination, const std::function<bool()>& condition);
		// 조건이 맞는 동안 도착 정점에 이동하며, 도착 정점에서 조건이 거짓일때 출발 정점으로 돌아오는 간선 또한 추가합니다.
		StateBuilder& AddHoldConditionTwoWay(const std::string& destination, const std::function<bool()>& condition);
	private:
		const std::string& departure;
		IStateGraph* const stateGraph;
	};
}