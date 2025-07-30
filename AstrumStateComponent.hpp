#pragma once
#include "AstrumComponent.hpp"
#include "AstrumStateGraph.hpp"

// to do : not implement yet.
class AstrumStateComponent : public AstrumComponent
{
public:
	AstrumStateComponent() {}
	AstrumStateComponent(const std::shared_ptr<AstrumStateGraph>& graph) : statusGraph(graph) {}

	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;

private:
	std::shared_ptr<AstrumStateGraph> statusGraph = nullptr;
};