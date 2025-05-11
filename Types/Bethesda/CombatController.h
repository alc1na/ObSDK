#pragma once
#include "BSSimpleList.h"
#include "MagicItem.h"
#include "TESPackage.h"
#include "NiPoint3.h"

struct CombatTarget;
struct CombatMagicItem;

class TESGameSoundHandle;
class TESObjectWEAP;
class TESIdleForm;

struct CombatTimer {
	float fStartTime;
	float fTargetTime;
	float fMinimumTime;
};

struct CombatMovementRestrictions {
	bool             bInitialized;
	bool             bReset;
	unsigned __int16 sRestrictedMoves;
	bool             bHasMoveLeftAnim;
	bool             bHasMoveRightAnim;
	bool             bHasMoveForwardAnim;
	bool             bHasMoveBackwardAnim;
	NiPoint3         Location;
};

struct CombatTarget{
	Actor* pTargetActor;
	int    iPriority;
	bool   bHighPriority;
	float  fDamageDone;
	float  fDamagetaken;
};


class CombatController : TESPackage {
public:
	enum CombatState {};
	enum Strategy {};

	virtual Strategy Update(float);

	bool                                              bHasAltarSyncedManeuver;
	Actor*                                            pAttacker;
	BSSimpleList<CombatTarget*>*                      pTargetList;
	float                                             fTimer;
	bool                                              bHasAcquired;
	bool                                              bBlocking;
	bool                                              bYielding;
	bool                                              bHasEngagedPlayer;
	bool                                              bHasHandledPlayerYield;
	bool                                              bForceCombat;
	char                                              cYieldHitCount;
	char                                              cFleeHitCount;
	ANIM_GROUP_ENUM                                   eCurrentAttack;
	float                                             fLastDistance;
	bool                                              bTimeUnchangingDistance;
	bool                                              bFirstUpdate;
	BSSimpleList<CombatMagicItem*>*                   pRangeMagicItems;
	BSSimpleList<CombatMagicItem*>*                   pMeleeMagicItems;
	BSSimpleList<CombatMagicItem*>*                   pRestoreMagicItems;
	BSSimpleList<CombatMagicItem*>*                   pBackupBuffItems;
	uint8_t                                           eManeuverState[4];
	uint8_t                                           eCurrentStrategy[4];
	CombatState                                       eCombatState;
	CombatState                                       eLastCombatState;
	CombatMagicItem*                                  pMeleeMagic;
	CombatMagicItem*                                  pRangedMagic;
	CombatMagicItem*                                  pRestoreMagic;
	CombatMagicItem*                                  pCounterEffectMagic;
	CombatMagicItem*                                  pBuffMagic;
	CombatMagicItem*                                  pChosenBuffMagic;
	CombatMagicItem*                                  pChosenBoundArmorMagic;
	CombatMagicItem*                                  pChosenBoundWeaponMagic;
	CombatMagicItem*                                  pChosenSummoningMagic;
	CombatMagicItem*                                  pDiseaseMagic;
	BSSimpleList<MagicItem*>*                         pPoisons;
	TESObjectWEAP*                                    pSummonableWeapon;
	TESObjectWEAP*                                    pSwitchWeapon;
	float                                             fPowerAttackRanges[5];
	bool                                              bHasForwardAttacks;
	bool                                              AvailablePowerAttacks[5];
	TESIdleForm*                                      pYieldIdle;
	float                                             fCombatPosition;
	int                                               iAdvanceMoveMode;
	CombatTimer                                       ManeuverTimer;
	CombatTimer                                       MeleeTimer;
	CombatTimer                                       AdvanceTimer;
	CombatTimer                                       CloseTimer;
	CombatTimer                                       MagicTimer;
	float                                             fTurnCycleDuration;
	bool                                              bHasSwitched;
	bool                                              bCanBeOnStation;
	bool                                              bTargetUnreachable;
	BSSimpleList<NiPoint3*>*                          pOnStationCoordinates;
	NiPoint3*                                         pRepositionCoordinate;
	NiPoint3                                          MoveAwayPostion;
	Actor*                                            pTakeCoverTarget;
	bool                                              bNoMeleeWeapon;
	bool                                              bNoRangedWeapon;
	CombatTimer                                       MonitorBuffsTimer;
	CombatTimer                                       LineOfSightTimer;
	CombatTimer                                       CollectAlliesTimer;
	bool                                              bTargetLineOfSight;
	bool                                              bAlliesBlockTarget;
	bool                                              bRangedAllyWantsToShoot;
	bool                                              bProjectileBlocked;
	BSSimpleList<Actor*>                              CurrentAllies;
	CombatTimer                                       InTheWayTimer;
	float                                             fStandoffDistance;
	bool                                              bCanReachTarget;
	int                                               iCurrentAllyCount;
	bool                                              bUseNoAreaSpells;
	bool                                              bTurning;
	bool                                              bShootNow;
	bool                                              bFirstReposition;
	ACTOR_SEGMENT_INVIEW                              eTargetSegmentInView;
	float                                             fFacingTargetDistance;
	float                                             fCurrentAttackReach;
	NiTPointerMap<unsigned int, TESGameSoundHandle*>* pMagicSounds;
	CombatMovementRestrictions                        MovementRestrictions;
	bool                                              bBeingDeleted;
	int                                               iLastDetectionLevel;
	char                                              cUpdateFrame;
	bool                                              bUnableToBuffStandoff;
	bool                                              bLastSpellRestore;
	CombatTimer                                       StaffTimer;
	bool                                              bHasHandToHandEquip;
	bool                                              bInitializing;
	bool                                              bIsTargetMovingAway;

	static inline CombatTarget* (__fastcall* pGetCombatTarget)(CombatController*, Actor*);
	CombatTarget* __fastcall GetCombatTarget(Actor* apActor) {
		return pGetCombatTarget(this, apActor);
	}

	static void InitSignatures() {
		const Pattern pattern_CC_GetCombatTarget = "48 8B 41 ? 48 85 C0 74 ? 48 8B 48 ? 48 85 C9 75";

		Scanner::Add(pattern_CC_GetCombatTarget, &pGetCombatTarget);
	}
};

ASSERT_SIZE(CombatController, 0x270);