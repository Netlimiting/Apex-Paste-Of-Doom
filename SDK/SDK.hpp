#include <mutex>
#include <unordered_map>
#include <deque>

#include "../utils/includes.hpp"
#include "../utils/offsets.hpp"
#include "../utils/Vector.hpp"

class SDK {
public:
    uintptr_t mtrix = 0;
    class Game {
    public: class Get {
    public: std::uint64_t getAddress();
    private: std::uintptr_t Address;
    };
          class Script : public Get {
          public: std::string GetName(int i);
                std::string getModelName();

                std::string getSignifierName();

          };
          class WorldToScreen : public Script {
          public: Vector3 W2S(Vector3 Position);
          };
    };
    class Glow : public Game::Get {
    public:
    };
    class Loot {
    public:
        int GetIndex();
        Vector3 GetPosition();
    };
    class Entity : public SDK::Game::WorldToScreen {
    public:

        class Weapon : public SDK::Game::Get {
        public:
            int GetAmmoCount();
            bool Reloading();
        };
        class Collision : public SDK::Game::Get {
        public:
            Vector3 Get_VecMin();
            Vector3 Get_VecMax();
            Vector3 Get_vecSpecifiedSurroundingMins();
            Vector3 Get_vecSpecifiedSurroundingMaxs();

            int Get_SolidFlags();
            int Get_SolidType();
            int Get_triggerBloat();
            int Get_collisionDetailLevel();
            int Get_SurroundType();
        };
        class Projectile : public SDK::Game::Get
        {
        public:
            void Set_ProjectilePerShot(int Projectile);
            void Set_ProjectilePerDelpoy(int Projectile);
            void Set_ProjectileGravity(float gravity);
            void Set_FireRate(float fireRate);
            void Set_ProjectileOwnerVelocity(float Velocity);
            void Set_ProjectileAirFriction(float Frication);
            void Set_ProjectileDrag(float Drag);
            float Get_ProjectileGravity();
            void Set_CrosshairSpread(int spread);
            void Set_SpreadRadius(int radius);
            int Get_CrosshairSpread();
            int Get_SpreadRaidus();
            float Get_ProjectileSpeed();
            bool IsSemi();
        };
        
        int Health;
        int Shield;
        int Max_Shield;
        int Shield_Type;
        int Level;
        bool Is_Alive;
        bool IsPlayer;
        bool IsLocalPlayer;
        float Distance;
        float Width;
        float Height;
        std::string Name;
        std::string Operator;
        Vector3 Feet_Position;
        Vector3 Head_Position;       
        bool Update();
        int Get_Current_shield();
        int BleedOutState();
        int Get_Max_shield();
        int Get_shield_type();
        int Get_Network_Flags();
        int Get_TeamNum();
        int Get_Squad();
        bool Get_Alive();
        bool Get_IsLocalPlayer();
        float Get_Height();
        float Get_Width();
        Vector3 Get_Position();
        Vector3 getBonePos(int ID);
        Vector3 GetBonePositionByHitBox(int ID);
        Vector3 ViewAngles();
        Vector2 Get_Punch();
        void SetViewAngles(Vector2 Angles);
        float GetDistance();
        bool Get_IsPlayer();
        float LastKillTime();
        int Current_Health();
        float Get_LastDeathTime();
        int Get_Level();
        int GetFlags();
        std::string GetOperator();
        int GetWeaponIndex();
        std::string get_weapon_name();
        float Get_WorldTime();
        bool Is_Spectating();
        float Get_LastVisibleTime();
        void Set_HitBoxSize(float size);
        void Set_WeaponSize(float size);
        void SetSkin(int ID);
        void Set_CharacterSkin(int ID);
        void Set_Fov(float fov);
        void Set_AnimationMask(int animationSequence);
        int Get_AnimationMask();
        void Set_ObserverMode(int mode);
        void Set_ServerModelState(int ModelState);
        int Get_GrappleState();
        void Do_ThirdPerson();
        void Reset_ThirdPerson();
        float Get_TraversalStartTime();
        float Get_TraversalProgress();
        Collision* Get_Collision();
        Projectile* Get_Projectile();
        Weapon* GetWeapon();
        Entity* LocalPlayer();
        Glow* GetGlow();
    };

    std::mutex PlayerUpdateMutex;
    std::uint64_t R5Apex = NULL;
    SDK::Entity* LocalPlayer;
    Vector2 DisplaySize = {static_cast<float>(GetSystemMetrics(0)), static_cast<float>(GetSystemMetrics(1))};
}; inline SDK sdk;

struct PlayerData {
    SDK::Entity* ClassAccess;
    std::string name;
    std::string weaponName;
    std::string operatorName;
};

inline int visentcount = 0;
inline uint64_t GameAssmebly = 0;
inline int EntityCount = 0;
inline std::string LevelName;
inline std::vector<PlayerData> EntList;
inline std::vector<SDK::Entity*> DeathboxList;
inline std::vector<std::string> StreamerList;
inline std::vector<std::string> SpectatorList;

