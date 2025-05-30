#include "Psilent.hpp"

void PSilent::Choke(uintptr_t netChannel) {
    Write<double>(netChannel + 0x2108, 999999);
}
void PSilent::ForceChoke(double Packet) {
    uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
    printf("Net Channel %u\n", netChannel);
    Write<double>(netChannel + 0x2108, Packet);
}
void PSilent::ChokeLoop() {
    uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
    uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);

    int attack_state = Read<int>(sdk.R5Apex + 0x077bfce0 + 0x64);
    if (chokedCommands > 7) {
        Write<double>(netChannel + 0x2108, 0);
        return;
    }
    if (attack_state != 0) {

        if (chokedCommands == 0) {
            Choke(netChannel);
        }
    }
    else
    {
        if (chokedCommands != 0)
            ForceChoke(0);
    }

}
void PSilent::BackTrack()
{
    uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
    uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);
    Silent->ChokeLoop();
    if (chokedCommands <= 0)
    {
        Silent->Choke(0);
        return;
    }
    int current_number = Read<int>(sdk.R5Apex + LatestCommandNumber);
    int iDesiredCmdNumber = current_number + 1;
    uint64_t cmdBase = Read<uint64_t>(sdk.R5Apex + pCommands + 248);
    uint64_t old_usercmd = (cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber - 1) % 750)));
    uint64_t Currentusercmd = cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber) % 750));
    Write<float>(Currentusercmd + 0x8, 50);
    Silent->ForceChoke(0);
}
void PSilent::SilentAim(Vector2 CalAngle) {

    uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + pCommands);
    //ChokeLoop();
    uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);
    if (chokedCommands <= 0)
        return;
    
    int current_number = Read<int>(sdk.R5Apex + LatestCommandNumber);
    int iDesiredCmdNumber = current_number + 1;
    uint64_t cmdBase = Read<uint64_t>(sdk.R5Apex + pCommands + 248);
    uint64_t old_usercmd = (cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber - 1) % 750)));
    uint64_t Currentusercmd = cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber) % 750));
    if (Currentusercmd > iDesiredCmdNumber)
    {
        ChokeLoop();
        Write<Vector2>(old_usercmd + 0xC, Vector2(CalAngle.x, CalAngle.y));
        Write<double>(netChannel + 0x2108, 0);
    }
}

void CodeCallback_OnWeaponAttack::address_to_bytes(uintptr_t address, uint8_t* bytes) {
    for (int i = 0; i < 8; ++i) {
        bytes[i] = (address >> (i * 8)) & 0xFF;
    }
}
bool CodeCallback_OnWeaponAttack::Create(Vector2 dir)
{
    
    return true;
}
bool CodeCallback_OnWeaponAttack::restore()
{
    return false;
}

void ShotDirection::Set_ShotDirection(Vector3 dir)
{
   //removed ofc

}