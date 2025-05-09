#pragma once
#include "FurnitureMark.h"
#include "MiddleLowProcess.h"

class MiddleHighProcess : public MiddleLowProcess {
public:
	virtual		 ~MiddleHighProcess();
	virtual void SetAnimationActiveFlag(bool);
	virtual void ResetTarget();
	virtual void ProcessBuyObject(Actor*);
	virtual void ProcessSteal(Actor*);
	virtual void ProcessPickPocket(Actor*);
	virtual void ProcessDialogue(Actor*);
	virtual void ProcessRemoveWorn(Actor*, bool, bool);
	virtual void ProcessTravel(Actor*, bool, bool, int);
	virtual void ProcessAccompanyOneHour(Actor*);
	virtual void FreeUpSpecialIdle(Actor*);

	BSSimpleList<TESObjectREFR*>          DeadDetectList;
	BSSimpleList<TESObjectREFR*>          RefListChairBed;
	float                                 fPursueTimer;
	float                                 fTorchEvalTimer;
	TESPackage*                           pRunOncePackage;
	float                                 fEquippedWeight;
	bool                                  bDoneOnce;
	TESPackage*                           LastUpdatePackage;
	PROCEDURE                             LastUpdateProcedure;
	bool                                  bFirstUpdateForProcedure;
	bool                                  bLowPathDirty;
	bool                                  bAltarAIExecutingProcedure;
	int                                   iRunOnceProcedureIndex;
	bool                                  bCompleteMovement;
	NiPoint3                              lastSeenPostion;
	PACKAGE_OBJECT_TYPE                   eUseItem;
	ItemChange*                           pWeapon;
	ItemChange*                           pTorch;
	ItemChange*                           pAmmo;
	ItemChange*                           pShield;
	bool                                  bWeaponBow;
	bool                                  bWeaponStaff;
	float                                 fWeaponValue;
	NiNode*                               pWeaponBone;
	NiNode*                               pTorchBone;
	NiNode*                               pShieldBone;
	NiNode*                               pSheathedWeaponBone;
	NiNode*                               pQuiverBone;
	NiNode*                               pArrowBone;
	bool                                  bWantWeaponDrawn;
	bool                                  bWeaponDrawn;
	NiPointer<bhkCharacterController>     spCharController;
	char                                  cKnockState;
	unsigned __int8                       cSitSleepState;
	TESObjectREFR*                        pCurrentFurniture;
	unsigned __int8                       cCurrentFurnitureIndex;
	FurnitureMark                         FurnitureMarker;
	__int16                               iSoul;
	Actor*                                pCommandingActor;
	TESObjectWEAP*                        pLastBoundWeapon;
	MagicItem*                            pCurrentSpell;
	MagicItem*                            pCurrentPackageSpell;
	bool                                  bCheckMagicNode;
	TESEffectShader*                      pCurrentWeaponEffect;
	float                                 fAlphaMult;
	float                                 fScriptRefractPower;
	BSFaceGenAnimationData*               m_pFaceAnimationData;
	bool                                  bRefreshMagicShaderEffects;
	bool                                  bRefreshFlareFlags;
	unsigned int                          uiFlareFlags;
	bool                                  bPickPocketed;
	bool                                  bDoneClothesChange;
	bool                                  bDetectLifeDetected;
	bool                                  bSummonedCreature;
	bool                                  bUpdate3dModel;
	bool                                  bForceNextUpdate;
	BSSimpleList<ArrowProjectile*>*       pAttachedArrowList;
	BSSimpleList<ActiveEffect*>*          pActiveEffectList;
	MagicTarget*                          pDesiredTarget;
	Animation*                            pAnimation;
	bool                                  bBeenAttacked;
	NiPointer<BSShaderPPLightingProperty> pLightingProperty;
	BSBound*                              pBSBound;
	float                                 fCurrentLightingValue;
	float                                 fCurrentLightingValueWithTorch;
};

ASSERT_SIZE(MiddleHighProcess, 0x2B8);