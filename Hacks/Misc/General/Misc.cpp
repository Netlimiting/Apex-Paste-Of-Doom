#include "Misc.hpp"
#define TICK_INTERVAL            (1.0f)


#define TIME_TO_TICKS( dt )        ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )        ( TICK_INTERVAL ( t ) )
#define ROUND_TO_TICKS( t )        ( TICK_INTERVAL TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK        (-1)

#if defined( TF_DLL )
#define ANIMATION_CYCLE_BITS        10
#else
#define ANIMATION_CYCLE_BITS        15
#endif
#define ANIMATION_CYCLE_MINFRAC        (1.0f / (1<<ANIMATION_CYCLE_BITS))
template< class T >
T Max(T const& val1, T const& val2)
{
    return val1 > val2 ? val1 : val2;
}

void SetTimeScale(float flTimeBase)
{
    const int nRemainderTime = Max(TIME_TO_TICKS(flTimeBase), 0);
    Write<float>(sdk.LocalPlayer->getAddress() + 0x1c68,(nRemainderTime));

    //const float flAttemptedTime = Max(flTimeBase - (Read<float>(sdk.LocalPlayer->getAddress() + 0x1c68) * TICK_INTERVAL), 0.0f);
    //Write<float>(sdk.LocalPlayer->getAddress() + 0x1c64,flAttemptedTime);
}




void Misc::NoRecoil() {
    if (!Cheat_Private::Aimbot::VABot || (Cheat_Private::Aimbot::VABot && !GetAsyncKeyState(Cheat_Private::Aimbot::AimbotKey))) {
        Vector3 angles;
        angles.y = Read<float>((uintptr_t)sdk.LocalPlayer + Offsets::DT_Player::m_viewOffEntity);
        angles.x = Read<float>((uintptr_t)sdk.LocalPlayer + Offsets::DT_Player::m_viewOffEntity + sizeof(float));
        Vector2 punch = sdk.LocalPlayer->Get_Punch();

        if ((punch.y < 0 || punch.x < 0) && GetAsyncKeyState(VK_LBUTTON)) {
            angles.x -= (punch.y - previousYaw) * (1);
            angles.y -= (punch.x - previousPitch) * (1);
            Write<float>((uintptr_t)sdk.LocalPlayer + Offsets::DT_Player::m_viewOffEntity, angles.y);
            Write<float>((uintptr_t)sdk.LocalPlayer + Offsets::DT_Player::m_viewOffEntity + sizeof(float), angles.x);
            previousPitch = punch.x;
            previousYaw = punch.y;
        }
    }
}
void Misc::doBigMapRadar()
{
    while (true)
    {
        if (!Cheat_Private::Misc::BigMapRadar || !inMatch)return;
        for (auto& Entity : EntList)
        {
            int localPlayerTeamID = sdk.LocalPlayer->Get_TeamNum();
            if (localPlayerTeamID != 1) {
                float curTime = Read<float>(sdk.LocalPlayer->getAddress() + Offsets::Misc::m_WorldTime);
                double continueTime = 0.2;
                float endTime = curTime + continueTime;
                while (curTime < endTime)
                {
                    Write<int>(sdk.LocalPlayer->getAddress() + Offsets::DT_BaseEntity::m_m_iTeamNum, 1);
                    curTime = Read<float>(Entity.ClassAccess->getAddress() + Offsets::Misc::m_WorldTime);
                }
                curTime = Read<float>(Entity.ClassAccess->getAddress() + Offsets::Misc::m_WorldTime);
                endTime = curTime + continueTime;
                while (curTime < endTime)
                {
                    Write<int>(Entity.ClassAccess->getAddress() + Offsets::DT_BaseEntity::m_m_iTeamNum, localPlayerTeamID);
                    curTime = Read<float>(Entity.ClassAccess->getAddress() + Offsets::Misc::m_WorldTime);
                }
            }
        } 
    }
}


