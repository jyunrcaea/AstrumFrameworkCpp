#include "AstrumStateComponent.hpp"

AstrumStateComponent::AstrumStateComponent(const std::string& starting) : state(starting) {}
AstrumStateComponent::AstrumStateComponent(const std::string& starting, const std::shared_ptr<AstrumStateGraph>& graph)
	: state(starting), stateGraph(graph) {}

void AstrumStateComponent::Update() {
	while (UpdateState());
	AstrumComponent::Update();
}

void AstrumStateComponent::SetStateGraph(const std::string& starting, const std::shared_ptr<AstrumStateGraph>& graph) {
	if (nullptr != stateGraph) {
		stateGraph->InvokeCallback(state, AstrumStateType::AstrumStatusType_Exit);
		stateGraph = nullptr;
	}

	stateGraph = graph;
	state = starting;
}

bool AstrumStateComponent::UpdateState() {
	if (nullptr == stateGraph) return false;

	for (auto& line : stateGraph->GetLines(state)) {
		if (line.Condition && line.Condition()) {
			stateGraph->InvokeCallback(line.From, AstrumStateType::AstrumStatusType_Exit);
			state = line.To;
			stateGraph->InvokeCallback(line.To, AstrumStateType::AstrumStatusType_Enter);
			return true;
		}
	}

	return false;
}