#include <algorithm>
#if defined(__ANDROID__)
#define GH_EXPORT __attribute__((visibility("default")))
#else
#define GH_EXPORT
#endif
extern "C" {
GH_EXPORT float gh_clamp_speed(float speed,float maximum) {
    return std::max(-maximum,std::min(speed,maximum));
}
}
