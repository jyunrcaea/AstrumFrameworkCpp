#include "AstrumStateGraph.hpp"
#include <format>
#include "AstrumException.hpp"

bool AstrumStateGraph::AddStateName(const std::string& name) {
	if (statusGraph.contains(name)) return false;
	statusGraph[name] = std::vector<AstrumStateGraph::ConditionLine>();
	return true;
}

bool AstrumStateGraph::AddStateName(const std::string& name, const std::function<void(AstrumStatusType)>& callback) {
	if (false == AddStateName(name)) return false;
	statusCallback[name] = callback;
	return true;
}

std::function<void(AstrumStatusType)>& AstrumStateGraph::GetCallback(const std::string name) {
	return statusCallback[name];
}
const std::unordered_map<std::string, std::vector<AstrumStateGraph::ConditionLine>>& AstrumStateGraph::GetGraph() const {
	return statusGraph;
}
