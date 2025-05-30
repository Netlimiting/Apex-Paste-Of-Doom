#pragma once
#include <windows.h>
#include <map>
#include <D3D11.h>
#include <d3d9types.h>
#include <dwmapi.h>
#include <d3d11.h>
#include <shared_mutex>

inline std::shared_mutex entityMutex;

inline std::atomic<bool> running(true);

#pragma comment(lib, "d3dx11.lib")

#include <D3DX11tex.h>
#pragma once  
#include <windows.h>  
#include <map>  
#include <D3D11.h>  
#include <d3d9types.h>  
#include <dwmapi.h>  
#include <d3d11.h>  
#include <shared_mutex>  

inline std::shared_mutex entityMutex;  

inline std::atomic<bool> running(true);  

// Remove the direct inclusion of D3DX11tex.h and replace it with DirectXTex library  
#include <DirectXTex.h>  

#pragma comment(lib, "d3d11.lib")  
#pragma comment(lib, "dxguid.lib")  

#include <Xinput.h>  
#pragma comment(lib,"XInput.lib")  
#pragma comment(lib,"Xinput9_1_0.lib")  

#include "../utils/callspoof.hpp"  

#define RESET   _("\033[0m")  
#define BLACK   _("\033[30m")     /* Black */  
#define RED      _("\033[31m")     /* Red */  
#define GREEN    _("\033[32m")    /* Green */  
#define YELLOW   _("\033[33m")   /* Yellow */  
#define BLUE     _("\033[34m")  /* Blue */  
#define MAGENTA  _("\033[35m") /* Magenta */  
#define CYAN     _("\033[36m")/* Cyan */  
#define WHITE    _("\033[37m")/* White */  
#define BOLDBLACK    _("\033[1m\033[30m")      /* Bold Black */  
#define BOLDRED      _("\033[1m\033[31m")      /* Bold Red */  
#define BOLDGREEN    _("\033[1m\033[32m")      /* Bold Green */  
#define BOLDYELLOW   _("\033[1m\033[33m")      /* Bold Yellow */  
#define BOLDBLUE     _("\033[1m\033[34m")      /* Bold Blue */  
#define BOLDMAGENTA  _("\033[1m\033[35m")      /* Bold Magenta */  
#define BOLDCYAN     _("\033[1m\033[36m")      /* Bold Cyan */  
#define BOLDWHITE    _("\033[1m\033[37m")      /* Bold White */  

#include "../interface.h"  
#include "../utils/xor.hpp"  
#include "../utils/returnspoof.hpp"  
#include "../Custom Radar/Webradar.hpp"  
#include "../imgui/imgui_internal.h"  

//Armor ICON  
#include "../img/Armor/Common Armor Bytes.h"  
#include "../img/Armor/Uncommon Armor Bytes.h"  
#include "../img/Armor/Rare Armor Bytes.h"  
#include "../img/Armor/Legendary Armor Bytes.h"  
#include "../img/Armor/Mythic Armor Bytes.h"  
#include "../img/Armor/Helmetbytes.h"  
#include "../img/Cartoon/Peter_Griffen.h"  
#include "../img/Cartoon/EKitten.h"  

//WEAPON ICON  
#include "../img/Weapons/Pistol/p2020 bytes.h"  
#include "../img/Weapons/Pistol/alternator bytes.h"  
#include "../img/Weapons/Pistol/re45 bytes.h"  
#include "../img/Weapons/Pistol/wingmen bytes.h"  

#include "../img/Weapons/Shotgun/eva_8_auto bytes.h"  
#include "../img/Weapons/Shotgun/mastiff bytes.h"  
#include "../img/Weapons/Shotgun/mozambique bytes.h"  
#include "../img/Weapons/Shotgun/peacekeeper bytes.h"  

#include "../img/Weapons/Rifle/car bytes.h"  
#include "../img/Weapons/Rifle/Carbine bytes.h"  
#include "../img/Weapons/Rifle/Flatline bytes.h"  
#include "../img/Weapons/Rifle/Hemlok bytes.h"  
#include "../img/Weapons/Rifle/Prowler bytes.h"  
#include "../img/Weapons/Rifle/Rampage bytes.h"  
#include "../img/Weapons/Rifle/Repeater bytes.h"  
#include "../img/Weapons/Rifle/scout bytes.h"  
#include "../img/Weapons/Rifle/Spit-Fire bytes.h"  

#include "../img/Weapons/Special/Bow bytes.h"  
#include "../img/Weapons/Special/Devotion bytes.h"  
#include "../img/Weapons/Special/Knife bytes.h"  
#include "../img/Weapons/Special/Kraber bytes.h"  
#include "../img/Weapons/Special/R99 Bytes.h"  

#include "../img/Weapons/Sniper/ChargedRifle bytes.h"  
#include "../img/Weapons/Sniper/DMR bytes.h"  
#include "../img/Weapons/Sniper/Sentinel Bytes.h"  

#include "../img/Weapons/Energy/EMG bytes.h"  
#include "../img/Weapons/Energy/Havoc bytes.h"  
#include "../img/Weapons/Energy/Nemisis bytes.h"  
#include "../img/Weapons/Energy/Triple bytes.h"  
#include "../img/Weapons/Energy/Volt bytes.h"  

//meds  
#include "../img/Meds/evo-cache bytes.h"  
#include "../img/Meds/Med-Kit bytes.h"  
#include "../img/Meds/Med-Small bytes.h"  
#include "../img/Meds/phynix bytes.h"  
#include "../img/Meds/Shield-Large bytes.h"  
#include "../img/Meds/Shield-Small bytes.h"  

//Ammo  
#include "../img/Ammo/EnergyAmmobytes.h"  
#include "../img/Ammo/HeavyAmmobytes.h"  
#include "../img/Ammo/LightAmmobytes.h"  
#include "../img/Ammo/ShotgunAmmobytes.h"  
#include "../img/Ammo/SniperAmmobytes.h"  

//Death Box  
#include "../img/deathbox/deathboxbytes.h"  
//Skins  

