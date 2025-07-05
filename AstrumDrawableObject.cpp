#include "AstrumDrawableObject.hpp"
#include <DirectXMath.h>

void AstrumDrawableObject::Draw() {
    AstrumRenderer::Instance().EnqueueRenderable(shared_from_this());
}

void AstrumDrawableObject::Render() { }

void AstrumDrawableObject::Rendering() {
    AstrumMatrix scaleMat, rotMat, transMat;

    scaleMat.Scaling(scale);
    rotMat.Rotation(rotation);
    transMat.Translation(position);

    transformBuffer.World = scaleMat * rotMat * transMat;

    transformBuffer.Projection = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XM_PIDIV2, 1280.0f / 720.0f, 0.5f, 1000.0f);

    transformBuffer.UpdateBuffer();

    Render();
}