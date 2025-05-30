#include "Player.hpp"
void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
    ImGui::GetBackgroundDrawList()->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
    ImGui::GetBackgroundDrawList()->PathStroke(col, false, thickness);
}
void Player::RunCheat()
{
    if (!sdk.LocalPlayer || !inMatch) return;

    visentcount = 0;

    auto localPos = sdk.LocalPlayer->Get_Position();

    for (const PlayerData& Entity : EntList) {

        auto diffPos = Entity.ClassAccess->Get_Position();

        if (localPos.equals(diffPos))continue;

        float Distance = calcDist(localPos, diffPos) / 39.f;

        if (Distance > Cheat_Private::Settings::RenderDistance) continue;
        if (Entity.ClassAccess->BleedOutState() > 0 && Cheat_Private::ESP::KnockedCheck || Entity.ClassAccess->Current_Health() == 0)continue;

        bool isTeam = false;
        bool isKnocked = false;

        Entity.ClassAccess->Get_TeamNum() == sdk.LocalPlayer->Get_TeamNum() ? isTeam = true : isTeam = false;
        Entity.ClassAccess->BleedOutState() > 0 ? isKnocked = true : isKnocked = false;

        if (Cheat_Private::ESP::Teamcheck && isTeam) continue;

        Vector3 Position = Entity.ClassAccess->Get_Position();


        bool isVisible = (Entity.ClassAccess->Get_LastVisibleTime() + 0.2f) >= sdk.LocalPlayer->Get_WorldTime();

        if (isVisible) visentcount++;

        gl.SetColor(Entity.ClassAccess, isVisible);

        esp.DrawEsp(Entity, isVisible, Distance, isTeam, isKnocked);

        misc.doSizeChanger(Entity.ClassAccess);

        if (Cheat_Private::ESP::OFFArrow)
        {
            float width = 5.f;
            auto va = sdk.LocalPlayer->ViewAngles();
            Vector3 LocalPlayereyes = Read<Vector3>((uintptr_t)sdk.LocalPlayer + 0x1ee0);
            auto angle = va.y - CalcAngle(LocalPlayereyes, Position).y - 90;
            ImColor offColor = ImColor(Cheat_Private::ESP::OFFArrowColor[0], Cheat_Private::ESP::OFFArrowColor[1], Cheat_Private::ESP::OFFArrowColor[2], 255.0f);
            if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[10])
            {
                isVisible
                    ? offColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                    : offColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
            }
            if (isKnocked && Cheat_Private::ESP::KnockedDraw)
                offColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

            if (isTeam && Cheat_Private::ESP::RemoveTeam)
                offColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);

            arc(sdk.DisplaySize.x / 2, sdk.DisplaySize.y / 2, (Cheat_Private::ESP::OFFRadius * 5), angle - width, angle + width, offColor, 4.f);
        }
    }

    if (Cheat_Private::ESP::alert)
    {
        std::string txt = std::string(_("[WARNING] ") + std::to_string(visentcount) + _(" VISIBLE PLAYERS"));
        ImVec2 size = ImGui::CalcTextSize(txt.c_str());
        Draw::esp->draw_text_outline_font(sdk.DisplaySize.x / 2 - (size.x / 2), sdk.DisplaySize.y / 2.7 - (size.y / 2), ImColor{ 255,255,255,255 }, txt.c_str(), 1.0f);
    }

    if (Cheat_Private::ESP::Radar)
        radar.doRadar();

    if (Cheat_Private::Misc::AmmoCounter || Cheat_Private::Misc::ReloadBar)
        ammo.DoAmmoCounter();

    if (Cheat_Private::Aimbot::VABot || Cheat_Private::Aimbot::PSilent || Cheat_Private::Aimbot::skyNade)
        aimbot.DoAimbot();

    misc.DoMisc();

    if (Cheat_Private::ESP::DisplayDeathBox)
    {
        for (auto& deathbox : DeathboxList)
        {
            auto pos = deathbox->Get_Position();
            float Distance = calcDist(localPos, pos) / 39.f;
            if (Distance > Cheat_Private::Settings::RenderDistance) continue;

            auto screen = W2S(pos);
            if (screen.Empty())continue;
            struct BoxDimensions {
                int width;
                int height;
                int yheight;
            };

            BoxDimensions weaponBox = { 110, 60, 150 };

            int boxX = pos.x - (weaponBox.width / 2);
            int boxY = pos.y + weaponBox.yheight + 5;
            int flippedBoxY = boxY - weaponBox.height - 5;


            Draw::menu->DrawRotatedImageWithBox(DeathBoxIcon::DeathBoxTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);

        }
    }

    if (Cheat_Private::Misc::BackTrack)
        Silent->BackTrack();
}

void Player::sendEntityPositions()
{
   
}

void Player::RunWebRadar()
{
  
}