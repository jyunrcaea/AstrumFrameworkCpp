#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include "AstrumSingleton.hpp"

class AstrumKeyBinderSingleton : public AstrumSingleton<AstrumKeyBinderSingleton>
{
	friend class AstrumSingleton<AstrumKeyBinderSingleton>;
	friend class AstrumKeyBinder;
	AstrumKeyBinderSingleton();

	struct KeyBindTag
	{
		std::vector<uint8_t> keys;
		bool pressed = false;
	};

public:
	bool AddKeyBind(const std::string& name, uint8_t key);
	bool RemoveKeyBind(const std::string& name, uint8_t key);
	bool IsKeyPressed(const std::string& name);
	void Update();

private:
	std::unordered_map<std::string, KeyBindTag> name2key;
};

class AstrumKeyBinder
{
	AstrumKeyBinder() = delete;
public:
	inline static bool AddKeyBind(const std::string& name, uint8_t key) { return AstrumKeyBinderSingleton::Instance().AddKeyBind(name, key); }
	inline static bool RemoveKeyBind(const std::string& name, uint8_t key) { return AstrumKeyBinderSingleton::Instance().RemoveKeyBind(name, key); }
	inline static bool IsKeyPressed(const std::string& name) { return AstrumKeyBinderSingleton::Instance().IsKeyPressed(name); }
	inline static void Update() { AstrumKeyBinderSingleton::Instance().Update(); }
};