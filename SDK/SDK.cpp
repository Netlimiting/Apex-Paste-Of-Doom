#include "SDK.hpp"

// Get
std::uint64_t SDK::Game::Get::getAddress() {
    uint64_t Address = ((uint64_t)this);
    if (!Address && !is_valid(Address)) return 0;
    else return Address;
}
//END

// SCRIPT

std::string SDK::Game::Script::GetName(int i) {

    uintptr_t NameOffset = Read<uintptr_t>(sdk.R5Apex + Offsets::Misc::m_NameList + ((i - 1) * 24)); 
    if (!NameOffset)
        return _("");
    std::string PlayerName = ReadString(NameOffset);
    return PlayerName;
}

std::string SDK::Game::Script::getModelName() {

    if (!this->getAddress()) return "";
    uintptr_t pMode_Name = Read < uintptr_t >(this->getAddress() + Offsets::C_BaseEntity::m_m_ModelName);
    if (!pMode_Name) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error uintptr_t pMode_Name = Read<uintptr_t>(this->getAddress() + Offsets::C_BaseEntity::m_m_ModelName) ? NULL "));
#endif
        return "";
    }
    return ReadString(pMode_Name);
}
std::string SDK::Game::Script::getSignifierName() {
    if (!this->getAddress()) return "";
    uintptr_t sigAddr = Read < uintptr_t >(this->getAddress() + Offsets::DT_BaseEntity::m_m_iSignifierName);
    if (!sigAddr) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error uintptr_t sigAddr = Read<uintptr_t>(this->getAddress() + Offsets::DT_BaseEntity::m_m_iSignifierName) ? NULL "));
#endif
        return "";
    }
    return ReadString(sigAddr);
}

//END

// WORLD TO SCREEN

Vector3 SDK::Game::WorldToScreen::W2S(Vector3 Position) {
   
  

    BaseMatrix Matrix = Read < BaseMatrix >(sdk.mtrix);

    Vector3 out;
    float _x = Matrix.at[0] * Position.x + Matrix.at[1] * Position.y + Matrix.at[2] * Position.z + Matrix.at[3];
    float _y = Matrix.at[4] * Position.x + Matrix.at[5] * Position.y + Matrix.at[6] * Position.z + Matrix.at[7];
    out.z = Matrix.at[12] * Position.x + Matrix.at[13] * Position.y + Matrix.at[14] * Position.z + Matrix.at[15];

    if (out.z < 0.1f) return {0,0,0};

    _x *= 1.f / out.z;
    _y *= 1.f / out.z;

    out.x = sdk.DisplaySize.x * .5f;
    out.y = sdk.DisplaySize.y * .5f;

    out.x += 0.5f * _x * sdk.DisplaySize.x + 0.5f;
    out.y -= 0.5f * _y * sdk.DisplaySize.y + 0.5f;

    return out;
}


