#pragma once
#include "AstrumVector3.hpp"
#include <memory>

struct IAstrumPrepareEvent {
    virtual void Prepare() = 0;
    virtual ~IAstrumPrepareEvent() = default;
};
struct IAstrumUpdateEvent {
    virtual void Update() = 0;
    virtual ~IAstrumUpdateEvent() = default;
};
struct IAstrumDrawEvent {
    virtual void Draw() = 0;
    virtual ~IAstrumDrawEvent() = default;
};
struct IAstrumReleaseEvent {
    virtual void Release() = 0;
    virtual ~IAstrumReleaseEvent() = default;
};

struct IAstrumObject : public IAstrumPrepareEvent, IAstrumUpdateEvent, IAstrumDrawEvent, IAstrumReleaseEvent {
    virtual ~IAstrumObject() = default;

    virtual AstrumVector3& GetPosition() = 0;
    virtual AstrumVector3& GetRotation() = 0;
    virtual AstrumVector3& GetScale() = 0;

    virtual bool IsVisible() const = 0;
    virtual IAstrumObject* GetParent() const = 0;

    virtual bool SetParent(IAstrumObject* parent) = 0;
    virtual bool ClearParent(IAstrumObject* parent) = 0;
};
