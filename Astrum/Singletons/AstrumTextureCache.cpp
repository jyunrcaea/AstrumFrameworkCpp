#include "AstrumTextureCache.hpp"

void AstrumTextureCacheSingleton::CleanUp() {
    for (auto it = textureMap.begin(); it != textureMap.end();) {
        if (it->second.use_count() <= 1) {
            it = textureMap.erase(it);
        } else {
            ++it;
        }
	}
}