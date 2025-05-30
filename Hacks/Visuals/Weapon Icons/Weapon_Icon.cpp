#include "Weapon_Icon.hpp"

void Weapon_Icon::DoWeaponIcon(Vector3 Pos, SDK::Entity* Player, bool vis)
{
    struct BoxDimensions {
        int width;
        int height;
        int yheight;
    };

    BoxDimensions weaponBox = { 55, 30, 75 };
    BoxDimensions ammoBox = { 30, 15, 35 };

    if (Cheat_Private::ESP::Level || Cheat_Private::ESP::Distance) {
        weaponBox.yheight = 75;
        ammoBox.yheight = 45;
    }

    int boxX = Pos.x - (weaponBox.width / 2);
    int boxY = Pos.y + weaponBox.yheight;
    int flippedBoxY = boxY - weaponBox.height;

    int AboxX = Pos.x - (ammoBox.width / 2);
    int AboxY = Pos.y + ammoBox.yheight;
    int AflippedBoxY = AboxY - ammoBox.height;

    static const std::unordered_map<int, ID3D11ShaderResourceView*> weaponTextureMap = {
        {112, WeaponIcon::PistolICON::P2020Texture},
        {85, WeaponIcon::PistolICON::Re45Texture},
        {84, WeaponIcon::PistolICON::AlternatorTexture},
        {115, WeaponIcon::PistolICON::WingmenTexture},
        {92, WeaponIcon::ShotgunICON::EVA8Texture},
        {101, WeaponIcon::ShotgunICON::MastiffTexture},
        {109, WeaponIcon::ShotgunICON::peacekeeperTexture},
        {102, WeaponIcon::ShotgunICON::MozambiqueTexture},
        {119, WeaponIcon::Rifle::CarTexture},
        {0, WeaponIcon::Rifle::CarbineTexture},
        {94, WeaponIcon::Rifle::FlatlineTexture},
        {96, WeaponIcon::Rifle::HemlockTexture},
        {107, WeaponIcon::Rifle::ProwlerTexture},
        {6, WeaponIcon::Rifle::RampageTexture},
        {95, WeaponIcon::Rifle::RepeaterTexture},
        {113, WeaponIcon::Rifle::SpitFireTexture},
        {2, WeaponIcon::Special::BowTexture},
        {89, WeaponIcon::Special::DevotionTexture},
        {176, WeaponIcon::Special::KnifeTexture},
        {98, WeaponIcon::Special::KraberTexture},
        {111, WeaponIcon::Special::R99Texture},
        {87, WeaponIcon::Sniper::ChargedRifleTexture},
        {90, WeaponIcon::Sniper::DMRTexture},
        {1, WeaponIcon::Sniper::SentinelTexture},
        {120, WeaponIcon::Energy::NemesisTexture},
        {117, WeaponIcon::Energy::VoltTexture},
        {114, WeaponIcon::Energy::TripleTexture},
        {99, WeaponIcon::Energy::EMGTexture},
        {91, WeaponIcon::Energy::HAVOCTexture},
    };


    int weapon_index = Player->GetWeaponIndex();

    auto it = weaponTextureMap.find(weapon_index);
    if (it != weaponTextureMap.end()) {
        ID3D11ShaderResourceView* texture = it->second;
        {
            ImColor WeaponICONColor = ImColor{ Cheat_Private::ESP::WeaponIconColor[0], Cheat_Private::ESP::WeaponIconColor[1], Cheat_Private::ESP::WeaponIconColor[2], 255.f };
            if (Cheat_Private::ESP::VisCheck && Cheat_Private::ESP::Vistype[8])
            {
                vis
                    ? WeaponICONColor = ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                    : WeaponICONColor = ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);
            }
            if (weapon_index == 112 || weapon_index == 85 || weapon_index == 84 || weapon_index == 115) { // my dumb ass imported pistols with an incorrect width and height so this checks for it and fixes my mistake
                Draw::menu->DrawRotatedImageWithBoxColor(texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height, WeaponICONColor);
            }
            else {
                Draw::menu->DrawRotatedImageWithBoxColor(texture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height, WeaponICONColor);
            }
        }
    }

}
