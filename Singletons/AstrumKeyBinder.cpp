#include "AstrumKeyBinder.hpp"
#include "AstrumDirectInput.hpp"

AstrumKeyBinderSingleton::AstrumKeyBinderSingleton() {}

bool AstrumKeyBinderSingleton::AddKeyBind(const std::string& name, uint8_t key) {
	auto& target = name2key[name];
	for (auto k : target.keys) {
		if (k == key) return false;
	}
	target.keys.push_back(key);

	return true;
}

bool AstrumKeyBinderSingleton::RemoveKeyBind(const std::string& name, uint8_t key) {
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

bool AstrumKeyBinderSingleton::IsKeyPressed(const std::string& name) {
	return name2key[name].pressed;
}

void AstrumKeyBinderSingleton::Update() {
	for (auto& [_, tag] : name2key) {
		tag.pressed = false;
		for (auto k : tag.keys) {
			if (AstrumDirectInput::IsKeyPressed(k)) {
				tag.pressed = true;
				break;
			}
		}
	}
}