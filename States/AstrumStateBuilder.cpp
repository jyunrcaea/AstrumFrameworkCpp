#include "AstrumStateBuilder.hpp"

AstrumStateBuilder::AstrumStateBuilder(IAstrumStateGraph* graph, const std::string& name)
	: departure(name), stateGraph(graph) {
	stateGraph->AddStateName(name);
}

AstrumStateBuilder& AstrumStateBuilder::SetCallback(const std::function<void(AstrumStateType)>& callback) {
	stateGraph->SetCallback(departure, callback);
	return *this;
}

AstrumStateBuilder& AstrumStateBuilder::AddConditionWay(const std::string& destination, const std::function<bool()>& condition) {
	stateGraph->AddConditionWay(departure, destination, condition);
	return *this;
}

AstrumStateBuilder& AstrumStateBuilder::AddHoldConditionTwoWay(const std::string& destination, const std::function<bool()>& condition) {
	stateGraph->AddConditionWay(departure, destination, condition);
	stateGraph->AddConditionWay(destination, departure, [condition]() { return false == condition();  });
	return *this;
}