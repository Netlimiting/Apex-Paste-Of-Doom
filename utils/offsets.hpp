#include <Windows.h>
#include <iostream>

#define Off constexpr uint64_t
#define StaticAddress(name,value) inline constexpr uint64_t m_##name = value


namespace Offsets {
    namespace Misc {
        // Existing constants
        StaticAddress(LocalPlayer, 0x26C70A8);
        StaticAddress(m_hViewModels, 0x2de0);
        StaticAddress(m_armsModelIndex, 0x497c);
        StaticAddress(GlobalVars, 0x1BB4180);
        StaticAddress(EntityList, 0x6B6BE08);
        StaticAddress(InputSystem, 0x1C63440);
        StaticAddress(NameList, 0x95A6E10);
        StaticAddress(m_customScriptInt, 0x15b4);
        StaticAddress(ClientState, 0x1BB44C0);
        StaticAddress(SignonState, 0x17eb37c);
        StaticAddress(LevelName, 0x1BB4694);
        StaticAddress(ViewRender, 0x336FE60);
        StaticAddress(ViewMatrix, 0x11a350);
        StaticAddress(Bones, 0xdd0);
        StaticAddress(PrimaryWeapon, 0x0d88 + 0x48);
        StaticAddress(lastVisibleTime, 0x19f0);
        StaticAddress(WorldTime, 0x2088);
        StaticAddress(LastKillTime, 0x35dc);
        StaticAddress(GameWorld, 0x17ec544);