//Pistols  
#include "../img/skins/p2020/Break_the_Enemy_P2020bytes.hpp"  
#include "../img/skins/p2020/Code_of_Honor_P2020bytes.hpp"  
#include "../img/skins/p2020/Eye_of_the_Storm_P2020bytes.hpp"  
#include "../img/skins/p2020/Hidden_Hazard_P2020bytes.hpp"  
#include "../img/skins/p2020/Hot_Spot_P2020bytes.hpp"  
#include "../img/skins/p2020/Off_the_Grid_P2020bytes.hpp"  
#include "../img/skins/p2020/Shadow_Web_P2020bytes.hpp"  
#include "../img/skins/p2020/Trial_by_Fire_P2020bytes.hpp"  
#include "../img/skins/re45/Blue_Fade_RE-45bytes.hpp"  
#include "../img/skins/re45/Break_the_Enemy_RE-45bytes.hpp"  
#include "../img/skins/re45/Code_of_Honor_RE-45bytes.hpp"  
#include "../img/skins/re45/Eye_of_the_Storm_RE-45bytes.hpp"  
#include "../img/skins/re45/Force_Limiter_RE-45bytes.hpp"  
#include "../img/skins/re45/Gnarly_RE-45bytes.hpp"  
#include "../img/skins/re45/Neon_Candy_RE-45bytes.hpp"  
#include "../img/skins/re45/Off_the_Grid_RE-45bytes.hpp"  
#include "../img/skins/re45/Pulse_Check_RE-45bytes.hpp"  
#include "../img/skins/re45/Recluse_RE-45bytes.hpp"  
#include "../img/skins/re45/Served_Fresh_RE-45bytes.hpp"  
#include "../img/skins/re45/Sunken_Treasure_RE-45bytes.hpp"  
#include "../img/skins/re45/The_Multipass_RE-45bytes.hpp"  
#include "../img/skins/re45/Trial_by_Fire_RE-45bytes.hpp"  
#include "../img/skins/re45/Tribal_Glyph_RE-45bytes.hpp"  
#include "../img/skins/re45/Ultraviolet_RE-45bytes.hpp"  
#include "../img/skins/Alternator/Break_the_Enemy_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Code_of_Honor_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Cyber_Hide_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Eye_of_the_Storm_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Great_Northern_Way_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Melternator_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Molten_Forge_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Off_the_Grid_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Recluse_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Star_Chart_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Summoning_Circle_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Treadrunner_Alternator_SMGbytes.hpp"  
#include "../img/skins/Alternator/Trial_by_Fire_Alternator_SMGbytes.hpp"  
#include "../img/brand/xex-image-Bytes.h"  

#define LOG(arg) std::cout << BOLDWHITE << _("[") << RED << _("Apex") << BOLDWHITE << _("] ") << BOLDWHITE << arg << _("\n");  
#define LOGF(arg) std::cout << BOLDWHITE << _("[") << CYAN << _("XEX") << BOLDWHITE << _("] ") << BOLDWHITE << arg << _("\n");  
#define LOG_DEBUG(arg) std::cout << RED << _("[DEBUG] ") << BOLDWHITE << arg << _("\n");  

#define Fail(arg) arg <= 0  
inline bool inMatch = false;  
inline std::vector<std::string> whiteListedPlayers;  
inline bool whiteListKey[] = {  
    false,  
    false,  
    false,  
    false,  
    false,  
    false,  
    false,  
    false,  
    false,  
    false  
};  

namespace WeaponIDs {  
    // Light Weapons  
    inline static int P2020 = 112;  
    inline int RE45 = 85;  
    inline int ALTERNATOR = 84;  
    inline int R99 = 111;  
    inline  int R301 = 0;  
    inline  int SPITFIRE = 113;  
    inline  int G7_SCOUT = 95;  

    // Heavy Weapons  
    inline  int FLATLINE = 94;  
    inline  int HEMLOCK = 96;  
    inline   int PROWLER = 107;  
    inline  int REPEATER_3030 = 118;  
    inline   int RAMPAGE = 6;  
    inline   int CAR = 119;  

    // Energy Weapons  
    inline  int HAVOC = 91;  
    inline   int DEVOTION = 89;  
    inline  int LSTAR = 99;  
    inline   int TRIPLE_TAKE = 114;  
    inline   int VOLT = 117;  
    inline   int NEMESIS = 120;  

    // Shotguns  
    inline int MOZAMBIQUE = 102;  
    inline  int PEACEKEEPER = 109;  
    inline  int MASTIFF = 101;  
    inline int EVA8 = 92;  

    // Sniper Rifles  
    inline   int LONGBOW = 90;  
    inline   int CHARGE_RIFLE = 87;  
    inline   int SENTINEL = 1;  

    // Legendary Weapons  
    inline   int WINGMAN = 115;  
    inline   int BOCEK = 2;  
    inline  int KRABER = 98;  
    inline   int KNIFE = 176;  
};  

struct HighlightFunctionBits  
{  
    uint8_t functionBits[4];  
};  

struct HighlightParameter  
{  
    float parameter[3];  
};  

struct CUserCmd {  
    int command_number; //0x0  
    int tick_count; //0x4  
    float command_time; //0x8  
    float viewangle_x; //0xC  
    float viewangle_y; //viewangle_x + 0x4  
    float viewangle_z; //viewangle_x + 0x8  
    char pad_0x18[0x14]; //0x18  
    float forwardmove; //0x2C  
    float sidemove; //0x30  
    float upmove; //0x34  
    int buttons; //0x38  
    char impulse; //0x3C  
};  

struct ReloadTime {  
    float r99 = 1.65f, devotion = 2.43f, Kraber = 3.5f, havoc = 2.81f, triple = 2.38f, volt = 1.61f, nemesis = 2.55f, FlatLine = 2.08f,  
        hemlock = 2.15f, prowler = 1.81f, repter = 0.82f, rampage = 2.84f, car = 1.40f, p2020 = 1.08f, re45 = 1.40f, alternator = 1.68f,  
        r301 = 1.73f, spitfire = 2.88f, scout = 2.11f, mozambique = 2.00f, eva = 2.58f, peacekeeper = 2.29f, mastiff = 0.87f, wingman = 2.04f,  
        longbow = 2.26f, chargerifle = 3.28f, sentinel = 2.45f;  
};  

inline static const std::unordered_map<int, float> weaponReloadTimeMap = {  
    {112, ReloadTime().p2020},  
    {85, ReloadTime().re45},  
    {84, ReloadTime().alternator},  
    {115, ReloadTime().wingman},  
    {92, ReloadTime().eva},  
    {101, ReloadTime().mastiff},  
    {109, ReloadTime().peacekeeper},  
    {102, ReloadTime().mozambique},  
    {119, ReloadTime().car},  
    {0, ReloadTime().r301}, // Assuming carbine is the same as "car" in reload time  
    {94, ReloadTime().FlatLine},  
    {96, ReloadTime().hemlock},  
    {107, ReloadTime().prowler},  
    {6, ReloadTime().rampage}, // Assuming Rampage is missing, so use r301 if appropriate  
    {95, ReloadTime().repter},  
    {113, ReloadTime().spitfire},  
    {89, ReloadTime().devotion},  
    {98, ReloadTime().Kraber},  
    {111, ReloadTime().r99},  
    {87, ReloadTime().chargerifle},  
    {90, ReloadTime().longbow},  
    {1, ReloadTime().sentinel},  
    {120, ReloadTime().nemesis},  
    {117, ReloadTime().volt},  
    {114, ReloadTime().triple},  
    {91, ReloadTime().havoc},  
};  
struct bounds_t {  
    float left, right, top, bottom;  
};  

