#include "AstrumStateGraph.hpp"

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

void AstrumStateGraph::AddStateNames(const std::initializer_list<std::string>& names) {
	auto it = names.begin();
	auto itEnd = names.end();
	while (it != itEnd) {
		AddStateName(*it++);
	}
}

void AstrumStateGraph::AddConditionWay(const std::string& from,const std::string& to, const std::function<bool()>& condition) {
	stateGraph[from].emplace_back(from, to, condition);
}

bool AstrumStateGraph::SetCallback(const std::string& name, const std::function<void(AstrumStateType)>& callback) {
	if (false == stateGraph.contains(name)) return false;

	stateCallback[name] = callback;
	return true;
}

std::function<void(AstrumStateType)>& AstrumStateGraph::GetCallback(const std::string& name) {
	return stateCallback[name];
}
const std::unordered_map<std::string, std::vector<AstrumStateGraph::ConditionLine>>& AstrumStateGraph::GetGraph() const {
	return stateGraph;
}

const std::vector<AstrumStateGraph::ConditionLine>& AstrumStateGraph::GetLines(const std::string from) {
	return stateGraph[from];
}

bool AstrumStateGraph::InvokeCallback(const std::string& name, AstrumStateType type) {
	if (false == stateCallback.contains(name)) {
		return false;
	}
	stateCallback[name](type);
	return true;
}

AstrumStateBuilder AstrumStateGraph::MakeStateBuilder(const std::string& name) {
	return AstrumStateBuilder(static_cast<IAstrumStateGraph*>(this), name);
}
