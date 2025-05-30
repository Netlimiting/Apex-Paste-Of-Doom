#include "AmmoCounter.hpp"

void AmmoCounter::UpdateReloadingStatus(bool IsReloading) {
    int WeaponID = sdk.LocalPlayer->GetWeaponIndex();
    auto it = weaponReloadTimeMap.find(WeaponID);

    if (it == weaponReloadTimeMap.end())
        return;

    if (IsReloading == TRUE && !isReloadingPreviously) {
        hasReloadingStarted = true;
        isReloadingPreviously = true;
        reloadTime = it->second;
        reloadStartTime = std::chrono::steady_clock::now();
    }
    else if (IsReloading == FALSE && isReloadingPreviously) {
        if (hasReloadingStarted) {
            hasReloadingStarted = false;
        }
        isReloadingPreviously = false;
    }
}
ImU32 AmmoCounter::interpolateColor(ImU32 colorStart, ImU32 colorEnd, float factor) {
    ImU8 rStart = (colorStart >> IM_COL32_R_SHIFT) & 0xFF;
    ImU8 gStart = (colorStart >> IM_COL32_G_SHIFT) & 0xFF;
    ImU8 bStart = (colorStart >> IM_COL32_B_SHIFT) & 0xFF;
    ImU8 aStart = (colorStart >> IM_COL32_A_SHIFT) & 0xFF;

    ImU8 rEnd = (colorEnd >> IM_COL32_R_SHIFT) & 0xFF;
    ImU8 gEnd = (colorEnd >> IM_COL32_G_SHIFT) & 0xFF;
    ImU8 bEnd = (colorEnd >> IM_COL32_B_SHIFT) & 0xFF;
    ImU8 aEnd = (colorEnd >> IM_COL32_A_SHIFT) & 0xFF;

    ImU8 r = static_cast<ImU8>(rStart + factor * (rEnd - rStart));
    ImU8 g = static_cast<ImU8>(gStart + factor * (gEnd - gStart));
    ImU8 b = static_cast<ImU8>(bStart + factor * (bEnd - bStart));
    ImU8 a = static_cast<ImU8>(aStart + factor * (aEnd - aStart));

    return IM_COL32(r, g, b, a);
}
void AmmoCounter::Render() {
    if (hasReloadingStarted) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - reloadStartTime;

        float percentageComplete = min(elapsed.count() / reloadTime, 1.0f);
        float progressBarWidth = 200.0f;
        float progressBarHeight = 5.0f;
        float screenWidth = ImGui::GetIO().DisplaySize.x;
        float screenHeight = ImGui::GetIO().DisplaySize.y;

        float posX = (screenWidth - progressBarWidth) / 2.0f;
        float posY = (screenHeight / 2.0f) - (progressBarHeight / 2.0f) - 200.0f;

        float currentBarWidth = progressBarWidth * (1.0f - percentageComplete);

        ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
        ImU32 backgroundColor = IM_COL32(50, 50, 50, 200);
        ImU32 barColorStart = IM_COL32(0, 255, 0, 255);
        ImU32 barColorEnd = IM_COL32(255, 0, 0, 255);

        ImU32 currentColor = interpolateColor(barColorStart, barColorEnd, percentageComplete);

        ImDrawList* drawList = ImGui::GetBackgroundDrawList();
        drawList->AddRectFilled(
            ImVec2(posX - 1.0f, posY - 1.0f),
            ImVec2(posX + progressBarWidth + 1.0f, posY + progressBarHeight + 1.0f),
            outlineColor
        );
        drawList->AddRectFilled(
            ImVec2(posX, posY),
            ImVec2(posX + progressBarWidth, posY + progressBarHeight),
            backgroundColor
        );
        drawList->AddRectFilled(
            ImVec2(posX + (progressBarWidth - currentBarWidth), posY),
            ImVec2(posX + progressBarWidth, posY + progressBarHeight),
            currentColor
        );

    }
}
void AmmoCounter::DoAmmoCounter()
{
    if (!Cheat_Private::Misc::AmmoCounter && !Cheat_Private::Misc::ReloadBar) return;

    uint64_t primary_weapons_latest = Read<uint64_t>((uintptr_t)sdk.LocalPlayer + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    if (!(primary_weapons_latest)) return;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    if (!(primary_weapons_list)) return;

    if (Cheat_Private::Misc::ReloadBar)
    {
        int IsReloading = Read<int>(primary_weapons_list + Offsets::Misc::m_IsReloading);
        int WeaponID = sdk.LocalPlayer->GetWeaponIndex();
        UpdateReloadingStatus(IsReloading);
        Render();
    }

    if (Cheat_Private::Misc::AmmoCounter) {
        int CurrentAmmo = Read<int>(primary_weapons_list + Offsets::Misc::m_CurrentAmmo);
        if (!CurrentAmmo)return;
        int MaxAmmo = Read<int>(primary_weapons_list + Offsets::Misc::m_MaxMagAmmo);
        float ammoPercentage = static_cast<float>(CurrentAmmo) / static_cast<float>(MaxAmmo);
        if (ammoPercentage <= 0.0f)return;

        float posX = (sdk.DisplaySize.x - 200.0f) / 2.0f;
        float posY = sdk.DisplaySize.y * 0.75f;

        float currentBarWidth = 200.0f * ammoPercentage;

        ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
        ImU32 backgroundColor = IM_COL32(50, 50, 50, 255);
        ImU32 barColorStart = IM_COL32(0, 255, 0, 255);
        ImU32 barColorEnd = IM_COL32(255, 0, 0, 255);

        ImU32 currentColor = ImGui::ColorConvertFloat4ToU32(
            ImLerp(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f - ammoPercentage)
        );

        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddRectFilled(
            ImVec2(posX - 1.0f, posY - 1.0f),
            ImVec2(posX + 200.0f + 1.0f, posY + 12.0f + 1.0f),
            outlineColor
        );
        drawList->AddRectFilled(
            ImVec2(posX, posY),
            ImVec2(posX + 200.0f, posY + 12.0f),
            backgroundColor
        );
        drawList->AddRectFilledMultiColor(
            ImVec2(posX, posY),
            ImVec2(posX + currentBarWidth, posY + 12.0f),
            currentColor,
            ImColor(255, 255, 255, 180),
            ImColor(255, 255, 255, 180),
            currentColor
        );

        std::string ammoText = std::to_string(CurrentAmmo) + _(" / ") + std::to_string(MaxAmmo);
        ImVec2 textSize = ImGui::CalcTextSize(ammoText.c_str());
        float textPosX = posX + (200.0f - textSize.x) / 2.0f;
        float textPosY = posY + (12.0f - textSize.y) / 2.0f;

        Draw::esp->draw_text_outline_font(textPosX, textPosY, IM_COL32(255, 255, 255, 255), ammoText.c_str(), 1.0f);
    }
}