#pragma once
#include <stddef.h>
#include "Character.h"
#include "NiTMap.h"
#include "Utils/Scanner.h"

struct AttributeSkillCounts;

class TESWorldSpace;
class TESGameSoundHandle;
class NiPointLight;
class DialoguePackage;
class CameraCaster;
class HitCaster;
class bhkMouseSpringAction;
class TESQuest;
class TESQuestStageItem;
class TESQuestTarget;
class TESClass;
class AlchemyItem;
class TESRegion;
class TESRegionSound;
class MAP_MARKER_STRUCT;
class NiCamera;
class MagicShaderHitEffect;

class PlayerCharacter : public Character {
public:
	enum GrabbingType : __int32 {
		GRAB_NONE = 0x0,
		GRAB_NORMAL = 0x1,
		GRAB_INVENTORY_DROP = 0x2,
		GRAB_TELEKINESIS = 0x3,
	};

	struct PlayerDeathInfos {
		uint8_t DeathReason[4];
		unsigned int KillerFormID;
		unsigned int KillerEntityID;
		unsigned __int16 KillerLevel;
	};

	bool                                 bHasGrabbedObject;
	bool                                 bAiContinuePickup;
	int                                  iCombatPersue;
	bool                                 bTravelUseDoor;
	bool                                 bOnElevator;
	bool                                 bInSEWorld;
	bool                                 bForceQuestTargetUpdate;
	DialoguePackage*                     pClosesConversation;
	int                                  ibuypercent;
	int                                  isellpercent;
	bool                                 binBarter;
	Actor*                               pBarterContainer;
	bool                                 btransporting;
	float                                fGrantedPlayerXP;
	float                                fSkillUsage[21];
	int                                  iSkillAdvanceCount;
	int                                  fSkillLevels[21];
	bool                                 bReadyToLevelUp;
	Creature*                            pLastRiddenHorse;
	PlayerDeathInfos                     PlayerDeathInfos;
	BSSimpleList<ActiveEffect*>*         pActiveEffectList;
	MagicItem*                           pCurrentSpell;
	MagicTarget*                         pDesiredTarget;
	CameraCaster*                        pCameraCaster;
	HitCaster*                           pHitCaster;
	BSSimpleList<MagicItem*>*            EatDrinkItems;
	BSSimpleList<TESBoundObject*>*       QueuedWornEnchantments;
	bool                                 bShowQuestItemsInInventory;
	float                                MagicActorValueModifiers[72];
	float                                ScriptActorValueModifiers[72];
	float                                fHealthModifier;
	float                                fMagickaModifier;
	float                                fFatigueModifier;
	float                                GameActorValueModifiers[72];
	TESObjectREFR*                       pLastDoorActivated;
	NiPointer<bhkMouseSpringAction>      spGrabSpring;
	TESObjectREFR*                       pGrabbedObject;
	GrabbingType                         eGrabType;
	float                                fGrabObjectWeight;
	float                                fGrabDistance;
	bool                                 b3rdPerson;
	bool                                 bTemp3rdPerson;
	bool                                 bTemp3rdPersonSwitchBack;
	bool                                 bAlwaysRun;
	bool                                 bAutoMove;
	int                                  iSleepTime;
	bool                                 bIsSleeping;
	float                                fFOV;
	float                                fsecondRunning;
	float                                fsecondSwimming;
	float                                fsecondSneaking;
	bool                                 bActorinSneakRange;
	bool                                 bCanFastTravel;
	BSSimpleList<TESObjectREFR*>*        pPlayerCombatList;
	float*                               pchargenskilluses;
	BSSimpleList<AttributeSkillCounts*>* pAttributeSkillCounts;
	char                                 iSpecializationCount[3];
	int                                  iNumberTraining;
	bool                                 bControlsDisabled;
	TESObjectREFR*                       pForceActivateRef;
	BipedAnim*                           p1stPersonBipedAnim;
	Animation*                           p1stPersonAnimation;
	NiPointer<NiAVObject>                sp1stPerson3D;
	float                                fEyeHeight;
	NiPointer<NiNode>                    spInventoryPC;
	Animation*                           pInventoryAnimation;
	MagicShaderHitEffect*                pInventoryWeaponEffect;
	BSSimpleList<TESTopic*>              listTopics;
	BSSimpleList<TESQuestStageItem*>     listQuestLog;
	TESQuest*                            pActiveQuest;
	BSSimpleList<TESQuestTarget*>        listQuestTargets;
	bool                                 bGreetingPlayer;
	float                                fGreetTimer;
	int                                  idaysinprison;
	int                                  ihourstosleep;
	bool                                 bEscapedfromJail;
	char                                 cMurder;
	int                                  iAmountStolenSold;
	float                                fSortActorDistanceTimer;
	float                                fSitHeadingDelta;
	bool                                 bBeenAttacked;
	MagicItem*                           pSelectedSpell;
	TESObjectBOOK*                       pSelectedScroll;
	NiPoint3                             vPlayerMapMarkerLoc;
	TESForm*                             pPlayerMapMarkerSpace;
	TESObjectREFR*                       pPlayerMapMarkerDoor;
	float                                fBowTimer;
	BirthSign*                           pBirthSign;
	int                                  iNumAdvance;
	uint8_t                              eskilladvance[4];
	TESClass*                            pDefaultClass;
	TESClass*                            pClassBasedOn;
	unsigned int                         pMiscStats[28];
	unsigned int                         pCrimeCounts[6];
	AlchemyItem*                         pPendingPoison;
	bool                                 bVampireFed;
	bool                                 bChargen;
	bool                                 bTelekinesisSelected;
	TESRegion*                           pOccupiedRegion;
	BSSimpleList<TESRegionSound*>        CurrentRegionSoundList;
	int                                  iPCFame;
	int                                  iPCInfamy;
	int                                  iCrimeGoldAcum;
	float                                fCrimeGoldSE;
	BSSimpleList<TESObjectREFR*>         JailMarkerList;
	void*                                pInitialStateBuffer;
	unsigned int                         iLastPlayingTimeUpdate;
	unsigned int                         iTotalPlayingTime;
	unsigned int                         iCharacterSeed;
	bool                                 bAiControlledToPos;
	bool                                 bAiControlledFromPos;
	bool                                 bInBorderContainedCell;
	bool                                 bReturnToLastKnownGoodPosition;
	NiPoint3                             LastKnownGoodPosition;
	TESForm*                             pLastKnownGoodLocation;
	NiTArray<TESRegion*>*                pBorderRegions;
	float                                fDifficultyLevel;
	bool                                 bBeingChased;
	BSSimpleList<MAP_MARKER_STRUCT*>     MapMarkerList;
	TESWorldSpace*                       pMapWorld;
	bool                                 bUFOMode;
	float                                fUFOCameraHeading;
	float                                fUFOCameraPitch;
	NiPoint3                             UFOCameraPos;
	unsigned int                         iSelectedSpellCastSoundID;
	TESGameSoundHandle*                  pSelectedSpellCastSound;
	TESGameSoundHandle*                  pMagicFailureSounds[6];
	BSSimpleList<TESObjectREFR*>         DroppedRefList;
	NiTMap<unsigned int, unsigned char>  RandomDoorSpaceMap;
	NiPointer<NiPointLight>              sp1stPersonLight;
	NiPointer<NiPointLight>              sp3rdPersonLight;
	int                                  iNumberActorsInCombat;
	float                                fSkillAdvancementUses[21];
	bool                                 bLoadingFromMainMenu;
	bool                                 bInsufficientChargeMessageShown;
	float                                fDropAngleMod;
	float                                fLastDropAngleMod;
	float                                fplayerDeathReloadTime;
	bool                                 bShouldRefreshClairvoyance;
	NiPointer<NiCamera>                  chaseCameraPtr;

	static inline PlayerCharacter** singleton = nullptr;
	static PlayerCharacter* GetSingleton() {
		if (singleton) {
			return *singleton;
		}

		return nullptr;
	}

	static void InitSignatures() {
		const Pattern gPlayerCharacterSig = {"48 8B 0D ? ? ? ? F3 0F 10 89", 3, 4};

		Scanner::Add(gPlayerCharacterSig, &singleton);
	}
};

ASSERT_SIZE(PlayerCharacter, 0xB70);