#pragma once
#include "../Objects/IAstrumObject.hpp"

struct IAstrumObject;

struct IAstrumComponent
{
	virtual ~IAstrumComponent() = default;

	virtual void Prepare() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void PreRender() = 0;

	virtual void SetOwner(IAstrumObject* owner) = 0;
	virtual IAstrumObject* GetOwner() const = 0;
};