#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>
#include <algorithm>
#include "AstrumStateBuilder.hpp"

// Enter는 양의 정수, Exit는 음의 정수임을 보장합니다.
enum AstrumStateType
{
	AstrumStatusType_Exit = -1,
	AstrumStatusType_None = 0,
	AstrumStatusType_Enter = 1,
};

// 상태 그래프 인터페이스
struct IAstrumStateGraph
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
	virtual bool AddStateName(const std::string& name) = 0;
	virtual bool AddStateName(const std::string& name, const std::function<void(AstrumStateType)>& callback) = 0;
	// 상태 정점을 여러개 추가합니다. 이미 생성된건 무시합니다.
	virtual void AddStateNames(const std::initializer_list<std::string>& names) = 0;
	virtual bool SetCallback(const std::string& name, const std::function<void(AstrumStateType)>& callback) = 0;
	virtual std::function<void(AstrumStateType)>& GetCallback(const std::string& name) = 0;
	// 상태 그래프를 (읽기 전용으로) 가져옵니다.
	virtual const std::unordered_map<std::string, std::vector<ConditionLine>>& GetGraph() const = 0;
	virtual const std::vector<ConditionLine>& GetLines(const std::string from) = 0;
	// 임의로 콜백을 호출합니다. (성공시 true, 함수가 존재하지 않으면 false)
	virtual bool InvokeCallback(const std::string& name, AstrumStateType type) = 0;
	virtual void AddConditionWay(const std::string& from, const std::string& to, const std::function<bool()>& condition) = 0;
};