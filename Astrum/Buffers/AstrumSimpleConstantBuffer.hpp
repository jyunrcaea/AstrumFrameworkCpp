#pragma once
#include <memory>
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

public:
	static std::shared_ptr<AstrumSimpleConstantBuffer> MakeShared(const std::function<void(AstrumConstantBuffer*)>& update, unsigned int size) {
		return std::make_shared<AstrumSimpleConstantBuffer>(update, size);
	}
};