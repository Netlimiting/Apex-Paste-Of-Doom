#include "../MovementTrace/MovementTrace.hpp"


class AmmoCounter {
public:
    bool isReloadingPreviously = false;
    bool hasReloadingStarted = false;
    std::chrono::steady_clock::time_point reloadStartTime;
    float reloadTime = 0.0f;
    void UpdateReloadingStatus(bool IsReloading);
    ImU32 interpolateColor(ImU32 colorStart, ImU32 colorEnd, float factor);
    void Render();
    void DoAmmoCounter();
}; inline AmmoCounter ammo;