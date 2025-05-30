#include "Aimbot.hpp"

SDK::Entity* Aimbot::GetBestEntity() {
   
    float closest = FLT_MAX;
    SDK::Entity* bestEnt = nullptr;

    float maxFovDistanceSquared = Cheat_Private::Aimbot::FovCircleSize * Cheat_Private::Aimbot::FovCircleSize;
    auto localPos = sdk.LocalPlayer->Get_Position();

    for (auto& curEnt : EntList) {
        auto diffPos = curEnt.ClassAccess->Get_Position();

        float Distance = calcDist(localPos, diffPos) / 39.f;

        if (Distance > Cheat_Private::Settings::AimbotDistance) continue;

        if (curEnt.ClassAccess->BleedOutState() > 0 && Cheat_Private::Aimbot::DisableKnocked || curEnt.ClassAccess->Current_Health() == 0)continue;
        if (curEnt.ClassAccess->Get_TeamNum() == sdk.LocalPlayer->Get_TeamNum() && Cheat_Private::Aimbot::DisableTeam) continue;


        bool vis = (curEnt.ClassAccess->Get_LastVisibleTime() + 0.2f) >= sdk.LocalPlayer->Get_WorldTime();
        if (Cheat_Private::Aimbot::VisCheck && !vis)
            continue;

        Vector3 bonePos = curEnt.ClassAccess->GetBonePositionByHitBox(Cheat_Private::Aimbot::SelectedBone);
        Vector3 TargetPos = W2S(bonePos);

        if (TargetPos.Empty()) continue;

        float deltaX = (sdk.DisplaySize.x / 2) - TargetPos.x;
        float deltaY = (sdk.DisplaySize.y / 2) - TargetPos.y;
        float lengthSquared = deltaX * deltaX + deltaY * deltaY;

        if (lengthSquared < closest && lengthSquared <= maxFovDistanceSquared) {
            closest = lengthSquared;
            bestEnt = curEnt.ClassAccess;
        }
    }

       return bestEnt;
}
void writeShotDirection(int64_t weaponHandle, Vector3 direction) {
   //removed for obvious reasons
}

void Aimbot::DoAimbot()
{
    static SDK::Entity* Entity = NULL;
    float progress = 0.0f;
    float increment = 0.05f;

    if (!GetAsyncKeyState(Cheat_Private::Aimbot::AimbotKey) && Cheat_Private::Aimbot::HardLock)
        Entity = GetBestEntity();
    else if (!Cheat_Private::Aimbot::HardLock)
        Entity = GetBestEntity();

    if (!Entity)return;

    Vector3 BonePosition = Entity->GetBonePositionByHitBox(Cheat_Private::Aimbot::SelectedBone);
    if (BonePosition.Empty()) return;
    Vector3 TargetPos = W2S(BonePosition);
    if (TargetPos.Empty()) return;

    if (Cheat_Private::Settings::ControllerSupport)
        xbox.GetState();

    Vector3 OldAngle = Vector3();
    Vector3 LocalPlayereyes = Read<Vector3>((uintptr_t)sdk.LocalPlayer + 0x1ee0);
    Vector3 ViewAngles = sdk.LocalPlayer->ViewAngles();
    if (GetAsyncKeyState(Cheat_Private::Aimbot::AimbotKey) || (xbox.isLeftTrigger() && Cheat_Private::Settings::ControllerSupport))
    {
        if (Cheat_Private::Aimbot::Predication)
        {
            Vector2 angl;
            CalcAnglePredictives(LocalPlayereyes, BonePosition, Read<Vector3>(Entity->getAddress() + 0x0170),
                sdk.LocalPlayer->Get_Projectile()->Get_ProjectileSpeed(),sdk.LocalPlayer->Get_Projectile()->Get_ProjectileGravity(),255,angl);
            OldAngle = { angl.x,angl.y,0 };

        }
        else
            OldAngle = CalcAngle(LocalPlayereyes, BonePosition);

        if (Cheat_Private::Aimbot::RcsControl)
        {
            Vector2 punch = sdk.LocalPlayer->Get_Punch();
            if (punch.y < 0 || punch.x < 0) {
                OldAngle.x -= (punch.x - previousPitch) * pitchSTR;
                OldAngle.y -= (punch.y - previousYaw) * yawSTR;
            }
        }

        Vector3 ViewAngles = sdk.LocalPlayer->ViewAngles();

        Vector3 delta = OldAngle - ViewAngles;

        delta.Normalize();

        if (Cheat_Private::Aimbot::SmoothingAmount != 1)
        {
            delta.y /= Cheat_Private::Aimbot::SmoothingAmount * 2;
            delta.x /= Cheat_Private::Aimbot::SmoothingAmount * 2;
        }
       
        if (Cheat_Private::Aimbot::PSilent)
        {
          // removed ofc
        }

        while (progress < 1.0f && Cheat_Private::Aimbot::VABot) {
            Vector3 curvedDelta = ApplyCurvature(delta, progress);
            if (Cheat_Private::Aimbot::VABot)
            {
               sdk.LocalPlayer->SetViewAngles(Vector2(ViewAngles.x + delta.x, ViewAngles.y + delta.y));
              
            }
           
           
            progress += increment;
        }
        if (Cheat_Private::Aimbot::AutoFire)
        {
           // driver::mouseclick(10, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        }
   
    }

    if (Cheat_Private::Aimbot::Snapline)
    {
        ImVec2 Size = ImGui::CalcTextSize(_("X"));
        Draw::esp->draw_text_outline_font(TargetPos.x - (Size.x / 2), TargetPos.y - (Size.y / 2), ImColor(Cheat_Private::Aimbot::SnaplineColor[0], Cheat_Private::Aimbot::SnaplineColor[1], Cheat_Private::Aimbot::SnaplineColor[2], 255.f), _("X"), 1.0f);
        Draw::esp->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), ImVec2(TargetPos.x, TargetPos.y), ImColor(Cheat_Private::Aimbot::SnaplineColor[0], Cheat_Private::Aimbot::SnaplineColor[1], Cheat_Private::Aimbot::SnaplineColor[2], 255.f), 1.0f);
    }

}