        // New constants to be added
        StaticAddress(OFFSET_HIGHLIGHTSETTINGS, 0x72B53B0);
        StaticAddress(OFFSET_HIGHLIGHTSERVERACTIVESTATES, 0x298);
        StaticAddress(OFFSET_HIGHLIGHTCURRENTCONID, 0x29C);
        StaticAddress(OFFSET_HIGHLIGHTVISIBILITYTYPE, 0x26c);
        StaticAddress(HIGHLIGHT_TYPE_SIZE, 0x34);
        StaticAddress(OFFSET_GLOW_COLOR, 0x1d0 + 0x30);
        StaticAddress(OFFSET_GLOW_TYPE, 0x29c);
        StaticAddress(OFFSET_GLOW_FIX, 0x278);
        StaticAddress(GLOW_DISTANCE, 0x264);
        // No change

    }
    namespace C_BaseEntity {
        StaticAddress(m_ModelName, 0x0030);
        StaticAddress(m_fFlags, 0x00c8);
        StaticAddress(m_angAbsRotation, 0x0164);
        StaticAddress(m_vecAbsOrigin, 0x017c);
        StaticAddress(m_vecPrevAbsOrigin, 0x0004);
        StaticAddress(m_flGravity, 0x0300);
        StaticAddress(m_rgflCoordinateFrame, 0x07b0);

    }
    namespace DT_BaseEntity {
        StaticAddress(moveparent, 0x001c);
        StaticAddress(m_parentAttachment, 0x0020);
        StaticAddress(m_fEffects, 0x0040);
        StaticAddress(m_usableType, 0x0044);
        StaticAddress(m_cellX, 0x0048);
        StaticAddress(m_cellY, 0x004c);
        StaticAddress(m_cellZ, 0x0050);
        StaticAddress(m_localOrigin, 0x0054);
        StaticAddress(m_nModelIndex, 0x0060);
        StaticAddress(m_clrRender, 0x0080);
        StaticAddress(m_clIntensity, 0x0084);
        StaticAddress(m_bossPlayer, 0x0154);
        StaticAddress(m_shieldHealth, 0x01a0);
        StaticAddress(m_Shield_type, 0x46c4);
        StaticAddress(m_shieldHealthMax, 0x01a4);
        StaticAddress(m_wantsScopeHighlight, 0x02c4);
        StaticAddress(m_networkedFlags, 0x02d8);
        StaticAddress(m_ignoreParentRotation, 0x02d0);
        StaticAddress(m_visibilityFlags, 0x0330);
        StaticAddress(m_iTeamNum, 0x0338);
        StaticAddress(m_teamMemberIndex, 0x0340);
        StaticAddress(m_squadID, 0x0344);
        StaticAddress(m_grade, 0x0338);
        StaticAddress(m_ignorePredictedTriggerFlags, 0x033c);
        StaticAddress(m_passThroughFlags, 0x0344);
        StaticAddress(m_passThroughThickness, 0x0348);
        StaticAddress(m_passThroughDirection, 0x034c);
        StaticAddress(m_bIsSoundCodeControllerValueSet, 0x0374);
        StaticAddress(m_flSoundCodeControllerValue, 0x0378);
        StaticAddress(m_localAngles, 0x0388);
        StaticAddress(m_hOwnerEntity, 0x039c);
        StaticAddress(m_bRenderWithViewModels, 0x0390);
        StaticAddress(m_nRenderFX, 0x0391);
        StaticAddress(m_nRenderMode, 0x03b1);
        StaticAddress(m_Collision, 0x03b8);
        StaticAddress(m_CollisionGroup, 0x0438);
        StaticAddress(m_contents, 0x042c);
        StaticAddress(m_collideWithOwner, 0x0430);
        StaticAddress(m_iSignifierName, 0x0478);
        StaticAddress(m_iName, 0x0481);
        StaticAddress(m_scriptNameIndex, 0x0588);
        StaticAddress(m_instanceNameIndex, 0x058c);
        StaticAddress(m_holdUsePrompt, 0x0610);
        StaticAddress(m_pressUsePrompt, 0x0618);
        StaticAddress(m_phaseShiftFlags, 0x06b0);
        StaticAddress(m_baseTakeDamage, 0x06b4);
        StaticAddress(m_invulnerableToDamageCount, 0x06b8);
        StaticAddress(m_attachmentLerpStartTime, 0x071c);
        StaticAddress(m_attachmentLerpEndTime, 0x0720);
        StaticAddress(m_attachmentLerpStartOrigin, 0x0724);
        StaticAddress(m_attachmentLerpStartAngles, 0x0730);
        StaticAddress(m_parentAttachmentModel, 0x0750);
        StaticAddress(m_fadeDist, 0x075c);
        StaticAddress(m_dissolveEffectEntityHandle, 0x07f4);
        StaticAddress(m_usablePriority, 0x0818);
        StaticAddress(m_usableDistanceOverride, 0x081c);
        StaticAddress(m_usableFOV, 0x0820);
        StaticAddress(m_usePromptSize, 0x0824);
        StaticAddress(m_spottedByTeams, 0x0828);
        StaticAddress(m_firstChildEntityLink, 0x0910);
        StaticAddress(m_firstParentEntityLink, 0x0914);
        StaticAddress(m_realmsBitMask, 0x0918);

    }
    namespace DT_Player
    {
        Off m_vecAbsOrigin = 0x0004;
        Off isLocalOriginLocal = 0x0010;
        Off m_fFlags = 0x00c8;
        Off m_hGroundEntity = 0x0324;
        Off m_iHealth = 0x0328;
        Off m_flMaxspeed = 0x032c;
        Off m_jumpPadDebounceExpireTime = 0x0350;
        Off m_iMaxHealth = 0x0470;
        Off m_lifeState = 0x0690;
        Off m_overlayEventParity = 0x16c1;
        Off m_inventory = 0x1928;
        Off m_selectedOffhands = 0x19a6;
        Off m_selectedOffhandsPendingHybridAction = 0x19a9;
        Off m_titanSoul = 0x1a24;
        Off m_bZooming = 0x1c41;
        Off m_zoomToggleOnStartTime = 0x1c44;
        Off m_zoomBaseFrac = 0x1c48;
        Off m_zoomBaseTime = 0x1c4c;
        Off m_zoomFullStartTime = 0x1c50;
        Off m_currentFramePlayer = 0x20e8;
        Off pl = 0x2510;
        Off m_ammoPoolCapacity = 0x2594;
        Off m_hasBadReputation = 0x2598;
        Off m_hardware = 0x25a0;
        Off m_unspoofedHardware = 0x2541;
        Off m_platformUserId = 0x25a8;
        Off m_progressionUserId = 0x2550;
        Off m_unSpoofedPlatformUserId = 0x25b8;
        Off m_EadpUserId = 0x2560;
        Off m_crossPlayChat = 0x25c0;
        Off m_crossPlayChatFriends = 0x25c1;
        Off m_crossProgressionMigrated = 0x25c2;
        Off m_laserSightColorCustomized = 0x25c3;
        Off m_laserSightColor = 0x25c4;
        Off m_classModsActive = 0x25d0;
        Off m_passives = 0x2788;
        Off m_bleedoutState = 0x27b8;
        Off m_bleedoutStartTime = 0x27bc;
        Off m_statusEffectsTimedPlayerNV = 0x27c0;
        Off m_statusEffectsEndlessPlayerNV = 0x28b0;
        Off m_damageComboLatestUpdateTime = 0x2974;
        Off m_damageComboStartHealth = 0x2978;
        Off m_gestureSequences = 0x297c;
        Off m_gestureStartTimes = 0x298c;
        Off m_gestureBlendInDuration = 0x29ac;
        Off m_gestureBlendOutDuration = 0x29cc;
        Off m_gestureFadeOutStartTime = 0x29ec;
        Off m_gestureFadeOutDuration = 0x2a0c;
        Off m_gestureAutoKillBitfield = 0x2a2c;
        Off m_autoSprintForced = 0x2a70;
        Off m_fIsSprinting = 0x2a74;
        Off m_playerSettingForStickySprintForward = 0x2a76;
        Off m_playerSettingForHoldToSprint = 0x2a77;
        Off m_lastSprintPressTime = 0x2a78;
        Off m_stickySprintForwardEnableTime = 0x2a7c;
        Off m_stickySprintForwardDisableTime = 0x2a80;
        Off m_damageImpulseNoDecelEndTime = 0x2a98;
        Off m_playerVehicles = 0x2aa4;
        Off m_playerVehicleCount = 0x2aac;
        Off m_playerVehicleDriven = 0x2ab0;
        Off m_playerVehicleUseTime = 0x2ab4;
        Off m_duckState = 0x2ab8;
        Off m_leanState = 0x2abc;
        Off m_canStand = 0x2ac1;
        Off m_StandHullMin = 0x2ac4;
        Off m_StandHullMax = 0x2ad0;
        Off m_DuckHullMin = 0x2adc;
        Off m_DuckHullMax = 0x2ae8;
        Off m_entitySyncingWithMe = 0x2af4;
        Off m_upDir = 0x2af8;
        Off m_traversalState = 0x2b7c;
        Off m_traversalType = 0x2b80;
        Off m_traversalForwardDir = 0x2bac;
        Off m_traversalRefPos = 0x2bb8;
        Off m_traversalYawDelta = 0x2be4;
        Off m_traversalYawPoseParameter = 0x2be8;
        Off m_wallClimbSetUp = 0x2c00;
        Off m_wallHanging = 0x2c01;
        Off m_grapple = 0x2d08;
        Off m_grappleActive = 0x2d90;
        Off m_turret = 0x2ddc;
        Off m_hViewModels = 0x2de0;
        Off m_viewOffEntity = 0x2df0;
        Off m_animViewEntity = 0x2e30;
        Off m_activeZipline = 0x2f20;
        Off m_ziplineValid3pWeaponLayerAnim = 0x2f2c;
        Off m_ziplineState = 0x2f30;
        Off m_ziplineGrenadeBeginStationEntity = 0x2fcc;
        Off m_ziplineGrenadeBeginStationAttachmentId = 0x2fd0;
        Off m_shadowShieldActive = 0x2ff8;
        Off m_tempShieldHealth = 0x2ffc;
        Off m_extraShieldHealth = 0x3000;
        Off m_extraShieldTier = 0x3004;
        Off m_isPerformingBoostAction = 0x303c;
        Off m_lastJumpPadTouched = 0x3198;
        Off m_launchCount = 0x31a0;
        Off m_launcherAirControlActive = 0x31a4;
        Off m_melee = 0x32d0;
        Off m_useCredit = 0x3308;
        Off m_playerFlags = 0x3318;
        Off m_hasMic = 0x3320;
        Off m_inPartyChat = 0x3321;
        Off m_communicationsAutoBlocked = 0x3322;
        Off m_playerMoveSpeedScale = 0x3324;
        Off m_bShouldDrawPlayerWhileUsingViewEntity = 0x3570;
        Off m_iSpawnParity = 0x35dc;
        Off m_flDeathTime = 0x36c8;
        Off m_ragdollCreationOrigin = 0x36cc;
        Off m_ragdollCreationYaw = 0x36d8;
        Off m_lastDodgeTime = 0x3718;
        Off m_timeJetpackHeightActivateCheckPassed = 0x3740;
        Off m_grappleHook = 0x37e0;
        Off m_petTitan = 0x37e4;
        Off m_xp = 0x380c;
        Off m_skill_mu = 0x3814;
        Off m_bHasMatchAdminRole = 0x3818;
        Off m_ubEFNoInterpParity = 0x4168;
        Off m_hColorCorrectionCtrl = 0x416c;
        Off m_title = 0x4190;
        Off m_Shared = 0x4500;
        Off m_pilotClassIndex = 0x4554;
        Off m_playerScriptNetDataGlobal = 0x47e0;
        Off m_helmetType = 0x47e8;
        Off m_armorType = 0x47ec;
        Off m_controllerModeActive = 0x47f4;
        Off m_skydiveForwardPoseValueTarget = 0x4818;
        Off m_skydiveSidePoseValueTarget = 0x4824;
        Off m_skydiveState = 0x484c;
        Off m_skydiveDiveAngle = 0x4864;
        Off m_skydiveIsDiving = 0x4868;
        Off m_skydiveSpeed = 0x486c;
        Off m_skydiveStrafeAngle = 0x4870;
        Off m_skydivePlayerPitch = 0x4884;
        Off m_skydivePlayerYaw = 0x4888;
        Off m_skydiveFromSkywardLaunch = 0x48c5;
        Off m_skydiveScriptInputOverride = 0x48c8;
        Off m_skydiveContraintPostion = 0x48cc;
        Off m_skydiveContraintRadius = 0x48d8;
        Off m_skywardLaunchState = 0x48dc;
        Off m_skywardLaunchSlowStartTime = 0x48f0;
        Off m_skywardLaunchSlowEndTime = 0x48f4;
        Off m_skywardLaunchFastEndTime = 0x48f8;
        Off m_skywardLaunchEndTime = 0x4900;
        Off m_skywardLaunchSlowSpeed = 0x4908;
        Off m_skywardLaunchFastSpeed = 0x490c;
        Off m_skywardOff = 0x4910;
        Off m_skywardLaunchInterrupted = 0x4920;
        Off m_skywardLaunchFollowing = 0x4921;
        Off m_skywardObstacleAvoidanceEndPos = 0x4924;
        Off m_armoredLeapAirPos = 0x4934;
        Off m_armoredLeapEndPos = 0x4940;
        Off m_armoredLeapType = 0x494c;
        Off m_armoredLeapPhase = 0x4950;
        Off m_armoredLeapStartTime = 0x4954;
        Off m_dragReviveState = 0x49c0;
        Off m_dragReviveOutroStartTime = 0x49c4;
        Off m_reviveTarget = 0x49c8;
    }
    namespace CollisionProperty {
        Off m_vecMins = 0x0010;
        Off m_vecMaxs = 0x001c;
        Off m_usSolidFlags = 0x0028;
        Off m_nSolidType = 0x002c;
        Off m_triggerBloat = 0x002d;
        Off m_collisionDetailLevel = 0x002e;
        Off m_nSurroundType = 0x003c;
        Off m_vecSpecifiedSurroundingMins = 0x0048;
        Off m_vecSpecifiedSurroundingMaxs = 0x0054;
    }
    namespace DT_Player_ViewOffEntityData
    {
        Off viewOffEntityHandle = 0x0008;
        Off lerpInDuration = 0x000c;
        Off lerpOutDuration = 0x0010;
        Off stabilizePlayerEyeAngles = 0x0014;
    }
    namespace DT_Player_AnimViewEntityData
    {
        Off animViewEntityAngleLerpInDuration = 0x0004;
        Off animViewEntityOriginLerpInDuration = 0x0008;
        Off animViewEntityLerpOutDuration = 0x000c;
        Off animViewEntityStabilizePlayerEyeAngles = 0x0010;
        Off animViewEntityThirdPersonCameraParity = 0x0014;
        Off animViewEntityThirdPersonCameraAttachment = 0x0018;
        Off animViewEntityNumThirdPersonCameraAttachments = 0x0020;
        Off animViewEntityThirdPersonCameraVisibilityChecks = 0x0024;
        Off animViewEntityDrawPlayer = 0x0025;
        Off fovTarget = 0x0028;
        Off fovSmoothTime = 0x002c;
        Off animViewEntityParity = 0x0038;
    }
    namespace DT_WeaponInventory
    {
        Off weapons = 0x0008;
        Off offhandWeapons = 0x0038;
        Off activeWeapons = 0x0064;
    }
    namespace DT_Player_LocalData
    {
        Off bcc_localdata = 0x0000;
        Off m_weaponGettingSwitchedOut = 0x0008;
        Off m_showActiveWeapon3p = 0x0010;
        Off m_vecViewOff_x = 0x0034;
        Off m_vecViewOff_y = 0x0038;
        Off m_vecViewOff_z = 0x003c;
        Off m_cloakEndTime = 0x01cc;
        Off m_cloakFadeInEndTime = 0x01d0;
        Off m_cloakFadeOutStartTime = 0x01d4;
        Off m_cloakFadeInDuration = 0x01d8;
        Off m_cloakFlickerAmount = 0x01dc;
        Off m_cloakFlickerEndTime = 0x01e0;
        Off m_networkedFlags = 0x02d8;
        Off m_deathVelocity = 0x0360;
        Off m_minimapData = 0x0838;
        Off m_nameVisibilityFlags = 0x0888;
        Off m_bIsPlayerOverheating = 0x18f0;
        Off m_playerOverheatValue = 0x18f4;
        Off m_timeLastGeneratedPlayerOverheat = 0x18f8;
        Off m_lastFiredTime = 0x1900;
        Off m_lastFiredWeapon = 0x1904;
        Off m_raiseFromMeleeEndTime = 0x1908;
        Off m_sharedEnergyCount = 0x190c;
        Off m_sharedEnergyTotal = 0x1910;
        Off m_sharedEnergyLockoutThreshold = 0x1914;
        Off m_lastSharedEnergyRegenTime = 0x1918;
        Off m_sharedEnergyRegenRate = 0x191c;
        Off m_sharedEnergyRegenDelay = 0x1920;
        Off m_lastSharedEnergyTakeTime = 0x1924;
        Off m_selectedWeapons = 0x1990;
        Off m_latestPrimaryWeapons = 0x1994;
        Off m_latestPrimaryWeaponsIndexZeroOrOne = 0x199c;
        Off m_latestNonOffhandWeapons = 0x19a4;
        Off m_lastCycleSlot = 0x19ac;
        Off m_weaponPermission = 0x19b4;
        Off m_weaponDelayEnableTime = 0x19b8;
        Off m_weaponDisabledInScript = 0x19bc;
        Off m_weaponDisabledFlags = 0x19d2;
        Off m_weaponInventorySlotLockedFlags = 0x19d4;
        Off m_weaponTypeDisabledFlags = 0x19d8;
        Off m_weaponTypeDisabledRefCount = 0x19dc;
        Off m_allowHudSelectionWhileWeaponsDisabled = 0x19e6;
        Off m_weaponAmmoRegenDisabled = 0x19e7;
        Off m_weaponAmmoRegenDisabledRefCount = 0x19e8;
        Off m_akimboState = 0x19ec;
        Off m_akimboShouldAltFire = 0x19ed;
        Off m_hudInfo_visibilityTestAlwaysPasses = 0x19ee;
        Off m_contextAction = 0x1a00;
        Off m_phaseShiftType = 0x1a2c;
        Off m_phaseShiftTimeStart = 0x1a30;
        Off m_phaseShiftTimeEnd = 0x1a34;
        Off m_targetInfoPingValue = 0x1bd0;
    }
    namespace DT_PointCamera
    {
        Off m_FOV = 0x09b0;
        Off m_bFogEnable = 0x09f0;
        Off m_bActive = 0x09f1;
    }
}