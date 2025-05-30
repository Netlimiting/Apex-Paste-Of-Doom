#include "Glow.hpp"

void Glow::weapon_glow()
{
       uint64_t actWeaponID = Read<uint64_t>((uint64_t)sdk.LocalPlayer + Offsets::Misc::m_m_hViewModels) & 0xFFFF;
        if (!actWeaponID) return;
        uint64_t currentWeapon = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (actWeaponID * 0x20));
        if (!currentWeapon) return;
        Write<uint8_t>(currentWeapon + OFF_GLOW_ENABLE,
            1);
        Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID,
            Cheat_Private::Misc::SelectedGlowIndex);

        if (Cheat_Private::Misc::WeaponGlowIndex == 5 || Cheat_Private::Misc::WeaponGlowIndex == 6)
        {
             auto highlightsettings = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
            //      
            static int cases = 0;
            static float r = 1.00f, g = 0.00f, b = 1.00f;
            switch (cases)
            {
            case 0: { r -= 0.003f; if (r <= 0) cases += 1; break; }
            case 1: { g += 0.003f; b -= 0.003f; if (g >= 1) cases += 1; break; }
            case 2: { r += 0.003f; if (r >= 1) cases += 1; break; }
            case 3: { b += 0.003f; g -= 0.003f; if (b >= 1) cases = 0; break; }
            default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
            }
            Write<HighlightFunctionBits>(highlightsettings + (0x38 * 46) + 0, { 137,138,35,127 });
            Write<HighlightParameter>(highlightsettings + 0x34 * uint64_t(Cheat_Private::Misc::SelectedGlowIndex) + 8, { r / 4.25f,g / 4.25f,b / 4.25f });

        }
}
void Glow::hand_glow()
{
    uint64_t actWeaponID = Read<uint64_t>((uint64_t)sdk.LocalPlayer + Offsets::Misc::m_m_hViewModelsWithArms) & 0xFFFF;
    if (!actWeaponID) return;
    uint64_t currentWeapon = Read<uint64_t>(
        sdk.R5Apex + Offsets::Misc::m_EntityList + (actWeaponID * 0x20));
    if (!currentWeapon) return;
    Write<uint8_t>(currentWeapon + OFF_GLOW_ENABLE,
        1);
    Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID,
        Cheat_Private::Misc::SelectedHandGlowIndex);

    if (Cheat_Private::Misc::HandGlowIndex == 5 || Cheat_Private::Misc::HandGlowIndex == 6)
    {
        auto highlightsettings = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
        //      
        static int cases = 0;
        static float r = 1.00f, g = 0.00f, b = 1.00f;
        switch (cases)
        {
        case 0: { r -= 0.003f; if (r <= 0) cases += 1; break; }
        case 1: { g += 0.003f; b -= 0.003f; if (g >= 1) cases += 1; break; }
        case 2: { r += 0.003f; if (r >= 1) cases += 1; break; }
        case 3: { b += 0.003f; g -= 0.003f; if (b >= 1) cases = 0; break; }
        default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
        }
        Write<HighlightFunctionBits>(highlightsettings + (0x38 * 46) + 0, { 137,138,35,127 });
        Write<HighlightParameter>(highlightsettings + 0x34 * uint64_t(Cheat_Private::Misc::SelectedHandGlowIndex) + 8, { r / 4.25f,g / 4.25f,b / 4.25f });

    }
}
void Glow::ItemGlow()
{
    while (true)
    {
        if (!inMatch)continue;
        if (Cheat_Private::Misc::ItemGlow) {

            if (!highlightsettingsa)
                highlightsettingsa = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
            const long highlightSize = 0x34;
            for (int highlightId = 1; highlightId < 50; highlightId++) {
                const HighlightFunctionBits newGlowMode = { 137,138,35,127 };
                const HighlightFunctionBits oldGlowMode = Read<HighlightFunctionBits>(highlightsettingsa + (highlightSize * highlightId) + 0);
                Write<HighlightFunctionBits>(highlightsettingsa + (highlightSize * highlightId) + 0, newGlowMode);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

    }
}

void Glow::SetColor(SDK::Entity* Entity, bool vis)
{
    if (Cheat_Private::ESP::Glow)
    {
        int glowtype = 83;
        if (Cheat_Private::ESP::VisCheck)
            vis ? glowtype = 83 : glowtype = 76;
        //26 blue or 83
        //16 green
        //76 red
       
        Write<int>(Entity->getAddress() + OFF_GLOW_ENABLE, 1);
        Write<int>(Entity->getAddress() + OFF_GLOW_HIGHLIGHT_ID, glowtype);
        Write<int>(Entity->getAddress() + OFF_GLOW_THROUGH_WALL, 2);
        Write<int>(Entity->getAddress() + OFF_GLOW_DISTANCE, 300.0f);
        Write<uint8_t>(Entity->getAddress() + OFF_GLOW_FIX, 2);

    }
}
void Glow::DisableGlow(uintptr_t entity)
{
    Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID, 0);
    Write<int>(entity + OFF_GLOW_THROUGH_WALL, 0);
    Write<float>(entity + OFF_GLOW_DISTANCE, 0.f);
    uint64_t HighlightSettings = Read<uint64_t>(entity + OFF_GLOW_HIGHLIGHTS);
    Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID + 0, 0);
}