inline std::array<int, 14> valid_bones = { 0,2,4,6,7,9,10,12,13,14,16,17,18 };  
struct box_bounds {  
    float left, right, top, bottom;  
    bool onscreen = false;  

    bool empty() {  
        if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)  
            return true;  

        if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)  
            return true;  

        return false;  
    }  
    static box_bounds null() {  
        return { 0, 0, 0, 0 };  
    }  
};  
enum class HitboxType {  
    Head = 0,  
    Neck = 1,  
    UpperChest = 2,  
    LowerChest = 3,  
    Stomach = 4,  
    Hip = 5,  
    Leftshoulder = 6,  
    Leftelbow = 7,  
    Lefthand = 8,  
    Rightshoulder = 9,  
    RightelbowBone = 10,  
    Righthand = 11,  
    LeftThighs = 12,  
    Leftknees = 13,  
    Leftleg = 14,  
    RightThighs = 16,  
    Rightknees = 17,  
    Rightleg = 18,  
};  

class CXBOXController  
{  
private:  
    XINPUT_STATE _controllerState;  
    DWORD _controllerNum;  
public:  
    CXBOXController(int playerNumber)  
    {  
        // Set the Controller Number  
        _controllerNum = playerNumber - 1;  
    }  

    XINPUT_STATE GetState()  
    {  
        // Zeroise the state  
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));  

        // Get the state  
        XInputGetState(_controllerNum, &_controllerState);  

        return _controllerState;  
    }  
    bool IsConnected()  
    {  
        // Zeroise the state  
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));  

        // Get the state  
        DWORD Result = XInputGetState(_controllerNum, &_controllerState);  

        if (Result == ERROR_SUCCESS)  
        {  
            return true;  
        }  
        else  
        {  
            return false;  
        }  
    }  
    void Vibrate(int leftVal, int rightVal)  
    {  
        // Create a Vibraton State  
        XINPUT_VIBRATION Vibration;  

        // Zeroise the Vibration  
        ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));  

        // Set the Vibration Values  
        Vibration.wLeftMotorSpeed = leftVal;  
        Vibration.wRightMotorSpeed = rightVal;  

        // Vibrate the controller  
        XInputSetState(_controllerNum, &Vibration);  
    }  
    bool isLeftTrigger() {  
        if (_controllerState.Gamepad.bLeftTrigger > 0) return true;  
        else return false;  
    }  
}; inline CXBOXController xbox(1);  

inline float previousPitch = 0;  
inline float previousYaw = 0;  
inline float pitchSTR = 1;  
inline float yawSTR = 1;  

struct Duck {  
    int start = 6,  
        finish = 4;  
}; inline Duck duck;  

struct Jump {  
    int start = 7,  
        dojump = 5,  
        finish = 4;  
}; inline Jump jump;  

struct ObserverState {  
    int none = 0,  
        freecam = 7;  
}; inline ObserverState observerstate;  

struct ModelState {  
    int none = 0,  
        crouch = 10,  
        jump = 118,  
        knocked = 988;  
}; inline ModelState modelstate;  

namespace LootTexture  
{  
    namespace MedTexture {  
        inline ID3D11ShaderResourceView* SmallMedTexture;  
        inline ID3D11ShaderResourceView* LargeMedTexture;  
        inline ID3D11ShaderResourceView* SmallShieldTexture;  
        inline ID3D11ShaderResourceView* LargeShieldTexture;  
        inline ID3D11ShaderResourceView* PhynioxTexture;  
        inline ID3D11ShaderResourceView* EvoCacheTexture;  
    }  
    namespace AmmoTexture {  
        inline ID3D11ShaderResourceView* SniperAmmoTexture;  
        inline ID3D11ShaderResourceView* ShotGunAmmoTexture;  
        inline ID3D11ShaderResourceView* LightAmmoTexture;  
        inline ID3D11ShaderResourceView* HeavyAmmoTexture;  
        inline ID3D11ShaderResourceView* EnergyAmmoTexture;  
    }  
    namespace Armor {  
        inline ID3D11ShaderResourceView* ShieldTexture;  
        inline ID3D11ShaderResourceView* HelmetTexture;  
    }  
}  
inline std::vector<std::pair<int, std::string>> MedList = {  
    {202, _("Sringe")},  
    {201, _("Med-Kit")},  
    {335, _("Evo-Cache")},  
    {204, _("Shield-Cell")},  
    {203, _("Shield-Battery")},  
    {200, _("Phoenix-Kit")}  
};  

inline std::vector<std::pair<int, std::string>> LightGunList = {  
    {117, _("P2020")},  
    {126, _("RE-45")},  
    {45, _("Alternator")},  
    {82, _("R-301")},  
    {77, _("M600 Spit-fire")},  
    {40, _("G7 Scout")}  
};  

inline std::vector<std::pair<int, std::string>> ShotGunList = {  
    {98, _("mozambique")},  
    {87, _("EVA")},  
    {93, _("PeaceKeeper")},  
    {2, _("Mastiff")}  
};  

inline std::vector<std::pair<int, std::string>> ShieldList = {  
    {220, _("Shield Level 1")},  
    {221, _("Shield Level 2")},  
    {222, _("Shield Level 3")},  
    {223, _("Shield Level 4")}  
};  

inline std::vector<std::pair<int, std::string>> HelmetList = {  
    {205, _("Helmet Level 1")},  
    {206, _("Helmet Level 2")},  
    {207, _("Helmet Level 3")},  
    {208, _("Helmet Level 4")}  
};  



