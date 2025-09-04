#include "AstrumTextureCache.hpp"

void AstrumTextureCacheSingleton::CleanUp() {
    for (auto it = textureMap.begin(); it != textureMap.end();) {
        if (it->second.expired()) {
            it = textureMap.erase(it);
        } else {
            ++it;
        }
	}
}