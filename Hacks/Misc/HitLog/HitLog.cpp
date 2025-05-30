#include "HitLog.hpp"
//chat generated
void HitLog::DrawKillText(const std::vector<KillInfo>& kills) {
    float startX = 10.0f;
    float startY = 150;
    float offsetY = 20.0f;
    //goofy ass feature 
    for (size_t i = 0; i < kills.size(); ++i) {
        const KillInfo& kill = kills[i];
        std::string text = _("Killed : ") + kill.name;

        Draw::esp->draw_text_outline_font(startX, startY + i * offsetY, ImColor(255, 255, 255, 255), text.c_str(), 1.f);
    }
}
void HitLog::UpdateKills() {
    auto currentTime = std::chrono::steady_clock::now();
    killList.erase(std::remove_if(killList.begin(), killList.end(),
        [currentTime](const KillInfo& kill) {
            return currentTime > kill.expirationTime;
        }),
        killList.end());
}
void HitLog::HandleKillEvent(float KillTime, const std::string& EntityName) {
    if (KillTime > PreviousKillTime) {
        PlaySound(_("Hitsound.wav"), GetModuleHandleA(NULL), SND_FILENAME | SND_ASYNC);

        KillInfo newKill;
        newKill.name = EntityName;
        newKill.expirationTime = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        killList.push_back(newKill);

        PreviousKillTime = KillTime;
    }
}
void HitLog::doHitLog(SDK::Entity* LocalPlayer, SDK::Entity* Entity, int Entity_Index)
{
    float KillTime = LocalPlayer->LastKillTime();
    std::string Name = Entity->GetName(Entity_Index);

    HandleKillEvent(KillTime, Name);

    UpdateKills();
    DrawKillText(killList);
}
SDK::Entity* HitLog::HitBestEnt() {
    float closest = FLT_MAX;
    SDK::Entity* bestEnt = nullptr;
    int Bone = 0;

    int screenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
    int screenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
    float maxFovDistanceSquared = 250.0f;

    for (auto& curEnt : EntList) {
        if (!(uintptr_t)curEnt.ClassAccess)continue;

        float worldTime = Read<float>(sdk.LocalPlayer->getAddress() + Offsets::Misc::m_WorldTime);
        float entityTime1 = Read<float>(curEnt.ClassAccess->getAddress() + Offsets::Misc::m_lastVisibleTime);
        bool vis = (entityTime1 + 0.2f) >= worldTime;
        if (!vis)
            continue;

        Vector3 bonePos = curEnt.ClassAccess->GetBonePositionByHitBox(1);
        Vector3 TargetPos = W2S(bonePos);

        if (TargetPos.Empty()) continue;

        float deltaX = screenCenterX - TargetPos.x;
        float deltaY = screenCenterY - TargetPos.y;
        float lengthSquared = deltaX * deltaX + deltaY * deltaY;

        if (lengthSquared < closest&& lengthSquared <= maxFovDistanceSquared) {
            closest = lengthSquared;
            bestEnt = curEnt.ClassAccess;
        }
    }

    return bestEnt;
}
void HitLog::UpdateHitData() {
    auto currentTime = std::chrono::steady_clock::now();
    size_t beforeSize = hit_data.size();
    hit_data.erase(std::remove_if(hit_data.begin(), hit_data.end(),
        [currentTime](const hitdata& hit) {
            bool isExpired = currentTime > hit.expirationTime;
            printf("Checking expiration: Current time: %lld, Expiration time: %lld, Is expired: %d\n",
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count(),
                std::chrono::duration_cast<std::chrono::milliseconds>(hit.expirationTime.time_since_epoch()).count(),
                isExpired);
            return isExpired;
        }),
        hit_data.end());
}
void HitLog::doHitSound() {
    while (true) {
        if (!Cheat_Private::Misc::hitSound || !sdk.LocalPlayer || EntList.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        auto Entity = HitBestEnt();
        if (!Entity) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (lastEntity != Entity) {
            oldHealth = FLT_MAX;
            oldShotTime = 0;
            oldShield = FLT_MAX;
            lastEntity = Entity;
        }

        uint64_t primary_weapons_latest = Read<uint64_t>((uintptr_t)sdk.LocalPlayer + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
        uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
        int shotTime = Read<int>((uintptr_t)primary_weapons_list + Offsets::Misc::m_CurrentAmmo);
        int currentHealth = Entity->Current_Health();
        int currentShield = Entity->Get_Current_shield();

        if (shotTime > oldShotTime && (currentHealth < oldHealth || currentShield < oldShield)) {
            if (oldHealth != FLT_MAX && oldShield != FLT_MAX) {
                PlaySound(_("C:\\Hitsound.wav"), GetModuleHandleA(nullptr), SND_FILENAME | SND_ASYNC);
             /*   Vector3 Position = Entity->GetBonePositionByHitBox(3);
                Vector3 hitPosition{ Position.x, Position.y,Position.z };
                hitdata data{ hitPosition, false, std::chrono::steady_clock::now() + std::chrono::seconds(2) };
                hit_data.push_back(data);*/

            }
            oldHealth = currentHealth;
            oldShield = currentShield;
            oldShotTime = shotTime;
        }
        oldShotTime = shotTime;
    }
}
void HitLog::DrawHitLine(const std::vector<hitdata>& hit_data) {
    for (const auto& hit : hit_data) {
        std::string text = _("Hit");
        ImVec2 size = ImGui::CalcTextSize(text.c_str());
        Vector3 Screen = W2S(hit.Position);
        Draw::esp->draw_text_outline_font(Screen.x - (size.x / 2), Screen.y - (size.y / 2), ImColor(255, 255, 255, 255), text.c_str(), 1.f);
    }
}
void HitLog::doHitData() {
    DrawHitLine(hit_data);
}