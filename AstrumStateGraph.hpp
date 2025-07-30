#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

enum AstrumStatusType
{
	AstrumStatusType_Exit = -1,
	AstrumStatusType_None = 0,
	AstrumStatusType_Enter = 1,
};

// 상태 그래프
class AstrumStateGraph
{
public:
	struct ConditionLine
	{
		std::string From;
		std::string To;
		std::function<bool()> Condition;
	};

public:
	// 상태 정점을 추가합니다.
	bool AddStateName(const std::string& name);
	bool AddStateName(const std::string& name, const std::function<void(AstrumStatusType)>& callback);
	// 한 정점에서 다른 정점으로 이동하는 조건 간선을 추가합니다.
	template<typename FromType, typename ToType, typename ConditionType>
	requires std::convertible_to<FromType, std::string>&& std::convertible_to<ToType, std::string>&& std::convertible_to<ConditionType, std::function<bool()>>
	void AddConditionWay(FromType&& from, ToType&& to, ConditionType&& condition) {
		statusGraph[from].emplace_back(std::forward(from), std::forward(to), std::forward(condition));
	}

	std::function<void(AstrumStatusType)>& GetCallback(const std::string name);
	// 상태 그래프를 (읽기 전용으로) 가져옵니다.
	const std::unordered_map<std::string, std::vector<ConditionLine>>& GetGraph() const;

private:
	std::unordered_map<std::string,std::vector<ConditionLine>> statusGraph;
	std::unordered_map<std::string, std::function<void(AstrumStatusType)>> statusCallback;

public:
	static std::shared_ptr<AstrumStateGraph> MakeShared() { return std::make_shared<AstrumStateGraph>(); }
};