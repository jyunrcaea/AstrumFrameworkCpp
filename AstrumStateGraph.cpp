#include "AstrumStateGraph.hpp"
#include <format>
#include "AstrumException.hpp"

bool AstrumStateGraph::AddStateName(const std::string& name) {
	if (stateGraph.contains(name)) return false;
	stateGraph[name] = std::vector<AstrumStateGraph::ConditionLine>();
	return true;
}

bool AstrumStateGraph::AddStateName(const std::string& name, const std::function<void(AstrumStateType)>& callback) {
	if (false == AddStateName(name)) return false;
	stateCallback[name] = callback;
	return true;
}

std::function<void(AstrumStateType)>& AstrumStateGraph::GetCallback(const std::string name) {
	return stateCallback[name];
}
const std::unordered_map<std::string, std::vector<AstrumStateGraph::ConditionLine>>& AstrumStateGraph::GetGraph() const {
	return stateGraph;
}

const std::vector<AstrumStateGraph::ConditionLine>& AstrumStateGraph::GetLines(const std::string from) {
	return stateGraph[from];
}

void AstrumStateGraph::InvokeCallback(const std::string& name, AstrumStateType type) {
	stateCallback[name](type);
}
