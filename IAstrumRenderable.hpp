#pragma once

struct IAstrumRenderable {
    virtual ~IAstrumRenderable() = default;
    virtual void Render() = 0;

protected:
	friend class AstrumRenderer;

    virtual void Rendering() = 0;
};