#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

class AstrumStatusGraph
{
public:
	struct ConditionLine
	{
		std::string From;
		std::string To;
		std::function<bool()> Condition;
	};

public:
	void AddStatusName(const std::string& name);
	void AddConditionWay(const std::string& from, const std::string& to, std::function<bool()> condition);

	const std::vector<std::vector<ConditionLine>>& GetGraph() const;
private:
	std::vector<std::string> statusNames;
	std::unordered_map<std::string, int> name2index;
	std::vector<std::vector<ConditionLine>> statusGraph;
};