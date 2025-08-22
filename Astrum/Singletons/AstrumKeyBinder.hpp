#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <dinput.h>
#include "AstrumSingleton.hpp"

namespace Astrum {
	class KeyBinder;

	class KeyBinderSingleton : public Singleton<KeyBinderSingleton>
	{
		friend class Singleton<KeyBinderSingleton>;
		friend class KeyBinder;
		KeyBinderSingleton();

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

	class KeyBinder
	{
		KeyBinder() = delete;
	public:
		inline static bool AddKeyBind(const std::string& name, uint8_t key) { return KeyBinderSingleton::Instance().AddKeyBind(name, key); }
		inline static bool RemoveKeyBind(const std::string& name, uint8_t key) { return KeyBinderSingleton::Instance().RemoveKeyBind(name, key); }
		inline static bool IsKeyPressed(const std::string& name) { return KeyBinderSingleton::Instance().IsKeyPressed(name); }
		inline static void Update() { KeyBinderSingleton::Instance().Update(); }
	};
}