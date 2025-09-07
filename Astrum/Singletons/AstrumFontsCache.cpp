#include "AstrumFontsCache.hpp"

void AstrumFontsCacheSingleton::CleanUp() {
    for (auto it = fontsMap.begin(); it != fontsMap.end();) {
        if (it->second.expired()) {
            it = fontsMap.erase(it);
        }
        else {
            ++it;
        }
    }
}