bool SDK::Entity::Update() {
   
    return true;
}
SDK::Entity::Projectile* SDK::Entity::Get_Projectile()
{
    uint64_t primary_weapons_latest = Read<uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    if (!primary_weapons_latest)return NULL;
    SDK::Entity::Projectile* primary_weapons_list = Read<SDK::Entity::Projectile*>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    if (!primary_weapons_list)return NULL;
    return primary_weapons_list;
}
void SDK::Entity::Projectile::Set_ProjectilePerShot(int Projectile)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_projectiles_per_shot, Projectile);
}
void SDK::Entity::Projectile::Set_ProjectilePerDelpoy(int Projectile)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_projectiles_per_deploy, Projectile);
}
void SDK::Entity::Projectile::Set_ProjectileGravity(float gravity)
{
    Write<float>(this->getAddress() + Offsets::Misc::m_projectiles_gravity, gravity);
}
void SDK::Entity::Projectile::Set_FireRate(float fireRate)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_projectiles_firerate, fireRate);
}
void SDK::Entity::Projectile::Set_ProjectileOwnerVelocity(float Velocity)
{
    Write<float>(this->getAddress() + Offsets::Misc::m_projectiles_OwnerVelocity, Velocity);
}
void SDK::Entity::Projectile::Set_ProjectileAirFriction(float Frication)
{
    Write<float>(this->getAddress() + Offsets::Misc::m_projectiles_Frication, Frication);
}
void SDK::Entity::Projectile::Set_ProjectileDrag(float Drag)
{
    Write<float>(this->getAddress() + Offsets::Misc::m_projectiles_DragCoefficeient, Drag);
}
float SDK::Entity::Projectile::Get_ProjectileGravity()
{
    return Read<float>(this->getAddress() + Offsets::Misc::m_projectiles_gravity);
}
void SDK::Entity::Projectile::Set_CrosshairSpread(int spread)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_CrosshairSpeard, spread);
}
void SDK::Entity::Projectile::Set_SpreadRadius(int radius)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_SpreadRadius, radius);
}
int SDK::Entity::Projectile::Get_CrosshairSpread()
{
    return Read<int>(this->getAddress() + Offsets::Misc::m_CrosshairSpeard);
}
int SDK::Entity::Projectile::Get_SpreadRaidus()
{
    return Read<int>(this->getAddress() + Offsets::Misc::m_SpreadRadius);
}
void SDK::Entity::SetViewAngles(Vector2 Angles)
{
    Write<Vector2>((uintptr_t)this + Offsets::DT_Player::m_viewOffEntity, Angles);
}
float SDK::Entity::GetDistance() {
    return this->Get_Position().distance(this->LocalPlayer()->Get_Position());
}
float SDK::Entity::Get_Height() {
    return this->Head_Position.y - this->Feet_Position.y;
}
float SDK::Entity::Get_Width() {
    return this->Height / 2;
}
int SDK::Entity::Get_GrappleState() {
    return Read<int>(this->getAddress() + Offsets::Misc::m_GrappleState);
}
void SDK::Entity::Set_CharacterSkin(int ID)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_CharacterSkin, ID);
}
void SDK::Entity::Do_ThirdPerson() {
    Write<int>(sdk.R5Apex + Offsets::Misc::m_ThirdPerson + 0x64, 1);
    Write<int>(sdk.R5Apex + Offsets::Misc::m_ThirdPersonTtype + 0x64, 2);
    Write<int>(this->getAddress() + Offsets::Misc::m_ThirdPersonent, 1);
    Write<int>(this->getAddress() + Offsets::Misc::m_ThirdPersonentptr, 1);
}
void SDK::Entity::Reset_ThirdPerson() {
    Write<int>(sdk.R5Apex + Offsets::Misc::m_ThirdPerson + 0x64, 0);
    Write<int>(this->getAddress() + Offsets::Misc::m_ThirdPersonent, 0);
    Write<int>(this->getAddress() + Offsets::Misc::m_ThirdPersonentptr, 0);
}

int SDK::Entity::Current_Health() {
    return Read < int >(this->getAddress() + Offsets::DT_Player::m_iHealth);
}
float SDK::Entity::Get_LastDeathTime()
{
    return Read< float >(this->getAddress() + Offsets::DT_Player::m_ideathTime);
}
bool SDK::Entity::Is_Spectating() {
    float targetangle = Read<float>(this->getAddress() + (0x2534 - 0X8));
    float targetyaw = -targetangle; // yaw is inverted
    if (targetyaw < 0)
        targetyaw += 360;
    targetyaw += 90; // yaw is off by 90
    if (targetyaw > 360)
        targetyaw -= 360;
    float localangle = Read<float>(sdk.LocalPlayer->getAddress() + (0x2534 - 0X8));
    float localyaw = -localangle; // yaw is inverted
    if (localyaw < 0)
        localyaw += 360;
    localyaw += 90; // yaw is off by 90
    if (localyaw > 360)
        localyaw -= 360;

    if (targetyaw == localyaw && this->Current_Health() == 0)
        return true;

    return false;
}
int SDK::Entity::Get_Current_shield() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_shieldHealth);

}
int SDK::Entity::Get_Max_shield() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_shieldHealthMax);

}
int SDK::Entity::Get_shield_type() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_Shield_type);

}
bool SDK::Entity::Projectile::IsSemi()
{
    return Read<bool>(this->getAddress() + Offsets::Misc::m_semi);
}
int SDK::Entity::Get_Network_Flags() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_passThroughThickness);
}
int SDK::Entity::Get_TeamNum() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_iTeamNum);
}
int SDK::Entity::BleedOutState()
{
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_bleedoutState);

}
int SDK::Entity::Get_Squad() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_squadID);
}
Vector2 SDK::Entity::Get_Punch()
{
    return Read<Vector2>(this->getAddress() + Offsets::Misc::m_punchAngles);
}
void SDK::Entity::Set_ObserverMode(int mode) {
    Write<int>(this->getAddress() + Offsets::Misc::m_iObserverMode, mode);
}

void SDK::Entity::Set_ServerModelState(int ModelState) {
    Write<int>(this->getAddress() + Offsets::Misc::m_ServerModelState, ModelState);
}