namespace AmrmorICON  
{  
    inline ID3D11ShaderResourceView* CommonArmorTexture;  
    inline ID3D11ShaderResourceView* UncommonArmorTexture;  
    inline ID3D11ShaderResourceView* RareArmorTexture;  
    inline ID3D11ShaderResourceView* LegendaryArmorTexture;  
    inline ID3D11ShaderResourceView* MythicArmorTexture;  
}  
namespace DeathBoxIcon {  
    inline ID3D11ShaderResourceView* DeathBoxTexture;  

}  
namespace WeaponIcon  
{  
    namespace PistolICON  
    {  
        inline ID3D11ShaderResourceView* P2020Texture;  
        inline ID3D11ShaderResourceView* AlternatorTexture;  
        inline ID3D11ShaderResourceView* Re45Texture;  
        inline ID3D11ShaderResourceView* WingmenTexture;  
    }  
    namespace ShotgunICON {  
        inline ID3D11ShaderResourceView* EVA8Texture;  
        inline ID3D11ShaderResourceView* MastiffTexture;  
        inline ID3D11ShaderResourceView* MozambiqueTexture;  
        inline ID3D11ShaderResourceView* peacekeeperTexture;  
    }  
    namespace Rifle {  
        inline ID3D11ShaderResourceView* CarTexture;  
        inline ID3D11ShaderResourceView* CarbineTexture;  
        inline ID3D11ShaderResourceView* FlatlineTexture;  
        inline ID3D11ShaderResourceView* HemlockTexture;  
        inline ID3D11ShaderResourceView* ProwlerTexture;  
        inline ID3D11ShaderResourceView* RampageTexture;  
        inline ID3D11ShaderResourceView* RepeaterTexture;  
        inline ID3D11ShaderResourceView* ScoutTexture;  
        inline ID3D11ShaderResourceView* SpitFireTexture;  
    }  
    namespace Special {  
        inline ID3D11ShaderResourceView* BowTexture;  
        inline ID3D11ShaderResourceView* DevotionTexture;  
        inline ID3D11ShaderResourceView* KnifeTexture;  
        inline ID3D11ShaderResourceView* KraberTexture;  
        inline ID3D11ShaderResourceView* R99Texture;  
    }  
    namespace Sniper {  
        inline ID3D11ShaderResourceView* ChargedRifleTexture;  
        inline ID3D11ShaderResourceView* DMRTexture;  
        inline ID3D11ShaderResourceView* SentinelTexture;  

    }  
    namespace Energy {  
        inline ID3D11ShaderResourceView* NemesisTexture;  
        inline ID3D11ShaderResourceView* VoltTexture;  
        inline ID3D11ShaderResourceView* TripleTexture;  
        inline ID3D11ShaderResourceView* EMGTexture;  
        inline ID3D11ShaderResourceView* HAVOCTexture;  

    }  
}  

inline ImFont* Modern;  
inline ImFont* Original;  

inline ID3D11ShaderResourceView* Peter_Texture;  
inline ID3D11ShaderResourceView* SexyGirlTexture;  
inline ID3D11ShaderResourceView* Kitten_Texture;  

namespace WeaponSkins {  
    namespace Pistol {  
        inline std::vector<std::pair<std::string, int>> P2020 = {  
            {_("EyeOfTheStorm"), 2},  
            {_("TrialByFire"), 3},  
            {_("CodeOfHonor"), 4},  
            {_("OffTheGrid"), 5},  
            {_("BreakTheEnemy"), 6},  
            {_("ShadowWeb"), 8},  
            {_("HotSpot"), 9},  
            {_("HiddenHazard"), 10}  
        };  
        inline std::vector<std::pair<std::string, int>> RE45 = {  
            {_("Recluse"), 1},  
            {_("EyeOfTheStorm"), 2},  
            {_("TrialByFire"), 3},  
            {_("CodeOfHonor"), 4},  
            {_("OffTheGrid"), 5},  
            {_("BreakTheEnemy"), 6},  
            {_("BlueFade"), 7},  
            {_("Gnarly"), 8},  
            {_("PulseCheck"), 9},  
            {_("TribalGlyph"), 10},  
            {_("NeonCandy"), 11},  
            {_("ForceLimiter"), 12},  
            {_("ServedFresh"), 13},  
            {_("TheMultiPass"), 14},  
            {_("SunkenTreasure"), 15},  
            {_("UltraViolet"), 16}  
        };  
        inline std::vector<std::pair<std::string, int>> Alternator = {  
            {_("Recluse"), 1},  
            {_("EyeOfTheStorm"), 2},  
            {_("TrialByFire"), 3},  
            {_("CodeOfHonor"), 4},  
            {_("OffTheGrid"), 5},  
            {_("BreakTheEnemy"), 6},  
            {_("MoltenForge"), 7},  
            {_("Melternator"), 8},  
            {_("StarChart"), 10},  
            {_("TreadRunner"), 11},  
            {_("CyberHide"), 12},  
            {_("Spotted"), 13},  
            {_("GreatNorthernWay"), 14},  
            {_("SummoningCircle"), 15},  
            {_("HiddenSkinOne"), 16},  
            {_("HiddenSkinTwo"), 17}  
        };  
        inline std::vector<std::pair<std::string, int>> Mozambique = {  
            {_("TrailByFire"), 3},  
            {_("CodeOfHonor"), 4},  
            {_("OffTheGrid"), 5},  
            {_("BreakTheEnemy"), 6},  
            {_("ScavengerHunt"), 7},  
            {_("OnyxHammer"), 8},  
            {_("HiddenSkinOne"), 9}  
        };  
        inline std::vector<std::pair<std::string, int>> Wingman = {  
            {_("ColdFusion"), 1},  
            {_("EyeOfTheStorm"), 2},  
            {_("TrialByTheFire"), 3},  
            {_("CodeOfHonor"), 4},  
            {_("OffTheGride"), 5},  
            {_("BreakTheEnemy"), 6},  
            {_("ArticBlaster"), 7},  
            {_("EternalLife"), 8},  
            {_("CrimsonKing"), 9},  
            {_("DragonWing"), 10},  
            {_("GladiatoryTrophy"), 11},  
            {_("BrokenWing"), 12},  
            {_("WingsOfMorjen"), 13},  
            {_("ArcticFox"), 14},  
            {_("RealityEradicator"), 15},  
            {_("BattleBlaster"), 16},  
            {_("HiddenSkinOne"), 17},  
            {_("HiddenSkinTwo"), 18},  
            {_("HiddenSkinThree"), 19}  
        };  
    }  
}  

namespace SelectedSkin {  
    namespace Pistol  
    {  
        namespace p2020 {  
            inline bool P2020[8];  
            namespace Texture {  
                inline ID3D11ShaderResourceView* EyeOfTheStorm;  
                inline ID3D11ShaderResourceView* TrialByFire;  
                inline ID3D11ShaderResourceView* CodeOfHonor;  
                inline ID3D11ShaderResourceView* OffTheGrid;  
                inline ID3D11ShaderResourceView* BreakTheEnemy;  
                inline ID3D11ShaderResourceView* ShadowWeb;  
                inline ID3D11ShaderResourceView* HotSpot;  
                inline ID3D11ShaderResourceView* HiddenHazard;  
            }  
        }  
        namespace re45 {  
            inline bool re45[15];  
            namespace Texture {  
                inline ID3D11ShaderResourceView* Recluse;  
                inline ID3D11ShaderResourceView* EyeOfTheStorm;  
                inline ID3D11ShaderResourceView* TrialByFire;  
                inline ID3D11ShaderResourceView* CodeOfHonor;  
                inline ID3D11ShaderResourceView* OffTheGrid;  
                inline ID3D11ShaderResourceView* BreakTheEnemy;  
                inline ID3D11ShaderResourceView* BlueFade;  
                inline ID3D11ShaderResourceView* Gnarly;  
                inline ID3D11ShaderResourceView* PulseCheck;  
                inline ID3D11ShaderResourceView* TribalGlyph;  
                inline ID3D11ShaderResourceView* NeonCandy;  
                inline ID3D11ShaderResourceView* ForceLimiter;  
                inline ID3D11ShaderResourceView* ServedFresh;  
                inline ID3D11ShaderResourceView* TheMultiPass;  
                inline ID3D11ShaderResourceView* SunkenTreasure;  
                inline ID3D11ShaderResourceView* UltraViolet;  

            }  
        }  

