#include "AstrumFontsCache.hpp"

void AstrumFontsCacheSingleton::CleanUp() {
    for (auto it = fontsMap.begin(); it != fontsMap.end();) {
        if (it->second.use_count() <= 1) {
            it = fontsMap.erase(it);
        }
        else {
            ++it;
        }
    }
}