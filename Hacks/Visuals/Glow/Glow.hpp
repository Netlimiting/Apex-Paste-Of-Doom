#include "../../Hacks/Misc/HitLog/HitLog.hpp"

#define OFF_GLOW_HIGHLIGHTS 0x7568E80
#define OFF_GLOW_ENABLE 0x26c
#define OFF_GLOW_THROUGH_WALL 0x26c
#define OFF_GLOW_HIGHLIGHT_ID 0x29C
#define OFF_HIGHLIGHT_TYPE_SIZE 0x34
#define OFF_GLOW_FIX 0x278
#define OFF_GLOW_DISTANCE 0x294

inline uintptr_t highlightsettingsa = 0;

class Glow {
public:
    void weapon_glow();
    void hand_glow();
    void ItemGlow();
    void SetColor(SDK::Entity* Entity, bool vis);
    void DisableGlow(uintptr_t entity);
}; inline Glow gl;