        namespace alternator  
        {  
            inline bool alternator[13];  
            namespace Texture {  
                inline ID3D11ShaderResourceView* Recluse;  
                inline ID3D11ShaderResourceView* EyeOfTheStorm;  
                inline ID3D11ShaderResourceView* TrialByFire;  
                inline ID3D11ShaderResourceView* CodeOfHonor;  
                inline ID3D11ShaderResourceView* OffTheGrid;  
                inline ID3D11ShaderResourceView* BreakTheEnemy;  
                inline ID3D11ShaderResourceView* MoltenForge;  
                inline ID3D11ShaderResourceView* Melternator;  
                inline ID3D11ShaderResourceView* StarChart;  
                inline ID3D11ShaderResourceView* TreadRunner;  
                inline ID3D11ShaderResourceView* CyberHide;  
                inline ID3D11ShaderResourceView* GreatNorthernWay;  
                inline ID3D11ShaderResourceView* SummoningCircle;  

            }  

        }  
        inline bool PistolSelected[3] = { false,false,false };  
    }  
}
#pragma comment(lib, "D3DX11.lib")

#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

#include "../utils/callspoof.hpp"

#define RESET   _("\033[0m")
#define BLACK   _("\033[30m")     /* Black */
#define RED      _("\033[31m")     /* Red */
#define GREEN    _("\033[32m")    /* Green */
#define YELLOW   _("\033[33m")   /* Yellow */
#define BLUE     _("\033[34m")  /* Blue */
#define MAGENTA  _("\033[35m") /* Magenta */
#define CYAN     _("\033[36m")/* Cyan */
#define WHITE    _("\033[37m")/* White */
#define BOLDBLACK    _("\033[1m\033[30m")      /* Bold Black */
#define BOLDRED      _("\033[1m\033[31m")      /* Bold Red */
#define BOLDGREEN    _("\033[1m\033[32m")      /* Bold Green */
#define BOLDYELLOW   _("\033[1m\033[33m")      /* Bold Yellow */
#define BOLDBLUE     _("\033[1m\033[34m")      /* Bold Blue */
#define BOLDMAGENTA  _("\033[1m\033[35m")      /* Bold Magenta */
#define BOLDCYAN     _("\033[1m\033[36m")      /* Bold Cyan */
#define BOLDWHITE    _("\033[1m\033[37m")      /* Bold White */

#include "../interface.h"
#include "../utils/xor.hpp"
#include "../utils/returnspoof.hpp"
#include "../Custom Radar/Webradar.hpp"
#include "../imgui/imgui_internal.h"

//Armor ICON
#include "../img/Armor/Common Armor Bytes.h"
#include "../img/Armor/Uncommon Armor Bytes.h"
#include "../img/Armor/Rare Armor Bytes.h"
#include "../img/Armor/Legendary Armor Bytes.h"
#include "../img/Armor/Mythic Armor Bytes.h"
#include "../img/Armor/Helmetbytes.h"
#include "../img/Cartoon/Peter_Griffen.h"
#include "../img/Cartoon/EKitten.h"

//WEAPON ICON
#include "../img/Weapons/Pistol/p2020 bytes.h"
#include "../img/Weapons/Pistol/alternator bytes.h"
#include "../img/Weapons/Pistol/re45 bytes.h"
#include "../img/Weapons/Pistol/wingmen bytes.h"

#include "../img/Weapons/Shotgun/eva_8_auto bytes.h"
#include "../img/Weapons/Shotgun/mastiff bytes.h"
#include "../img/Weapons/Shotgun/mozambique bytes.h"
#include "../img/Weapons/Shotgun/peacekeeper bytes.h"

#include "../img/Weapons/Rifle/car bytes.h"
#include "../img/Weapons/Rifle/Carbine bytes.h"
#include "../img/Weapons/Rifle/Flatline bytes.h"
#include "../img/Weapons/Rifle/Hemlok bytes.h"
#include "../img/Weapons/Rifle/Prowler bytes.h"
#include "../img/Weapons/Rifle/Rampage bytes.h"
#include "../img/Weapons/Rifle/Repeater bytes.h"
#include "../img/Weapons/Rifle/scout bytes.h"
#include "../img/Weapons/Rifle/Spit-Fire bytes.h"

#include "../img/Weapons/Special/Bow bytes.h"
#include "../img/Weapons/Special/Devotion bytes.h"
#include "../img/Weapons/Special/Knife bytes.h"
#include "../img/Weapons/Special/Kraber bytes.h"
#include "../img/Weapons/Special/R99 Bytes.h"

#include "../img/Weapons/Sniper/ChargedRifle bytes.h"
#include "../img/Weapons/Sniper/DMR bytes.h"
#include "../img/Weapons/Sniper/Sentinel Bytes.h"


#include "../img/Weapons/Energy/EMG bytes.h"
#include "../img/Weapons/Energy/Havoc bytes.h"
#include "../img/Weapons/Energy/Nemisis bytes.h"
#include "../img/Weapons/Energy/Triple bytes.h"
#include "../img/Weapons/Energy/Volt bytes.h"


//meds
#include "../img/Meds/evo-cache bytes.h"
#include "../img/Meds/Med-Kit bytes.h"
#include "../img/Meds/Med-Small bytes.h"
#include "../img/Meds/phynix bytes.h"
#include "../img/Meds/Shield-Large bytes.h"
#include "../img/Meds/Shield-Small bytes.h"


//Ammo
#include "../img/Ammo/EnergyAmmobytes.h"
#include "../img/Ammo/HeavyAmmobytes.h"
#include "../img/Ammo/LightAmmobytes.h"
#include "../img/Ammo/ShotgunAmmobytes.h"
#include "../img/Ammo/SniperAmmobytes.h"

//Death Box
#include "../img/deathbox/deathboxbytes.h"
//Skins

