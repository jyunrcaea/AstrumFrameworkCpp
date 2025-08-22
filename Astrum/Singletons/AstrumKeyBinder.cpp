#include "AstrumKeyBinder.hpp"
#include "AstrumDirectInput.hpp"

namespace Astrum {
	KeyBinderSingleton::KeyBinderSingleton() {}

	bool KeyBinderSingleton::AddKeyBind(const std::string& name, uint8_t key) {
		auto& target = name2key[name];
		for (auto k : target.keys) {
			if (k == key) return false;
		}
		target.keys.push_back(key);

		return true;
	}

	bool KeyBinderSingleton::RemoveKeyBind(const std::string& name, uint8_t key) {
		auto& target = name2key[name];
		const auto itEnd = target.keys.end();
		for (auto it = target.keys.begin(); it != itEnd; ++it) {
			if (*it == key) {
				target.keys.erase(it);
				return true;
			}
		}

		return false;
	}

	bool KeyBinderSingleton::IsKeyPressed(const std::string& name) {
		return name2key[name].pressed;
	}

	void KeyBinderSingleton::Update() {
		for (auto& [_, tag] : name2key) {
			tag.pressed = false;
			for (auto k : tag.keys) {
				if (DirectInput::IsKeyPressed(k)) {
					tag.pressed = true;
					break;
				}
			}
		}
	}
}