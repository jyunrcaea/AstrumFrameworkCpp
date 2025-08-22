#include "AstrumStateBuilder.hpp"

namespace Astrum
{
	StateBuilder::StateBuilder(IStateGraph* graph, const std::string& name)
		: departure(name), stateGraph(graph) {
		stateGraph->AddStateName(name);
	}

	StateBuilder& StateBuilder::SetCallback(const std::function<void(EStateType)>& callback) {
		stateGraph->SetCallback(departure, callback);
		return *this;
	}

	StateBuilder& StateBuilder::AddConditionWay(const std::string& destination, const std::function<bool()>& condition) {
		stateGraph->AddConditionWay(departure, destination, condition);
		return *this;
	}

	StateBuilder& StateBuilder::AddHoldConditionTwoWay(const std::string& destination, const std::function<bool()>& condition) {
		stateGraph->AddConditionWay(departure, destination, condition);
		stateGraph->AddConditionWay(destination, departure, [condition]() { return false == condition(); });
		return *this;
	}
}