//Pistols
#include "../img/skins/p2020/Break_the_Enemy_P2020bytes.hpp"
#include "../img/skins/p2020/Code_of_Honor_P2020bytes.hpp"
#include "../img/skins/p2020/Eye_of_the_Storm_P2020bytes.hpp"
#include "../img/skins/p2020/Hidden_Hazard_P2020bytes.hpp"
#include "../img/skins/p2020/Hot_Spot_P2020bytes.hpp"
#include "../img/skins/p2020/Off_the_Grid_P2020bytes.hpp"
#include "../img/skins/p2020/Shadow_Web_P2020bytes.hpp"
#include "../img/skins/p2020/Trial_by_Fire_P2020bytes.hpp"
#include "../img/skins/re45/Blue_Fade_RE-45bytes.hpp"
#include "../img/skins/re45/Break_the_Enemy_RE-45bytes.hpp"
#include "../img/skins/re45/Code_of_Honor_RE-45bytes.hpp"
#include "../img/skins/re45/Eye_of_the_Storm_RE-45bytes.hpp"
#include "../img/skins/re45/Force_Limiter_RE-45bytes.hpp"
#include "../img/skins/re45/Gnarly_RE-45bytes.hpp"
#include "../img/skins/re45/Neon_Candy_RE-45bytes.hpp"
#include "../img/skins/re45/Off_the_Grid_RE-45bytes.hpp"
#include "../img/skins/re45/Pulse_Check_RE-45bytes.hpp"
#include "../img/skins/re45/Recluse_RE-45bytes.hpp"
#include "../img/skins/re45/Served_Fresh_RE-45bytes.hpp"
#include "../img/skins/re45/Sunken_Treasure_RE-45bytes.hpp"
#include "../img/skins/re45/The_Multipass_RE-45bytes.hpp"
#include "../img/skins/re45/Trial_by_Fire_RE-45bytes.hpp"
#include "../img/skins/re45/Tribal_Glyph_RE-45bytes.hpp"
#include "../img/skins/re45/Ultraviolet_RE-45bytes.hpp"
#include "../img/skins/Alternator/Break_the_Enemy_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Code_of_Honor_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Cyber_Hide_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Eye_of_the_Storm_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Great_Northern_Way_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Melternator_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Molten_Forge_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Off_the_Grid_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Recluse_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Star_Chart_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Summoning_Circle_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Treadrunner_Alternator_SMGbytes.hpp"
#include "../img/skins/Alternator/Trial_by_Fire_Alternator_SMGbytes.hpp"
#include "../img/brand/xex-image-Bytes.h"

#define LOG(arg) std::cout << BOLDWHITE << _("[") << RED << _("Apex") << BOLDWHITE << _("] ") << BOLDWHITE << arg << _("\n");
#define LOGF(arg) std::cout << BOLDWHITE << _("[") << CYAN << _("XEX") << BOLDWHITE << _("] ") << BOLDWHITE << arg << _("\n");
#define LOG_DEBUG(arg) std::cout << RED << _("[DEBUG] ") << BOLDWHITE << arg << _("\n");

#define Fail(arg) arg <= 0
inline bool inMatch = false;
inline std::vector<std::string> whiteListedPlayers;
inline bool whiteListKey[] = {
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
};

namespace WeaponIDs {
    // Light Weapons
    inline static int P2020 = 112;
    inline int RE45 = 85;
    inline int ALTERNATOR = 84;
    inline int R99 = 111;
    inline  int R301 = 0;
    inline  int SPITFIRE = 113;
    inline  int G7_SCOUT = 95;

    // Heavy Weapons
    inline  int FLATLINE = 94;
    inline  int HEMLOCK = 96;
    inline   int PROWLER = 107;
    inline  int REPEATER_3030 = 118;
    inline   int RAMPAGE = 6;
    inline   int CAR = 119;

    // Energy Weapons
    inline  int HAVOC = 91;
    inline   int DEVOTION = 89;
    inline  int LSTAR = 99;
    inline   int TRIPLE_TAKE = 114;
    inline   int VOLT = 117;
    inline   int NEMESIS = 120;

    // Shotguns
    inline int MOZAMBIQUE = 102;
    inline  int PEACEKEEPER = 109;
    inline  int MASTIFF = 101;
    inline int EVA8 = 92;

    // Sniper Rifles
    inline   int LONGBOW = 90;
    inline   int CHARGE_RIFLE = 87;
    inline   int SENTINEL = 1;

    // Legendary Weapons
    inline   int WINGMAN = 115;
    inline   int BOCEK = 2;
    inline  int KRABER = 98;
    inline   int KNIFE = 176;
};

struct HighlightFunctionBits
{
    uint8_t functionBits[4];
};

struct HighlightParameter
{
    float parameter[3];
};

struct CUserCmd {
    int command_number; //0x0
    int tick_count; //0x4
    float command_time; //0x8
    float viewangle_x; //0xC
    float viewangle_y; //viewangle_x + 0x4
    float viewangle_z; //viewangle_x + 0x8
    char pad_0x18[0x14]; //0x18
    float forwardmove; //0x2C
    float sidemove; //0x30
    float upmove; //0x34
    int buttons; //0x38
    char impulse; //0x3C
};

struct ReloadTime {
    float r99 = 1.65f, devotion = 2.43f, Kraber = 3.5f, havoc = 2.81f, triple = 2.38f, volt = 1.61f, nemesis = 2.55f, FlatLine = 2.08f,
        hemlock = 2.15f, prowler = 1.81f, repter = 0.82f, rampage = 2.84f, car = 1.40f, p2020 = 1.08f, re45 = 1.40f, alternator = 1.68f,
        r301 = 1.73f, spitfire = 2.88f, scout = 2.11f, mozambique = 2.00f, eva = 2.58f, peacekeeper = 2.29f, mastiff = 0.87f, wingman = 2.04f,
        longbow = 2.26f, chargerifle = 3.28f, sentinel = 2.45f;
};

inline static const std::unordered_map<int, float> weaponReloadTimeMap = {
    {112, ReloadTime().p2020},
    {85, ReloadTime().re45},
    {84, ReloadTime().alternator},
    {115, ReloadTime().wingman},
    {92, ReloadTime().eva},
    {101, ReloadTime().mastiff},
    {109, ReloadTime().peacekeeper},
    {102, ReloadTime().mozambique},
    {119, ReloadTime().car},
    {0, ReloadTime().r301}, // Assuming carbine is the same as "car" in reload time
    {94, ReloadTime().FlatLine},
    {96, ReloadTime().hemlock},
    {107, ReloadTime().prowler},
    {6, ReloadTime().rampage}, // Assuming Rampage is missing, so use r301 if appropriate
    {95, ReloadTime().repter},
    {113, ReloadTime().spitfire},
    {89, ReloadTime().devotion},
    {98, ReloadTime().Kraber},
    {111, ReloadTime().r99},
    {87, ReloadTime().chargerifle},
    {90, ReloadTime().longbow},
    {1, ReloadTime().sentinel},
    {120, ReloadTime().nemesis},
    {117, ReloadTime().volt},
    {114, ReloadTime().triple},
    {91, ReloadTime().havoc},
};
struct bounds_t {
    float left, right, top, bottom;
};

inline std::array<int, 14> valid_bones = { 0,2,4,6,7,9,10,12,13,14,16,17,18 };
struct box_bounds {
    float left, right, top, bottom;
    bool onscreen = false;

