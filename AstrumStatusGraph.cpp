#include "AstrumStatusGraph.hpp"
#include <format>
#include "AstrumException.hpp"

bool AstrumStatusGraph::AddStatusName(const std::string& name) {
	if (statusGraph.contains(name)) return false;
	statusGraph[name] = std::vector<AstrumStatusGraph::ConditionLine>();
	return true;
}

bool AstrumStatusGraph::AddStatusName(const std::string& name, const std::function<void(AstrumStatusType)>& callback) {
	if (false == AddStatusName(name)) return false;
	statusCallback[name] = callback;
	return true;
}

std::function<void(AstrumStatusType)>& AstrumStatusGraph::GetCallback(const std::string name) {
	return statusCallback[name];
}
const std::unordered_map<std::string, std::vector<AstrumStatusGraph::ConditionLine>>& AstrumStatusGraph::GetGraph() const {
	return statusGraph;
}