bool SDK::Entity::Get_IsPlayer() {
    if (this->getSignifierName().find("player") != std::string::npos)
        return true;
    else
        return false;
}
float SDK::Entity::Projectile::Get_ProjectileSpeed()
{
    return Read<float>(this->getAddress() + Offsets::Misc::m_ProjectileSpeed);
}
bool SDK::Entity::Get_IsLocalPlayer() {
    if (this->LocalPlayer()->getAddress() == this->getAddress())
        return true;
    else
        return false;
}
bool SDK::Entity::Get_Alive() {
    if (this->Health <= 0.1f)
        return false;
    else
        return true;
}
int SDK::Entity::Get_Level()
{
    uint64_t Address = ((uint64_t)this);
    if (!Address) return 0;
    int m_xp = Read<int>(Address + Offsets::DT_Player::m_xp); //m_xp
    if (m_xp < 0) return 0;
    if (m_xp < 100) return 1;

    int levels[] = {
        2750, 6650, 11400,
        17000, 23350, 30450,
        38300,46450, 55050,
        64100, 73600, 83550,
        93950, 104800, 116100,
        127850, 140050, 152400,
        164900, 177550, 190350,
        203300, 216400, 229650,
        243050, 256600, 270300,
        284150, 298150, 312300,
        326600, 341050, 355650,
        370400, 385300, 400350,
        415550, 430900, 446400,
        462050, 477850, 493800,
        509900, 526150, 542550,
        559100, 575800, 592650,
        609650, 626800, 644100,
        661550, 679150, 696900,
        714800 };

    int level = 56;
    int arraySize = sizeof(levels) / sizeof(levels[0]);

    for (int i = 0; i < arraySize; i++)
    {
        if (m_xp < levels[i])
        {
            return i + 1;
        }
    }

    return level + ((m_xp - levels[arraySize - 1] + 1) / 18000);
}
void SDK::Entity::Set_WeaponSize(float size)
{
    std::uint64_t ViewModel = Read<std::uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    if (!ViewModel)return;
    uint64_t ActiveViewModel = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (ViewModel << 5));
    if (!ActiveViewModel)return;

    if (Read<float>(ActiveViewModel + Offsets::Misc::m_ModelSize) != size)
        Write<float>(ActiveViewModel + Offsets::Misc::m_ModelSize, size);
}
void SDK::Entity::Set_Fov(float fov)
{
    Write<float>(this->getAddress() + Offsets::Misc::m_settings_fov, fov);
}
void SDK::Entity::Set_AnimationMask(int AnimationSequence)
{
    Write<int>(this->getAddress() + Offsets::Misc::m_ServerAninimation, AnimationSequence);
}
int SDK::Entity::Get_AnimationMask()
{
    return Read<int>(this->getAddress() + Offsets::Misc::m_ServerAninimation);
}
std::string SDK::Entity::GetOperator()
{

    std::string ModelName = this->getModelName();
    static std::unordered_map<std::string, std::string> ModelNameMap = {
       {_("dummie"), _("Dummie")}, {_("ash"), _("Ash")}, {_("ballistic"), _("Ballistic")},
       {_("bangalore"), _("Bangalore")}, {_("bloodhound"), _("Bloodhound")},
       {_("catalyst"), _("Catalyst")}, {_("caustic"), _("Caustic")},
       {_("conduit"), _("Conduit")}, {_("crypto"), _("Crypto")}, {_("fuse"), _("Fuse")},
       {_("gibraltar"), _("Gibraltar")}, {_("horizon"), _("Horizon")}, {_("nova"), _("Horizon")},
       {_("holo"), _("Mirage")}, {_("mirage"), _("Mirage")}, {_("lifeline"), _("Lifeline")},
       {_("loba"), _("Loba")}, {_("madmaggie"), _("Mad Maggie")}, {_("newcastle"), _("Newcastle")},
       {_("octane"), _("Octane")}, {_("pathfinder"), _("Pathfinder")}, {_("rampart"), _("Rampart")},
       {_("revenant"), _("Revenant")}, {_("seer"), _("Seer")}, {_("stim"), _("Octane")},
       {_("valkyrie"), _("Valkyrie")}, {_("vantage"), _("Vantage")}, {_("wattson"), _("Wattson")},
       {_("wraith"), _("Wraith")}, {_("alter"), _("Alter")}
    };

    std::string replacedName = ModelName;
    for (auto& entry : ModelNameMap) {
        if (ModelName.empty())continue;
        if (ModelName.find(entry.first) != std::string::npos) {
            replacedName = entry.second;
            break;
        }
    }

    return replacedName;
}
Vector3 SDK::Entity::Get_Position() {

    Vector3 Pos = Read < Vector3 >(this->getAddress() + Offsets::C_BaseEntity::m_m_vecAbsOrigin);
    if (Pos.Empty()) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error Vector3 Pos = Read<Vector3>(this->getAddress() + Offsets::C_BaseEntity::m_m_vecAbsOrigin) ? NULL Vector3 "));
#endif
        return {
          0,
          0,
          0
        };
    }
    return Pos;
}
Vector3 SDK::Entity::getBonePos(int ID) {
    Vector3 pos = this->Get_Position();
    if (pos.Empty()) return {
      0,
      0,
      0
    };
    uintptr_t bones = Read < uintptr_t >(this->getAddress() + Offsets::Misc::m_Bones); //PoopSets::demfuckingBone
    if (!bones) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error uintptr_t bones = Read<uintptr_t>(this->getAddress() + Offsets::Misc::m_Bones) ? NULL Vector3 "));
#endif
        return {
          0,
          0,
          0
        };
    }
    Vector3 bone = {};
    UINT32 boneloc = (ID * 0x30);
    bone_t bo = {};
    bo = Read < bone_t >(bones + boneloc);

    bone.x = bo.x + pos.x;
    bone.y = bo.y + pos.y;
    bone.z = bo.z + pos.z;
    return bone;
}

