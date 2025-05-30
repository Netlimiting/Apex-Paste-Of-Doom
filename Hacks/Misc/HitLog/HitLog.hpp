#include "../../Misc/AmmoCounter/AmmoCounter.hpp"

struct KillInfo {
    std::string name;
    std::chrono::steady_clock::time_point expirationTime;
};

struct MovementInfo {
    std::vector<Vector2> Positions;
    std::chrono::steady_clock::time_point expirationTime;
};

class HitLog {
public:
    float PreviousKillTime = 0.0f;
    std::vector<KillInfo> killList;
    struct _Time { _int64 time; };
    struct hitdata { Vector3 Position; bool Headshot; std::chrono::steady_clock::time_point expirationTime; };
    float oldHealth = FLT_MAX;
    _int64 oldShotTime = 0;
    int oldShield = FLT_MAX;
    SDK::Entity* lastEntity = nullptr;
    std::vector<hitdata> hit_data;

    void DrawKillText(const std::vector<KillInfo>& kills);
    void UpdateKills();
    void HandleKillEvent(float KillTime, const std::string& EntityName);
    void doHitLog(SDK::Entity* LocalPlayer, SDK::Entity* Entity, int Entity_Index);
    SDK::Entity* HitBestEnt();
    void UpdateHitData();
    void doHitSound();
    void DrawHitLine(const std::vector<hitdata>& hit_data);
    void doHitData();
}; inline HitLog hl;

