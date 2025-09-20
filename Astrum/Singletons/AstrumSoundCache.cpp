#include "AstrumSoundCache.hpp"

void AstrumSoundCacheSingleton::CleanUp() {
    for (auto it = soundMap.begin(); it != soundMap.end();) {
        if (it->second.use_count() <= 1) {
            it = soundMap.erase(it);
        } else {
            ++it;
        }
    }
}