float SDK::Entity::Get_WorldTime()
{
    return Read<float>(this->getAddress() + Offsets::Misc::m_WorldTime);
}
float SDK::Entity::Get_LastVisibleTime()
{
    return Read<float>(this->getAddress() + Offsets::Misc::m_lastVisibleTime);
}
void SDK::Entity::Set_HitBoxSize(float size) {
    Write<float>(this->getAddress() + Offsets::Misc::m_ModelSize, 1.09f);
}
Vector3 SDK::Entity::GetBonePositionByHitBox(int ID) {
    Vector3 origin = Get_Position();
    if (origin.Empty()) return {
      0,
      0,
      0
    };

    uint64_t Model = Read < uint64_t >(this->getAddress() + 0xff0);
    if (!Model)return Vector3();

    uint64_t StudioHdr = Read < uint64_t >(Model + 0x8);
    if (!StudioHdr)return Vector3();

    //get hitbox array
    uint16_t HitboxCache = Read < uint16_t >(StudioHdr + 0x34);
    if (!HitboxCache)return Vector3();

    uint64_t HitBoxsArray = StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));
    if (!HitBoxsArray)return Vector3();

    uint16_t IndexCache = Read < uint16_t >(HitBoxsArray + 0x4);
    if (!IndexCache)return Vector3();

    int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));

    uint16_t Bone = Read < uint16_t >(HitBoxsArray + HitboxIndex + (ID * 0x20));

    if (Bone < 0 || Bone > 255)
        return Vector3();

    //hitpos
    uint64_t BoneArray = Read < uint64_t >(this->getAddress() + Offsets::Misc::m_Bones);
    if (!BoneArray)return Vector3();

    uintptr_t Add = BoneArray + Bone * sizeof(matrix3x4_t);
    matrix3x4_t Matrix = Read < matrix3x4_t >(Add);

    return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
}
Vector3 SDK::Entity::ViewAngles() {
    return Read < Vector3 >(this->getAddress() + Offsets::DT_Player::m_viewOffEntity);
}
SDK::Entity* SDK::Entity::LocalPlayer() {
    return Read < SDK::Entity* >(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
}
SDK::Glow* SDK::Entity::GetGlow() {
    return Read < SDK::Glow* >(this->getAddress());
}
SDK::Entity::Collision* SDK::Entity::Get_Collision() {
    return Read < SDK::Entity::Collision* >(this->getAddress() + Offsets::DT_BaseEntity::m_m_Collision);
}
float SDK::Entity::LastKillTime()
{
    return  Read<float>((uintptr_t)this + Offsets::Misc::m_LastKillTime);
}
//Collision
int SDK::Loot::GetIndex()
{
    return Read<int>((uint64_t)this + Offsets::Misc::m_m_customScriptInt);
}
Vector3 SDK::Loot::GetPosition()
{
    return Read<Vector3>((uint64_t)this + Offsets::C_BaseEntity::m_m_vecAbsOrigin);
}
Vector3 SDK::Entity::Collision::Get_VecMin() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMins);
}
Vector3 SDK::Entity::Collision::Get_VecMax() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMaxs);
}
Vector3 SDK::Entity::Collision::Get_vecSpecifiedSurroundingMins() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMins);
}
Vector3 SDK::Entity::Collision::Get_vecSpecifiedSurroundingMaxs() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMaxs);
}

