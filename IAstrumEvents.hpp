#pragma once

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