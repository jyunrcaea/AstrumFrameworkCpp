#pragma once
#include "IAstrumStateGraph.hpp"
#include "AstrumStateBuilder.hpp"

class AstrumStateGraph : public IAstrumStateGraph
{
public:
	virtual bool AddStateName(const std::string& name) override;
	virtual bool AddStateName(const std::string& name, const std::function<void(AstrumStateType)>& callback) override;
	virtual void AddStateNames(const std::initializer_list<std::string>& names) override;

	// 한 정점에서 다른 정점으로 이동하는 조건 간선을 추가합니다.
	template<typename FromType, typename ToType, typename ConditionType>
	requires std::convertible_to<FromType, std::string>&& std::convertible_to<ToType, std::string>&& std::convertible_to<ConditionType, std::function<bool()>>
	void AddConditionWay(FromType&& from, ToType&& to, ConditionType&& condition) {
		stateGraph[from].emplace_back(std::forward<FromType>(from), std::forward<ToType>(to), std::forward<ConditionType>(condition));
	}
	virtual void AddConditionWay(const std::string& from,const std::string& to, const std::function<bool()>& condition) override;
	virtual bool SetCallback(const std::string& name, const std::function<void(AstrumStateType)>& callback) override;
	virtual std::function<void(AstrumStateType)>& GetCallback(const std::string& name) override;
	virtual const std::unordered_map<std::string, std::vector<ConditionLine>>& GetGraph() const override;
	virtual const std::vector<ConditionLine>& GetLines(const std::string from) override;
	virtual bool InvokeCallback(const std::string& name, AstrumStateType type) override;

	AstrumStateBuilder MakeBuilder(const std::string& name);
private:
	std::unordered_map<std::string,std::vector<ConditionLine>> stateGraph;
	std::unordered_map<std::string, std::function<void(AstrumStateType)>> stateCallback;

public:
	static std::shared_ptr<AstrumStateGraph> MakeShared() { return std::make_shared<AstrumStateGraph>(); }
};