inline Vector3 W2S(Vector3 Position) {
    BaseMatrix Matrix = static_cast < BaseMatrix >(sdk.mtrix);

    Vector3 out;
    float _x = Matrix.at[0] * Position.x + Matrix.at[1] * Position.y + Matrix.at[2] * Position.z + Matrix.at[3];
    float _y = Matrix.at[4] * Position.x + Matrix.at[5] * Position.y + Matrix.at[6] * Position.z + Matrix.at[7];
    out.z = Matrix.at[12] * Position.x + Matrix.at[13] * Position.y + Matrix.at[14] * Position.z + Matrix.at[15];

    if (out.z < 0.1f) return {
      0,
      0,
      0
    };

    _x *= 1.f / out.z;
    _y *= 1.f / out.z;

    out.x = sdk.DisplaySize.x * .5f;
    out.y = sdk.DisplaySize.y * .5f;

    out.x += 0.5f * _x * sdk.DisplaySize.x + 0.5f;
    out.y -= 0.5f * _y * sdk.DisplaySize.y + 0.5f;

    return out;
}
inline std::string getModelName(std::uint64_t address) {

    uintptr_t pMode_Name = Read < uintptr_t >(address + Offsets::C_BaseEntity::m_m_ModelName);
    if (!pMode_Name) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error uintptr_t pMode_Name = Read<uintptr_t>(this->getAddress() + Offsets::C_BaseEntity::m_m_ModelName) ? NULL "));
#endif
        return "";
    }
    return ReadString(pMode_Name);
}

inline Vector3 GetTargetPositionA(Vector3 targetPosition, Vector3 targetVelocity, float time) {
    return targetPosition.add(targetVelocity.mul(time));
}
inline bool OptimalAngle(const Vector3 start, const Vector3 end, const float speed, const float gravity, float& angle) {
    float horizontalDistance = calcDist(start,end);
    float heightDifference = end.z - start.z;

    float root = powf(speed, 4) - gravity * (gravity * powf(horizontalDistance, 2) + 2 * heightDifference * powf(speed, 2));
    if (root < 0.0)
        return false;

    float term1 = powf(speed, 2) - sqrt(root);
    float term2 = gravity * horizontalDistance;

    angle = atanf(term1 / term2);
    return true;
}
inline float GetTimeToTarget(Vector3 startPosition, Vector3 endPosition, float bulletSpeed) {
    float distance = (endPosition.sub(startPosition)).Magnitude();
    return distance / bulletSpeed; // * 1000
}
inline Vector3 GetTargetPosition(Vector3 startPosition, Vector3 endPosition, Vector3 targetVelocity, float bulletSpeed) {
    float time = GetTimeToTarget(startPosition, endPosition, bulletSpeed);
    return GetTargetPositionA(endPosition, targetVelocity, time);
}
inline bool CalcAnglePredictives(Vector3 start, Vector3 targetPosition, Vector3 targetVelocity, float bulletSpeed, float bulletScale, int steps, Vector2& result)
{
    const float gravity = 750.0f / bulletScale;

    float angle = 0;
    float time = 0.0;
    float timeStep = 1.0f / steps;

    for (int i = 0; i < steps; i++) {
        Vector3 predictedPosition = GetTargetPositionA(targetPosition, targetVelocity, time);
        if (!OptimalAngle(start, predictedPosition, bulletSpeed, gravity, angle))
            continue;

        Vector3 direction = predictedPosition.sub(start);
        float horizontalDistance = direction.Magnitude2D();
        float travelTime = horizontalDistance / (bulletSpeed * cosf(angle));
        if (travelTime <= time) {
            result.x = -angle * (180 / M_PI);
            result.y = atan2f(direction.y, direction.x) * (180 / M_PI); //180
            return true;
        }
        time += timeStep;
    }
    targetPosition = GetTargetPosition(start, targetPosition, targetVelocity, bulletSpeed);
    auto g1 = CalcAngle(start, targetPosition);
    result = { g1.x,g1.y };
    return true;
}
inline box_bounds get_bounds(PlayerData player, float expand = 0) {
    box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

    for (auto j : valid_bones) {
        Vector3 sc;
         sc = W2S(player.ClassAccess->GetBonePositionByHitBox(j));
        if (!sc.Empty()) {
            Vector3 bone_screen = sc;

            if (bone_screen.x < ret.left)
                ret.left = bone_screen.x;
            if (bone_screen.x > ret.right)
                ret.right = bone_screen.x;
            if (bone_screen.y < ret.top)
                ret.top = bone_screen.y;
            if (bone_screen.y > ret.bottom)
                ret.bottom = bone_screen.y;
            ret.onscreen = true;
        }

    }

    if (ret.left == FLT_MAX)
        return box_bounds::null();
    if (ret.right == FLT_MIN)
        return box_bounds::null();
    if (ret.top == FLT_MAX)
        return box_bounds::null();
    if (ret.bottom == FLT_MIN)
        return box_bounds::null();

    ret.left -= expand;
    ret.right += expand;
    ret.top -= expand;
    ret.bottom += expand;

    return ret;
};