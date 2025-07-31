#pragma once
#include <span>
#include "AstrumConstantBuffer.hpp"
#include "../Vectors/AstrumVector4.hpp"

class AstrumColorConstantBuffer : public AstrumConstantBuffer
{
public:
	AstrumColorConstantBuffer();
	
	AstrumVector4 Data{ 1.f, 1.f, 1.f, 1.f };

	void UpdateBuffer();
};