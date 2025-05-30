#include "../../Misc/General/Misc.hpp"
#define pCommands  0x23BDA90//48 89 05 69 93 15 02
#define LatestCommandNumber  0x190DBBC 
#define NetChannel  0x18ECE20  


class PSilent {
public:
    void Choke(uintptr_t netChannel);
    void ForceChoke(double Packet);
    void ChokeLoop();
    void SilentAim(Vector2 CalAngle);
    void BackTrack();
}; inline PSilent* Silent;

class ShotDirection {
public:
    void Set_ShotDirection(Vector3 dir);
}; inline ShotDirection* shot = new ShotDirection;

class CodeCallback_OnWeaponAttack {
public:
    std::uint64_t CodeCallback_OnWeaponAttack_OFFSET = 0x0;
    bool isHooked = false;
    std::uint64_t hookAddress = 0x0;
    std::uint64_t hookJMP = 0x0;
    std::uint64_t RedirectHook = 0x0;
    static void address_to_bytes(uintptr_t address, uint8_t* bytes);
    bool Create(Vector2 dir);
    bool restore();
}; inline CodeCallback_OnWeaponAttack* onAttack = new CodeCallback_OnWeaponAttack;