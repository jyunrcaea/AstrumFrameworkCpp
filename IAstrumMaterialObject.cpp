#include "IAstrumMaterialObject.hpp"

std::shared_ptr<AstrumTexture> IAstrumMaterialObject::GetTexture() { return GetMaterial()->GetTexture(); }