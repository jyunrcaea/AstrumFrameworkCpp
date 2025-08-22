#pragma once
#include <memory>
#include <functional>
#include "AstrumConstantBuffer.hpp"

namespace Astrum {
	class SimpleConstantBuffer : public ConstantBuffer
	{
	public:
		SimpleConstantBuffer(const std::function<void(ConstantBuffer*)>& update, unsigned int size)
			: ConstantBuffer(size), updateFunction(update) { }

		virtual void UpdateBuffer() override {
			if (updateFunction) updateFunction(this);
		}
	private:
		std::function<void(ConstantBuffer*)> updateFunction;

	public:
		static std::shared_ptr<SimpleConstantBuffer> MakeShared(const std::function<void(ConstantBuffer*)>& update, unsigned int size) {
			return std::make_shared<SimpleConstantBuffer>(update, size);
		}
	};
}