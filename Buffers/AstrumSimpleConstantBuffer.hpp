#pragma once
#include <functional>
#include "AstrumConstantBuffer.hpp"

class AstrumSimpleConstantBuffer : public AstrumConstantBuffer
{
public:
	AstrumSimpleConstantBuffer(const std::function<void(AstrumConstantBuffer*)>& update, unsigned int size)
		: AstrumConstantBuffer(size), updateFunction(update) { }

	virtual void UpdateBuffer() override {
		if (updateFunction) updateFunction(this);
	}
private:
	std::function<void(AstrumConstantBuffer*)> updateFunction;
};