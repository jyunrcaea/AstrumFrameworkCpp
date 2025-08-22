#include "AstrumStateGraph.hpp"

namespace Astrum
{
	bool StateGraph::AddStateName(const std::string& name) {
		if (stateGraph.contains(name)) return false;
		stateGraph[name] = std::vector<StateGraph::ConditionLine>();
		return true;
	}

	bool StateGraph::AddStateName(const std::string& name, const std::function<void(EStateType)>& callback) {
		if (false == AddStateName(name)) return false;
		stateCallback[name] = callback;
		return true;
	}

	void StateGraph::AddStateNames(const std::initializer_list<std::string>& names) {
		auto it = names.begin();
		auto itEnd = names.end();
		while (it != itEnd) {
			AddStateName(*it++);
		}
	}

	void StateGraph::AddConditionWay(const std::string& from, const std::string& to, const std::function<bool()>& condition) {
		stateGraph[from].emplace_back(from, to, condition);
	}

	bool StateGraph::SetCallback(const std::string& name, const std::function<void(EStateType)>& callback) {
		if (false == stateGraph.contains(name)) return false;

		stateCallback[name] = callback;
		return true;
	}

	std::function<void(EStateType)>& StateGraph::GetCallback(const std::string& name) {
		return stateCallback[name];
	}
	const std::unordered_map<std::string, std::vector<StateGraph::ConditionLine>>& StateGraph::GetGraph() const {
		return stateGraph;
	}

	const std::vector<StateGraph::ConditionLine>& StateGraph::GetLines(const std::string from) {
		return stateGraph[from];
	}

	bool StateGraph::InvokeCallback(const std::string& name, EStateType type) {
		if (false == stateCallback.contains(name)) {
			return false;
		}
		stateCallback[name](type);
		return true;
	}

	StateBuilder StateGraph::MakeStateBuilder(const std::string& name) {
		return StateBuilder(static_cast<IStateGraph*>(this), name);
	}
}
