#include "Esp.hpp"

void Esp::DrawEsp(PlayerData Entity, bool vis, float Distance, bool isTeamate, bool isKnocked)
{
    auto Player = Entity.ClassAccess;

    Vector3 BasePos = Player->Get_Position();
    BasePos.z -= 3;
    if (BasePos.Empty()) return;

    Vector3 LocalPos = sdk.LocalPlayer->Get_Position();

    Vector3 HeadPosition = Player->GetBonePositionByHitBox(0);

    if (HeadPosition.Empty())
        HeadPosition = Player->GetBonePositionByHitBox(1);

    HeadPosition.z += 8;

    if (HeadPosition.Empty()) return;

    Vector3 Pos = W2S(BasePos);
    Vector3 HeadPos = W2S(HeadPosition);

    if (Pos.Empty() || HeadPos.Empty()) return;

    int Height = (HeadPos.y - Pos.y);
    int Width = Height / 1.3;


    if (Cheat_Private::ESP::Filledbox)
        Draw::esp->DrawFilledBox(Pos.x - (Width / 2), Pos.y, Width, Height, ImColor((Cheat_Private::ESP::FilledBoxColor[0]), (Cheat_Private::ESP::FilledBoxColor[1]),(Cheat_Private::ESP::FilledBoxColor[2]), 125.f), .5f);


    if (Cheat_Private::ESP::Box)
    {
        ImColor boxColor = ImColor{ Cheat_Private::ESP::BoxColor[0], Cheat_Private::ESP::BoxColor[1], Cheat_Private::ESP::BoxColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[0])
        {
            vis
                ? boxColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : boxColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }

        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            boxColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            boxColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);


        Draw::esp->DrawBox(Pos.x - (Width / 2), Pos.y, Width, Height, ImColor(0, 0, 0, 255), 3);
        Draw::esp->DrawBox(Pos.x - (Width / 2), Pos.y, Width, Height, boxColor, .1f);

    }
    if (Cheat_Private::ESP::WeaponICON)
        WpIcon.DoWeaponIcon(Pos, Player, vis);

    if (Cheat_Private::ESP::CornerBox)
    {
        Draw::esp->DrawCorneredBox(Pos.x - (Width / 2), Pos.y, Width, Height, ImColor(0, 0, 0, 255), 2.f);

        ImColor cornerBoxColor = ImColor{ Cheat_Private::ESP::BoxColor[0], Cheat_Private::ESP::BoxColor[1], Cheat_Private::ESP::BoxColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[0])
        {
            vis
                ? cornerBoxColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : cornerBoxColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }

        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            cornerBoxColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            cornerBoxColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);

        Draw::esp->DrawCorneredBox(Pos.x - (Width / 2), Pos.y, Width, Height, cornerBoxColor, .5f);
    }
    if (Cheat_Private::ESP::PeterGriffen)
    {
        Draw::menu->DrawRotatedImageWithBox(Peter_Texture, Pos.x - (Width / 2), Pos.y, Width, Height);
    }
    if (Cheat_Private::ESP::EKitten)
    {
        Draw::menu->DrawRotatedImageWithBox(SexyGirlTexture, Pos.x - (Width / 2), Pos.y, Width, Height);
    }

    // Drawing SernEsp
    if (Cheat_Private::ESP::SernEsp && Distance <= 100)
    {
        Draw::esp->SeerHealth(HeadPos.x, HeadPos.y, Player->Get_Current_shield(), Player->Get_Max_shield(), Player->Get_shield_type(), Player->Current_Health());
    }



    if (Cheat_Private::ESP::Level)
    {
        if (!Cheat_Private::ESP::Distance)
        {
            std::string levelText = std::to_string(int(Player->Get_Level())) + _("LV");
            ImVec2 sizeLevel = ImGui::CalcTextSize(levelText.c_str());

            ImColor levelColor = ImColor{ Cheat_Private::ESP::LevelColor[0], Cheat_Private::ESP::LevelColor[1], Cheat_Private::ESP::LevelColor[2], 255.f };

            if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[6])
            {
                vis
                    ? levelColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                    : levelColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
            }

            if (isKnocked && Cheat_Private::ESP::KnockedDraw)
                levelColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

            if (isTeamate && Cheat_Private::ESP::RemoveTeam)
                levelColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);

            int offset = Cheat_Private::ESP::Distance ? -sizeLevel.x / 2 : 0;

            Draw::esp->draw_text_outline_font(Pos.x - (sizeLevel.x / 2), (Pos.y - (sizeLevel.y / 2)) + 10, levelColor, levelText.c_str(), 1);
        }
    }
    if (Cheat_Private::ESP::Snapline)
    {
        ImColor SnaplineColor = ImColor{ Cheat_Private::ESP::SnaplineColor[0], Cheat_Private::ESP::SnaplineColor[1], Cheat_Private::ESP::SnaplineColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[9])
        {
            vis
                ? SnaplineColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : SnaplineColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }
        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            SnaplineColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            SnaplineColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);
        switch (Cheat_Private::ESP::SnaplineIndex)
        {
        case 0: // top
            Draw::esp->AddLine(ImVec2(sdk.DisplaySize.x / 2, 0), ImVec2(HeadPos.x, HeadPos.y), SnaplineColor, .01f);
            break;
        case 1: // center
            Draw::esp->AddLine(ImVec2(sdk.DisplaySize.x / 2, sdk.DisplaySize.y / 2), ImVec2(HeadPos.x, HeadPos.y), SnaplineColor, .01f);
            break;
        case 2: // bottom
            Draw::esp->AddLine(ImVec2(sdk.DisplaySize.x / 2, sdk.DisplaySize.y), ImVec2(HeadPos.x, HeadPos.y), SnaplineColor, .01f);
            break;
        }
    }
    // Drawing Distance Text
    if (Cheat_Private::ESP::Distance)
    {
        std::string distanceText = std::to_string(int(Distance)) + _("M");
        ImVec2 sizeDistance = ImGui::CalcTextSize(distanceText.c_str());

        ImColor distanceColor = ImColor{ Cheat_Private::ESP::DistanceColor[0], Cheat_Private::ESP::DistanceColor[1], Cheat_Private::ESP::DistanceColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[3])
        {
            vis
                ? distanceColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : distanceColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }

        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            distanceColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            distanceColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);

        int offset = Cheat_Private::ESP::Level ? sizeDistance.x / 2 : 0;

        if (Cheat_Private::ESP::Level)
        {
            std::string NewText = std::to_string(int(Player->Get_Level())) + _("LV") + _(" : ") + distanceText;
            ImVec2 sizeLevel = ImGui::CalcTextSize(NewText.c_str());
            Draw::esp->draw_text_outline_font(Pos.x - (sizeLevel.x / 2), (Pos.y - (sizeLevel.y / 2)) + 10, distanceColor, NewText.c_str(), 1);
        }
        else {
            Draw::esp->draw_text_outline_font(Pos.x - (sizeDistance.x / 2), (Pos.y - (sizeDistance.y / 2)) + 10, distanceColor, distanceText.c_str(), 1);
        }
    }

    // Drawing weapon ESP
    if (Cheat_Private::ESP::Name)
    {
        std::string nameText = Entity.ClassAccess->get_weapon_name();
        ImVec2 size = ImGui::CalcTextSize(nameText.c_str());

        ImColor nameColor = ImColor{ Cheat_Private::ESP::NameColor[0], Cheat_Private::ESP::NameColor[1], Cheat_Private::ESP::NameColor[2], 255.f };
        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[7])
        {
            vis
                ? nameColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : nameColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }
        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            nameColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            nameColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);
        if (Cheat_Private::ESP::Weapon)
        {
            if (Cheat_Private::ESP::Operator)
            {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 40, nameColor, nameText.c_str(), 1);
            }
            else {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 25, nameColor, nameText.c_str(), 1);
            }
        }
        else {
            if (Cheat_Private::ESP::Operator)
            {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 25, nameColor, nameText.c_str(), 1);
            }
            else {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 10, nameColor, nameText.c_str(), 1);
            }

        }
    }

    // Drawing Operator ESP
    if (Cheat_Private::ESP::Operator)
    {
        std::string operatorText = Player->GetOperator();
        ImVec2 size = ImGui::CalcTextSize(operatorText.c_str());

        ImColor operatorColor = ImColor{ Cheat_Private::ESP::OperatorColor[0], Cheat_Private::ESP::OperatorColor[1], Cheat_Private::ESP::OperatorColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[5])
        {
            vis
                ? operatorColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : operatorColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }
        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            operatorColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            operatorColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);
        if (Cheat_Private::ESP::Weapon)
        {
            if (Cheat_Private::ESP::Name)
            {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 25, operatorColor, operatorText.c_str(), 1);
            }
            else {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 25, operatorColor, operatorText.c_str(), 1);
            }
        }
        else {
            if (Cheat_Private::ESP::Name)
            {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 10, operatorColor, operatorText.c_str(), 1);
            }
            else {
                Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 10, operatorColor, operatorText.c_str(), 1);
            }
        }
    }
    // Name
    if (Cheat_Private::ESP::Weapon)
    {
        std::string nameText = Entity.name;
        ImVec2 size = ImGui::CalcTextSize(nameText.c_str());

        ImColor nameColor = ImColor{ Cheat_Private::ESP::WeaponColor[0], Cheat_Private::ESP::WeaponColor[1], Cheat_Private::ESP::WeaponColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[4])
        {
            vis
                ? nameColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : nameColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }
        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            nameColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            nameColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);
        Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 10, nameColor, nameText.c_str(), 1);
    }

    // Draw Shield Bar


    if (Cheat_Private::ESP::Health) {
        {

            float spec = Pos.x - (Width / 2.2f);
            int Health = Player->Current_Health();
            ImColor healthColor = Health > 75 ? ImColor(0, 255, 0, 255) : Health > 45 ? ImColor(255, 99, 0, 255) : ImColor(255, 0, 0, 255);

            float barWidth = 2.0f; // Make the bar slightly wider for better visibility
            ImVec2 barPosMin = ImVec2(spec + Width * 1.1f, Pos.y);
            ImVec2 barPosMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + Height);

            ImGui::GetBackgroundDrawList()->AddRectFilled({ barPosMin.x - 2, barPosMin.y + 2 }, { barPosMax.x + 2, barPosMax.y - 2 }, ImColor(0, 0, 0, 255));
            ImGui::GetBackgroundDrawList()->AddRectFilled(barPosMin, barPosMax, ImColor(0, 0, 0, 255));
            ImGui::GetBackgroundDrawList()->AddRect(barPosMin, barPosMax, ImColor(255, 255, 255, 150));

            float healthBarHeight = Health * Height / 100.0f;
            ImVec2 healthBarMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + healthBarHeight);

            ImColor gradientStart = ImColor(healthColor.Value.x, healthColor.Value.y, healthColor.Value.z, 0.2f);
            ImColor gradientEnd = ImColor(healthColor.Value.x, healthColor.Value.y, healthColor.Value.z, 1.0f);

            ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(barPosMin, healthBarMax, gradientStart, gradientStart, gradientEnd, gradientEnd);
        }
    }
    if (Cheat_Private::ESP::Shield)
    {
        float spec = Pos.x - (Width / 2.2f);
        int shield = Player->Get_Current_shield();
        int shieldType = Player->Get_shield_type();
        ImColor shieldColor;
        bool drawShield = true;
        switch (shieldType)
        {
        case 5: shieldColor = ImColor(200, 15, 50); break;
        case 4: shieldColor = ImColor(205, 195, 50); break;
        case 3: shieldColor = ImColor(150, 65, 245); break;
        case 2: shieldColor = ImColor(25, 115, 175); break;
        case 1: shieldColor = ImColor(215, 215, 215); break;
        default: drawShield = false; break;
        }
        //chat generated
        if (drawShield && shield != 0)
        {
            float barWidth = 2.0f; 
            ImVec2 barPosMin = ImVec2(spec + Width * 1.1f, Pos.y);
            ImVec2 barPosMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + Height);

            ImGui::GetBackgroundDrawList()->AddRectFilled({ barPosMin.x - 2, barPosMin.y + 2 }, { barPosMax.x + 2, barPosMax.y - 2 }, ImColor(0, 0, 0, 255));

            ImGui::GetBackgroundDrawList()->AddRectFilled(barPosMin, barPosMax, ImColor(0, 0, 0, 255));
            ImGui::GetBackgroundDrawList()->AddRect(barPosMin, barPosMax, ImColor(255, 255, 255, 150)); 

            float shieldBarHeight = shield * Height / 125.0f;
            ImVec2 shieldBarMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + shieldBarHeight);

            ImColor gradientStart = ImColor(shieldColor.Value.x, shieldColor.Value.y, shieldColor.Value.z, 0.2f); 
            ImColor gradientEnd = ImColor(shieldColor.Value.x, shieldColor.Value.y, shieldColor.Value.z, 1.0f); 

            ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(barPosMin, shieldBarMax, gradientStart, gradientStart, gradientEnd, gradientEnd);
        }
    }
    if (Cheat_Private::ESP::HeadCircle)
    {
        Vector3 tempHead = Player->GetBonePositionByHitBox(0);
        Vector3 tempNeck = Player->GetBonePositionByHitBox(1);

        Vector3 Head = W2S(tempHead);
        Vector3 Neck = W2S(tempNeck);

        float radius = std::hypot(Head.x - Neck.x, Head.y - Neck.y);

        ImColor HeadColor = ImColor{ Cheat_Private::ESP::HeadCircleColor[0], Cheat_Private::ESP::HeadCircleColor[1], Cheat_Private::ESP::HeadCircleColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[2])
        {
            vis
                ? HeadColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : HeadColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }
        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            HeadColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            HeadColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);

        if (!Head.Empty() || !Neck.Empty())
        {
            ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Head.x, Head.y), radius * 1.3 + 1, ImColor(0, 0, 0, 255));
            ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Head.x, Head.y), radius * 1.3, HeadColor);
        }
    }
    if (Cheat_Private::ESP::Skeleton)
    {
        //chat generated
        ImColor skeletonColor = ImColor{ Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f };

        if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[1])
        {
            vis
                ? skeletonColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : skeletonColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
        }


        if (Cheat_Private::ESP::SkeletonGay)
        {
            static int colorStage = 0;
            static float r = 1.0f, g = 0.0f, b = 1.0f;

            switch (colorStage) {
            case 0: r -= 0.005f; if (r <= 0) colorStage++; break;
            case 1: g += 0.005f; b -= 0.005f; if (g >= 1) colorStage++; break;
            case 2: r += 0.005f; if (r >= 1) colorStage++; break;
            case 3: b += 0.005f; g -= 0.005f; if (b >= 1) colorStage = 0; break;
            default: r = 1.0f; g = 0.0f; b = 1.0f; break;
            }
            skeletonColor = { r,g,b,255.0f };
        }

        if (isKnocked && Cheat_Private::ESP::KnockedDraw)
            skeletonColor = ImColor(Cheat_Private::ESP::KnockedColor[0], Cheat_Private::ESP::KnockedColor[1], Cheat_Private::ESP::KnockedColor[2], 255.f);

        if (isTeamate && Cheat_Private::ESP::RemoveTeam)
            skeletonColor = ImColor(Cheat_Private::ESP::TeamColor[0], Cheat_Private::ESP::TeamColor[1], Cheat_Private::ESP::TeamColor[2], 255.f);
        //Base
        Vector3 tempHead = Player->GetBonePositionByHitBox(0);
        Vector3 tempNeck = Player->GetBonePositionByHitBox(1);
        Vector3 tempUpperChest = Player->GetBonePositionByHitBox(2);
        Vector3 tempStomach = Player->GetBonePositionByHitBox(4);
        Vector3 tempHips = Player->GetBonePositionByHitBox(5);

        //Left Arms
        Vector3 tempLeftShoulder = Player->GetBonePositionByHitBox(6);
        Vector3 tempLeftElbow = Player->GetBonePositionByHitBox(7);
        Vector3 tempLeftHand = Player->GetBonePositionByHitBox(8);

        //Right Arm
        Vector3 tempRightShoulder = Player->GetBonePositionByHitBox(9);
        Vector3 tempRightElbow = Player->GetBonePositionByHitBox(10);
        Vector3 tempRightHand = Player->GetBonePositionByHitBox(11);

        //Left Leg
        Vector3 tempLeftThigh = Player->GetBonePositionByHitBox(12);
        Vector3 tempLeftKnee = Player->GetBonePositionByHitBox(13);
        Vector3 tempLeftLeg = Player->GetBonePositionByHitBox(14);

        //Right Leg
        Vector3 tempRightThigh = Player->GetBonePositionByHitBox(16);
        Vector3 tempRightKnee = Player->GetBonePositionByHitBox(17);
        Vector3 tempRightLeg = Player->GetBonePositionByHitBox(18);

        if (tempHead.Empty() || tempNeck.Empty() || tempUpperChest.Empty() ||
            tempStomach.Empty() || tempHips.Empty() || tempLeftShoulder.Empty() ||
            tempLeftElbow.Empty() || tempLeftHand.Empty() || tempRightShoulder.Empty() ||
            tempRightElbow.Empty() || tempRightHand.Empty() || tempLeftThigh.Empty() ||
            tempLeftKnee.Empty() || tempLeftLeg.Empty() || tempRightThigh.Empty() ||
            tempRightKnee.Empty() || tempRightLeg.Empty()) return;

        Vector3 Head = W2S(tempHead);
        Vector3 Neck = W2S(tempNeck);
        Vector3 UpperChest = W2S(tempUpperChest);
        Vector3 Stomach = W2S(tempStomach);
        Vector3 Hips = W2S(tempHips);

        // Left Arm
        Vector3 LeftShoulder = W2S(tempLeftShoulder);
        Vector3 LeftElbow = W2S(tempLeftElbow);
        Vector3 LeftHand = W2S(tempLeftHand);

        // Right Arm
        Vector3 RightShoulder = W2S(tempRightShoulder);
        Vector3 RightElbow = W2S(tempRightElbow);
        Vector3 RightHand = W2S(tempRightHand);

        // Left Leg
        Vector3 LeftThigh = W2S(tempLeftThigh);
        Vector3 LeftKnee = W2S(tempLeftKnee);
        Vector3 LeftLeg = W2S(tempLeftLeg);

        // Right Leg
        Vector3 RightThigh = W2S(tempRightThigh);
        Vector3 RightKnee = W2S(tempRightKnee);
        Vector3 RightLeg = W2S(tempRightLeg);

        if (Head.Empty() || Neck.Empty() || UpperChest.Empty() ||
            Stomach.Empty() || Hips.Empty() || LeftShoulder.Empty() ||
            LeftElbow.Empty() || LeftHand.Empty() || RightShoulder.Empty() ||
            RightElbow.Empty() || RightHand.Empty() || LeftThigh.Empty() ||
            LeftKnee.Empty() || LeftLeg.Empty() || RightThigh.Empty() ||
            RightKnee.Empty() || RightLeg.Empty()) return;

        //base draw
        Draw::esp->AddLine({ Head.x,Head.y }, { Neck.x,Neck.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ Neck.x,Neck.y }, { UpperChest.x,UpperChest.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ UpperChest.x,UpperChest.y }, { Stomach.x,Stomach.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ Stomach.x,Stomach.y }, { Hips.x,Hips.y }, skeletonColor, 1.f);

        //Left Arm Draw
        Draw::esp->AddLine({ UpperChest.x,UpperChest.y }, { LeftShoulder.x,LeftShoulder.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ LeftShoulder.x,LeftShoulder.y }, { LeftElbow.x,LeftElbow.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ LeftElbow.x,LeftElbow.y }, { LeftHand.x,LeftHand.y }, skeletonColor, 1.f);

        //Right Arm Draw
        Draw::esp->AddLine({ UpperChest.x,UpperChest.y }, { RightShoulder.x,RightShoulder.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ RightShoulder.x,RightShoulder.y }, { RightElbow.x,RightElbow.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ RightElbow.x,RightElbow.y }, { RightHand.x,RightHand.y }, skeletonColor, 1.f);

        //Left Leg Draw
        Draw::esp->AddLine({ Hips.x,Hips.y }, { LeftThigh.x,LeftThigh.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ LeftThigh.x,LeftThigh.y }, { LeftKnee.x,LeftKnee.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ LeftKnee.x,LeftKnee.y }, { LeftLeg.x,LeftLeg.y }, skeletonColor, 1.f);

        //Right Leg Draw
        Draw::esp->AddLine({ Hips.x,Hips.y }, { RightThigh.x,RightThigh.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ RightThigh.x,RightThigh.y }, { RightKnee.x,RightKnee.y }, skeletonColor, 1.f);
        Draw::esp->AddLine({ RightKnee.x,RightKnee.y }, { RightLeg.x,RightLeg.y }, skeletonColor, 1.f);

        float radius = std::hypot(Head.x - Neck.x, Head.y - Neck.y);

        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Head.x, Head.y), radius, skeletonColor);
    }

}
