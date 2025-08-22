#pragma once
#include "AstrumComponent.hpp"
#include "../States/AstrumStateGraph.hpp"

namespace Astrum
{
	// to do : not tested yet.
	class StateComponent : public Component
	{
	public:
		StateComponent(const std::string& starting);
		StateComponent(const std::string& starting, const std::shared_ptr<StateGraph>& graph);

		virtual void Update() override;
		void SetStateGraph(const std::string& starting, const std::shared_ptr<StateGraph>& graph);

	private:
		std::string state;
		std::shared_ptr<StateGraph> stateGraph = nullptr;

		bool UpdateState();

	public:
		static std::shared_ptr<StateComponent> MakeShared(const std::string& starting) {
			return std::make_shared<StateComponent>(starting);
		}
		static std::shared_ptr<StateComponent> MakeShared(const std::string& starting, const std::shared_ptr<StateGraph>& graph) {
			return std::make_shared<StateComponent>(starting, graph);
		}
	};
}