#pragma once
#include <typeinfo>

template <typename T>
struct AstrumType {
public:
	static const char* GetName() {
		return typeid(T).name();
	}
};