    bool empty() {
        if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
            return true;

        if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
            return true;

        return false;
    }
    static box_bounds null() {
        return { 0, 0, 0, 0 };
    }
};
enum class HitboxType {
    Head = 0,
    Neck = 1,
    UpperChest = 2,
    LowerChest = 3,
    Stomach = 4,
    Hip = 5,
    Leftshoulder = 6,
    Leftelbow = 7,
    Lefthand = 8,
    Rightshoulder = 9,
    RightelbowBone = 10,
    Righthand = 11,
    LeftThighs = 12,
    Leftknees = 13,
    Leftleg = 14,
    RightThighs = 16,
    Rightknees = 17,
    Rightleg = 18,
};

class CXBOXController
{
private:
    XINPUT_STATE _controllerState;
    DWORD _controllerNum;
public:
    CXBOXController(int playerNumber)
    {
        // Set the Controller Number
        _controllerNum = playerNumber - 1;
    }

    XINPUT_STATE GetState()
    {
        // Zeroise the state
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        // Get the state
        XInputGetState(_controllerNum, &_controllerState);

        return _controllerState;
    }
    bool IsConnected()
    {
        // Zeroise the state
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        // Get the state
        DWORD Result = XInputGetState(_controllerNum, &_controllerState);

        if (Result == ERROR_SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Vibrate(int leftVal, int rightVal)
    {
        // Create a Vibraton State
        XINPUT_VIBRATION Vibration;

        // Zeroise the Vibration
        ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

        // Set the Vibration Values
        Vibration.wLeftMotorSpeed = leftVal;
        Vibration.wRightMotorSpeed = rightVal;

        // Vibrate the controller
        XInputSetState(_controllerNum, &Vibration);
    }
    bool isLeftTrigger() {
        if (_controllerState.Gamepad.bLeftTrigger > 0) return true;
        else return false;
    }
}; inline CXBOXController xbox(1);

inline float previousPitch = 0;
inline float previousYaw = 0;
inline float pitchSTR = 1;
inline float yawSTR = 1;

struct Duck {
    int start = 6,
        finish = 4;
}; inline Duck duck;

struct Jump {
    int start = 7,
        dojump = 5,
        finish = 4;
}; inline Jump jump;

struct ObserverState {
    int none = 0,
        freecam = 7;
}; inline ObserverState observerstate;

struct ModelState {
    int none = 0,
        crouch = 10,
        jump = 118,
        knocked = 988;
}; inline ModelState modelstate;

namespace LootTexture
{
    namespace MedTexture {
        inline ID3D11ShaderResourceView* SmallMedTexture;
        inline ID3D11ShaderResourceView* LargeMedTexture;
        inline ID3D11ShaderResourceView* SmallShieldTexture;
        inline ID3D11ShaderResourceView* LargeShieldTexture;
        inline ID3D11ShaderResourceView* PhynioxTexture;
        inline ID3D11ShaderResourceView* EvoCacheTexture;
    }
    namespace AmmoTexture {
        inline ID3D11ShaderResourceView* SniperAmmoTexture;
        inline ID3D11ShaderResourceView* ShotGunAmmoTexture;
        inline ID3D11ShaderResourceView* LightAmmoTexture;
        inline ID3D11ShaderResourceView* HeavyAmmoTexture;
        inline ID3D11ShaderResourceView* EnergyAmmoTexture;
    }
    namespace Armor {
        inline ID3D11ShaderResourceView* ShieldTexture;
        inline ID3D11ShaderResourceView* HelmetTexture;
    }
}
inline std::vector<std::pair<int, std::string>> MedList = {
    {202, _("Sringe")},
    {201, _("Med-Kit")},
    {335, _("Evo-Cache")},
    {204, _("Shield-Cell")},
    {203, _("Shield-Battery")},
    {200, _("Phoenix-Kit")}
};

inline std::vector<std::pair<int, std::string>> LightGunList = {
    {117, _("P2020")},
    {126, _("RE-45")},
    {45, _("Alternator")},
    {82, _("R-301")},
    {77, _("M600 Spit-fire")},
    {40, _("G7 Scout")}
};

inline std::vector<std::pair<int, std::string>> ShotGunList = {
    {98, _("mozambique")},
    {87, _("EVA")},
    {93, _("PeaceKeeper")},
    {2, _("Mastiff")}
};

inline std::vector<std::pair<int, std::string>> ShieldList = {
    {220, _("Shield Level 1")},
    {221, _("Shield Level 2")},
    {222, _("Shield Level 3")},
    {223, _("Shield Level 4")}
};

inline std::vector<std::pair<int, std::string>> HelmetList = {
    {205, _("Helmet Level 1")},
    {206, _("Helmet Level 2")},
    {207, _("Helmet Level 3")},
    {208, _("Helmet Level 4")}
};



namespace AmrmorICON
{
    inline ID3D11ShaderResourceView* CommonArmorTexture;
    inline ID3D11ShaderResourceView* UncommonArmorTexture;
    inline ID3D11ShaderResourceView* RareArmorTexture;
    inline ID3D11ShaderResourceView* LegendaryArmorTexture;
    inline ID3D11ShaderResourceView* MythicArmorTexture;
}
namespace DeathBoxIcon {
    inline ID3D11ShaderResourceView* DeathBoxTexture;

}
namespace WeaponIcon
{
    namespace PistolICON
    {
        inline ID3D11ShaderResourceView* P2020Texture;
        inline ID3D11ShaderResourceView* AlternatorTexture;
        inline ID3D11ShaderResourceView* Re45Texture;
        inline ID3D11ShaderResourceView* WingmenTexture;
    }
    namespace ShotgunICON {
        inline ID3D11ShaderResourceView* EVA8Texture;
        inline ID3D11ShaderResourceView* MastiffTexture;
        inline ID3D11ShaderResourceView* MozambiqueTexture;
        inline ID3D11ShaderResourceView* peacekeeperTexture;
    }
    namespace Rifle {
        inline ID3D11ShaderResourceView* CarTexture;
        inline ID3D11ShaderResourceView* CarbineTexture;
        inline ID3D11ShaderResourceView* FlatlineTexture;
        inline ID3D11ShaderResourceView* HemlockTexture;
        inline ID3D11ShaderResourceView* ProwlerTexture;
        inline ID3D11ShaderResourceView* RampageTexture;
        inline ID3D11ShaderResourceView* RepeaterTexture;
        inline ID3D11ShaderResourceView* ScoutTexture;
        inline ID3D11ShaderResourceView* SpitFireTexture;
    }
    namespace Special {
        inline ID3D11ShaderResourceView* BowTexture;
        inline ID3D11ShaderResourceView* DevotionTexture;
        inline ID3D11ShaderResourceView* KnifeTexture;
        inline ID3D11ShaderResourceView* KraberTexture;
        inline ID3D11ShaderResourceView* R99Texture;
    }
    namespace Sniper {
        inline ID3D11ShaderResourceView* ChargedRifleTexture;
        inline ID3D11ShaderResourceView* DMRTexture;
        inline ID3D11ShaderResourceView* SentinelTexture;

    }
    namespace Energy {
        inline ID3D11ShaderResourceView* NemesisTexture;
        inline ID3D11ShaderResourceView* VoltTexture;
        inline ID3D11ShaderResourceView* TripleTexture;
        inline ID3D11ShaderResourceView* EMGTexture;
        inline ID3D11ShaderResourceView* HAVOCTexture;

    }
}

inline ImFont* Modern;
inline ImFont* Original;

inline ID3D11ShaderResourceView* Peter_Texture;
inline ID3D11ShaderResourceView* SexyGirlTexture;
inline ID3D11ShaderResourceView* Kitten_Texture;

namespace WeaponSkins {
    namespace Pistol {
        inline std::vector<std::pair<std::string, int>> P2020 = {
            {_("EyeOfTheStorm"), 2},
            {_("TrialByFire"), 3},
            {_("CodeOfHonor"), 4},
            {_("OffTheGrid"), 5},
            {_("BreakTheEnemy"), 6},
            {_("ShadowWeb"), 8},
            {_("HotSpot"), 9},
            {_("HiddenHazard"), 10}
        };
        inline std::vector<std::pair<std::string, int>> RE45 = {
            {_("Recluse"), 1},
            {_("EyeOfTheStorm"), 2},
            {_("TrialByFire"), 3},
            {_("CodeOfHonor"), 4},
            {_("OffTheGrid"), 5},
            {_("BreakTheEnemy"), 6},
            {_("BlueFade"), 7},
            {_("Gnarly"), 8},
            {_("PulseCheck"), 9},
            {_("TribalGlyph"), 10},
            {_("NeonCandy"), 11},
            {_("ForceLimiter"), 12},
            {_("ServedFresh"), 13},
            {_("TheMultiPass"), 14},
            {_("SunkenTreasure"), 15},
            {_("UltraViolet"), 16}
        };
        inline std::vector<std::pair<std::string, int>> Alternator = {
            {_("Recluse"), 1},
            {_("EyeOfTheStorm"), 2},
            {_("TrialByFire"), 3},
            {_("CodeOfHonor"), 4},
            {_("OffTheGrid"), 5},
            {_("BreakTheEnemy"), 6},
            {_("MoltenForge"), 7},
            {_("Melternator"), 8},
            {_("StarChart"), 10},
            {_("TreadRunner"), 11},
            {_("CyberHide"), 12},
            {_("Spotted"), 13},
            {_("GreatNorthernWay"), 14},
            {_("SummoningCircle"), 15},
            {_("HiddenSkinOne"), 16},
            {_("HiddenSkinTwo"), 17}
        };
        inline std::vector<std::pair<std::string, int>> Mozambique = {
            {_("TrailByFire"), 3},
            {_("CodeOfHonor"), 4},
            {_("OffTheGrid"), 5},
            {_("BreakTheEnemy"), 6},
            {_("ScavengerHunt"), 7},
            {_("OnyxHammer"), 8},
            {_("HiddenSkinOne"), 9}
        };
        inline std::vector<std::pair<std::string, int>> Wingman = {
            {_("ColdFusion"), 1},
            {_("EyeOfTheStorm"), 2},
            {_("TrialByTheFire"), 3},
            {_("CodeOfHonor"), 4},
            {_("OffTheGride"), 5},
            {_("BreakTheEnemy"), 6},
            {_("ArticBlaster"), 7},
            {_("EternalLife"), 8},
            {_("CrimsonKing"), 9},
            {_("DragonWing"), 10},
            {_("GladiatoryTrophy"), 11},
            {_("BrokenWing"), 12},
            {_("WingsOfMorjen"), 13},
            {_("ArcticFox"), 14},
            {_("RealityEradicator"), 15},
            {_("BattleBlaster"), 16},
            {_("HiddenSkinOne"), 17},
            {_("HiddenSkinTwo"), 18},
            {_("HiddenSkinThree"), 19}
        };
    }
}

namespace SelectedSkin {
    namespace Pistol
    {
        namespace p2020 {
            inline bool P2020[8];
            namespace Texture {
                inline ID3D11ShaderResourceView* EyeOfTheStorm;
                inline ID3D11ShaderResourceView* TrialByFire;
                inline ID3D11ShaderResourceView* CodeOfHonor;
                inline ID3D11ShaderResourceView* OffTheGrid;
                inline ID3D11ShaderResourceView* BreakTheEnemy;
                inline ID3D11ShaderResourceView* ShadowWeb;
                inline ID3D11ShaderResourceView* HotSpot;
                inline ID3D11ShaderResourceView* HiddenHazard;
            }
        }
        namespace re45 {
            inline bool re45[15];
            namespace Texture {
                inline ID3D11ShaderResourceView* Recluse;
                inline ID3D11ShaderResourceView* EyeOfTheStorm;
                inline ID3D11ShaderResourceView* TrialByFire;
                inline ID3D11ShaderResourceView* CodeOfHonor;
                inline ID3D11ShaderResourceView* OffTheGrid;
                inline ID3D11ShaderResourceView* BreakTheEnemy;
                inline ID3D11ShaderResourceView* BlueFade;
                inline ID3D11ShaderResourceView* Gnarly;
                inline ID3D11ShaderResourceView* PulseCheck;
                inline ID3D11ShaderResourceView* TribalGlyph;
                inline ID3D11ShaderResourceView* NeonCandy;
                inline ID3D11ShaderResourceView* ForceLimiter;
                inline ID3D11ShaderResourceView* ServedFresh;
                inline ID3D11ShaderResourceView* TheMultiPass;
                inline ID3D11ShaderResourceView* SunkenTreasure;
                inline ID3D11ShaderResourceView* UltraViolet;

            }
        }

        namespace alternator
        {
            inline bool alternator[13];
            namespace Texture {
                inline ID3D11ShaderResourceView* Recluse;
                inline ID3D11ShaderResourceView* EyeOfTheStorm;
                inline ID3D11ShaderResourceView* TrialByFire;
                inline ID3D11ShaderResourceView* CodeOfHonor;
                inline ID3D11ShaderResourceView* OffTheGrid;
                inline ID3D11ShaderResourceView* BreakTheEnemy;
                inline ID3D11ShaderResourceView* MoltenForge;
                inline ID3D11ShaderResourceView* Melternator;
                inline ID3D11ShaderResourceView* StarChart;
                inline ID3D11ShaderResourceView* TreadRunner;
                inline ID3D11ShaderResourceView* CyberHide;
                inline ID3D11ShaderResourceView* GreatNorthernWay;
                inline ID3D11ShaderResourceView* SummoningCircle;

            }

        }
        inline bool PistolSelected[3] = { false,false,false };
    }
}

