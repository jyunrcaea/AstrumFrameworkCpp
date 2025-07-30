#pragma once
#include "AstrumComponent.hpp"
#include "AstrumStateGraph.hpp"

// to do : not tested yet.
class AstrumStateComponent : public AstrumComponent
{
public:
	AstrumStateComponent(const std::string& starting);
	AstrumStateComponent(const std::string& starting, const std::shared_ptr<AstrumStateGraph>& graph);

	virtual void Update() override;
	void SetStateGraph(const std::string& starting, const std::shared_ptr<AstrumStateGraph>& graph);

private:
	std::string state;
	std::shared_ptr<AstrumStateGraph> stateGraph = nullptr;

	bool UpdateState();

public:
	static std::shared_ptr<AstrumStateComponent> MakeShared(const std::string& starting) {
		return std::make_shared<AstrumStateComponent>(starting);
	}
	static std::shared_ptr<AstrumStateComponent> MakeShared(const std::string& starting, const std::shared_ptr<AstrumStateGraph>& graph) {
		return std::make_shared<AstrumStateComponent>(starting, graph);
	}
};