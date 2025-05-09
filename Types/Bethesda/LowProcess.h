#pragma once
#include "BaseProcess.h"
#include "ModifierList.h"

class LowProcess : public BaseProcess {
public:
	virtual      ~LowProcess();
	virtual void ProcessEscort(Actor*);
	virtual void ProcessSleep(Actor*);
	virtual void ProcessEat(Actor*);
	virtual void ProcessCombat(Actor*);
	virtual void ProcessAlarm(Actor*);
	virtual bool ProcessActivate(Actor*, bool);
	virtual void ProcessAccompany(Actor*);
	virtual void ProcessAquire(Actor*);
	virtual void ProcessVampireFeed(Actor*);
	virtual void ProcessAmbushWait(Actor*);
	virtual bool ProcessUseItemAt(Actor*);
	virtual void ProcessChooseSpell(Actor*);
	virtual void ProcessFleeNonCombat(Actor*);
	virtual void ProcessMovementBlockedWait(Actor*);
	virtual void ProcessSummonCreatureDefend(Actor*);
	virtual void ProcessClearMountPosition(Actor*);
	virtual void ProcessAim(Actor*);
	virtual void ProcessCast(Actor*);
	virtual void ProcessNotify(Actor*);
	virtual bool CheckIfHasObject(Actor*, int);
	virtual void SetTargetForPackage(Actor*);
	virtual void SetLocationForPackage(Actor*);
	virtual bool MountTheHorse(Actor*);
	virtual bool DismountTheHorse(Actor*);
	virtual void EvaluateOrderAquireList(Actor*);

	float                          fHourLastProcessed;
	unsigned int                   iDateLastProcessed;
	bool                           bActivatedPackTarget;
	bool                           bCompleteAction;
	bool                           bCombatAggresson;
	float                          fHourLastPreloadChecked;
	unsigned int                   iDelayedPreloadFrame;
	bool                           bAlert;
	bool                           bFollower;
	TESBoundObject*                pItemBeingUsed;
	float                          fFadeDelayTimer;
	TESObjectREFR*                 pTarget;
	TESObjectREFR*                 pGenericLocation;
	PathLow*                       pPathSystem;
	int                            iNumberItemsActivate;
	BSSimpleList<ObjectstoAquire*> ObjectList;
	ObjectstoAquire*               pAquireObject;
	ObjectstoAquire*               pSavedAquireObject;
	BSSimpleList<TESObjectREFR*>   GenericLocationsList;
	BSSimpleList<ObjectstoAquire*> TempObjectList;
	BSSimpleList<TESObjectREFR*>   TempLocList;
	TESBoundObject*                pObjecttoAquire;
	TESBoundObject*                pObjectForLocation;
	PACKAGE_OBJECT_TYPE            eFormType;
	ModifierList                   pGameModifiers;
	bool                           bLockedLocation;
	float                          fEssentialDownTimer;
	float                          fDeathTime;
};
