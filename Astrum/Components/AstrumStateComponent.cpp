#include "AstrumStateComponent.hpp"

namespace Astrum
{
	StateComponent::StateComponent(const std::string& starting) : state(starting) {}
	StateComponent::StateComponent(const std::string& starting, const std::shared_ptr<StateGraph>& graph)
		: state(starting), stateGraph(graph) {}

	void StateComponent::Update() {
		while (UpdateState());
		Component::Update();
	}

	void StateComponent::SetStateGraph(const std::string& starting, const std::shared_ptr<StateGraph>& graph) {
		if (nullptr != stateGraph) {
			stateGraph->InvokeCallback(state, StateType::StatusType_Exit);
			stateGraph = nullptr;
		}

		stateGraph = graph;
		state = starting;
	}

	bool StateComponent::UpdateState() {
		if (nullptr == stateGraph) return false;

		for (auto& line : stateGraph->GetLines(state)) {
			if (line.Condition && line.Condition()) {
				stateGraph->InvokeCallback(line.From, StateType::StatusType_Exit);
				state = line.To;
				stateGraph->InvokeCallback(line.To, StateType::StatusType_Enter);
				return true;
			}
		}

		return false;
	}
}