int SDK::Entity::Collision::Get_SolidFlags() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_usSolidFlags);
}
int SDK::Entity::Collision::Get_SolidType() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_nSolidType);
}
int SDK::Entity::Collision::Get_triggerBloat() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_triggerBloat);
}
int SDK::Entity::Collision::Get_collisionDetailLevel() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_collisionDetailLevel);
}
int SDK::Entity::Collision::Get_SurroundType() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_nSurroundType);
}
int SDK::Entity::GetFlags()
{
    uintptr_t Weapon = Read<uintptr_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon);
    if (!Weapon) return 0;
    return Read<int>(Weapon + Offsets::Misc::m_flags);
}
int SDK::Entity::GetWeaponIndex()
{
    uint64_t primary_weapons_latest = Read<uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    int weapon_index = Read<int>(primary_weapons_list + 0x1778); // weapon name0x1574 0x0769b4b8
    return weapon_index;
}

std::string SDK::Entity::get_weapon_name()
{
    uint64_t primary_weapons_latest = Read<uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    int weapon_index = Read<int>(primary_weapons_list + 0x1788); // weapon name0x1574 0x0769b4b8
    static const std::unordered_map<int, std::string> weapon_map = {
        {WeaponIDs::R301, _("R301")},
        {WeaponIDs::BOCEK, _("Bocek")},
        {WeaponIDs::HAVOC, _("Havoc")},
        {WeaponIDs::DEVOTION, _("Devotion")},
        {WeaponIDs::LSTAR, _("L-Star")},
        {WeaponIDs::TRIPLE_TAKE, _("Triple Take")},
        {WeaponIDs::VOLT, _("Volt")},
        {WeaponIDs::NEMESIS, _("Nemesis")},
        {WeaponIDs::FLATLINE, _("Flatline")},
        {WeaponIDs::HEMLOCK, _("Hemlock")},
        {WeaponIDs::REPEATER_3030, _("30-30 Repeater")},
        {WeaponIDs::RAMPAGE, _("Rampage")},
        {WeaponIDs::CAR, _("C.A.R")},
        {WeaponIDs::P2020, _("P2020")},
        {WeaponIDs::RE45, _("RE45")},
        {WeaponIDs::ALTERNATOR, _("Alternator")},
        {WeaponIDs::R99, _("R99")},
        {WeaponIDs::SPITFIRE, _("Spitfire")},
        {WeaponIDs::G7_SCOUT, _("G7 Scout")},
        {WeaponIDs::MOZAMBIQUE, _("Mozambique")},
        {WeaponIDs::EVA8, _("EVA-8 Auto")},
        {WeaponIDs::PEACEKEEPER, _("Peacekeeper")},
        {WeaponIDs::SENTINEL, _("Sentinel")},
        {WeaponIDs::CHARGE_RIFLE, _("Charge Rifle")},
        {WeaponIDs::LONGBOW, _("Longbow")},
        {WeaponIDs::MASTIFF, _("Mastiff")},
        {WeaponIDs::PROWLER, _("Prowler")},
        {WeaponIDs::WINGMAN, _("Wingman")},
        {WeaponIDs::KRABER, _("Kraber")},
        {WeaponIDs::KNIFE, _("Knife")}
    };

    auto it = weapon_map.find(weapon_index);
    if (it != weapon_map.end()) {
        return it->second;
    }

    return "None";
}
float SDK::Entity::Get_TraversalStartTime() {
    return Read<float>(this->getAddress() + Offsets::Misc::m_traversalStartTime);
}
float SDK::Entity::Get_TraversalProgress() {
    return Read<float>(this->getAddress() + Offsets::Misc::m_tranversalProgress);
}
void SDK::Entity::SetSkin(int ID)
{
    uint64_t primary_weapons_latest = Read<uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    Write<int>(primary_weapons_list + 0x0d60, ID);
}
int SDK::Entity::Weapon::GetAmmoCount()
{
    return Read<int>(this->getAddress() + Offsets::Misc::m_AmmoCount);
}

bool SDK::Entity::Weapon::Reloading()
{
    return Read<bool>(this->getAddress() + Offsets::Misc::m_IsReloading);
}

SDK::Entity::Weapon* SDK::Entity::GetWeapon()
{
    uint64_t primary_weapons_latest = Read<uint64_t>(this->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    if (!(primary_weapons_latest)) return NULL;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    if (!(primary_weapons_list)) return NULL;

    return Read<SDK::Entity::Weapon*>(primary_weapons_list);
}