void Misc::doExploits() {
    while (true) {
        static float oldanimationpackets = 0;
        static bool wasAnimation = false;

        if (!sdk.LocalPlayer || !inMatch) continue;
        auto Projectile = sdk.LocalPlayer->Get_Projectile();
        if (!Projectile) continue;
   

        if (Cheat_Private::Misc::NoAnimation) {
            if (!oldanimationpackets) {
                oldanimationpackets = sdk.LocalPlayer->Get_AnimationMask();
            }
            sdk.LocalPlayer->Set_AnimationMask(modelstate.crouch);
            wasAnimation = true;
        }

        if (!Cheat_Private::Misc::NoAnimation && wasAnimation) {
            sdk.LocalPlayer->Set_AnimationMask(oldanimationpackets);
            oldanimationpackets = NULL;
            wasAnimation = false;
        }

        if (Cheat_Private::Misc::NoSpread) {
            if (Projectile->Get_CrosshairSpread() != 0) {
                Projectile->Set_CrosshairSpread(0);
            }
            if (Projectile->Get_SpreadRaidus() != 0) {
                Projectile->Set_SpreadRadius(0);
            }
        }
        if (Cheat_Private::Misc::ForceBullets)
        {
            //if (Projectile->IsSemi() && GetAsyncKeyState(0x01))
                //driver::mouseclick(1, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        }
        if (Cheat_Private::Misc::FakeDuck) {
            if (GetAsyncKeyState(Cheat_Private::Misc::KafeDuckBIND)) {
                Write<int>(sdk.R5Apex + Offsets::Misc::m_DUCK, duck.start);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                Write<int>(sdk.R5Apex + Offsets::Misc::m_DUCK, duck.finish);
            }
        }
    }
}
void Misc::doSizeChanger(SDK::Entity* Entity) {
    
    if (Cheat_Private::Misc::LargePlayers) {
        Entity->Set_HitBoxSize(1.08f);
    }
    if (Cheat_Private::Misc::LargeWeapon) {
        Entity->Set_WeaponSize(3.9f);
    }
}
void Misc::DoMisc() {
    static bool didBright = false;
    static bool WasThirdperson = false;
    static bool Once = true;
    static bool wasbigMapRadar = true;

    if (Cheat_Private::Misc::WeaponGlow) {
        gl.weapon_glow();
    }

    if (Cheat_Private::Misc::HandGlow) {
        gl.hand_glow();
    }

    if (Cheat_Private::Misc::FullBright && !didBright) {
        Write<int>(sdk.R5Apex + Offsets::Misc::m_ForceBright, 1);
        didBright = true;
    }

    if (!Cheat_Private::Misc::FullBright && didBright) {
        Write<int>(sdk.R5Apex + Offsets::Misc::m_ForceBright, 0);
        didBright = false;
    }

    if (Cheat_Private::Misc::Clfps) {
        Write<int>(sdk.R5Apex + Offsets::Misc::m_clData, 1);
    }

    if (Cheat_Private::Misc::CharacterSkinChanger) {
        sdk.LocalPlayer->Set_CharacterSkin(Cheat_Private::Misc::CharacterSkin);
    }

    if (Cheat_Private::Misc::Thirdperson) {
        if (GetAsyncKeyState(Cheat_Private::Misc::ThirdPeronKey))
            sdk.LocalPlayer->Do_ThirdPerson();
        else
            sdk.LocalPlayer->Reset_ThirdPerson();
    }

    if (Cheat_Private::Misc::FovChanger) {
        float fov = static_cast<float>(Cheat_Private::Misc::SetFov / 100.0f);
        sdk.LocalPlayer->Set_Fov(fov);
    }

    if (Cheat_Private::Misc::zoom && GetAsyncKeyState(Cheat_Private::Misc::zoomkey)) {
        sdk.LocalPlayer->Set_Fov(.4f);
    }

    if (Cheat_Private::Aimbot::RcsControl) {
        NoRecoil();
    }

    if (Cheat_Private::Misc::SuperGlide) {
        static float startjumpTime = 0;
        static bool startSg = false;

        float WorldTime = sdk.LocalPlayer->Get_WorldTime();
        float m_traversalStartTime = sdk.LocalPlayer->Get_TraversalStartTime();
        float m_traversalProgress = sdk.LocalPlayer->Get_TraversalProgress();
        auto HangOnWall = -(m_traversalStartTime - WorldTime);

        if (GetAsyncKeyState(Cheat_Private::Misc::SuperGliderkey)) {
            if (m_traversalProgress > 0.87f && !startSg && HangOnWall > 0.05f && HangOnWall < 1.5f) {
                startjumpTime = WorldTime;
                startSg = true;
            }

            if (startSg) {

                Write<int>(sdk.R5Apex + Offsets::Misc::m_JUMP, jump.start);
                if ((WorldTime - startjumpTime) > 0.007) {
                    Write<int>(sdk.R5Apex + Offsets::Misc::m_DUCK, duck.start);
                }
            }

            if ((WorldTime - startjumpTime) > 1.5f && startSg) {
                Write<int>(sdk.R5Apex + Offsets::Misc::m_JUMP, jump.finish);
                Write<int>(sdk.R5Apex + Offsets::Misc::m_DUCK, duck.finish);
                startSg = false;
            }
        }
    }

    if (Cheat_Private::Misc::PlayerModelSpoof) {
        sdk.LocalPlayer->Set_ServerModelState(modelstate.crouch);
    }

    if (Cheat_Private::Misc::Freecam) {
        if (GetAsyncKeyState(Cheat_Private::Misc::FreeCamBind))
            sdk.LocalPlayer->Set_ObserverMode(observerstate.freecam);
        else
            sdk.LocalPlayer->Set_ObserverMode(observerstate.none);
    }

    if (Cheat_Private::Misc::SkinChanger) {
        sdk.LocalPlayer->SetSkin(Cheat_Private::Misc::SkinID);
    }

    if (Cheat_Private::Misc::AutoGrapple) {
        if (GetAsyncKeyState(0x51)) { // Q
            Write<int>(sdk.R5Apex + Offsets::Misc::m_JUMP, jump.start);
            auto GrappleState = sdk.LocalPlayer->Get_GrappleState();
            if (GrappleState == 1) {
                Write<int>(sdk.R5Apex + Offsets::Misc::m_JUMP, jump.dojump);
            }
        }
    }

    if (Cheat_Private::Misc::ItemGlow && Once) {
        std::thread(&Glow::ItemGlow, gl).detach();
        Once = false;
    }
    if (Cheat_Private::Misc::BigMapRadar && !wasbigMapRadar)
    {
        std::thread(doBigMapRadar);
        wasbigMapRadar = true;
    }
    else if (!Cheat_Private::Misc::BigMapRadar && wasbigMapRadar)
        wasbigMapRadar = false;

}