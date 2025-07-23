#pragma once
#include <memory>
#include "IAstrumEvents.hpp"
#include "IAstrumObject.hpp"

struct IAstrumObject;

struct IAstrumComponent : public IAstrumPrepareEvent, public IAstrumUpdateEvent, public IAstrumReleaseEvent
{
public:
	virtual ~IAstrumComponent() = default;
	virtual void SetOwner(IAstrumObject* owner) = 0;
	virtual IAstrumObject* GetOwner() const = 0;
};