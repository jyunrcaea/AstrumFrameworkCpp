#pragma once
#include "../Units/AstrumMatrix.hpp"

struct alignas(16) AstrumTransformData {
    AstrumMatrix World;
    AstrumMatrix View;
    AstrumMatrix Projection;
    AstrumMatrix WorldView;
    AstrumMatrix WorldViewProjection;
};