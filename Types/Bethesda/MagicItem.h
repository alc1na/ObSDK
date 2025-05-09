#pragma once
#include "EffectItemList.h"
#include "MagicSystem.h"
#include "MiscEnums.h"
#include "TESFullName.h"

class BaseFormComponent;
class TESFile;
class EffectItem;

class MagicItem : TESFullName, EffectItemList {
public:
	enum CannotCastReason : __int32 {
		NOCAST_OK                       = 0x0,
		NOCAST_MAGICKA                  = 0x1,
		NOCAST_SILENCED                 = 0x2,
		NOCAST_SKILLCHECK               = 0x3,
		NOCAST_POWERUSED                = 0x4,
		NOCAST_MULTIPLEBOUNDEFFECTS     = 0x5,
		NOCAST_RANGEDUNDERWATER         = 0x6,
		NOCAST_CLAIRVOYANCEWITHOUTQUEST = 0x7,
	};

	virtual bool                   IsAutoCalc();
	virtual void                   SetAutoCalc(bool);
	virtual MagicSystem::SpellType GetSpellType();
	virtual bool                   IgnoreResistance();
	virtual bool                   GetNoAbsorbOrReflect();
	virtual CHUNK_ID               GetChunkID();
	virtual void*                  GetData();
	virtual unsigned __int64       GetDataSize();
	virtual bool                   CompareMagicItemData(MagicItem*);
	virtual void                   CopyMagicItemData(MagicItem*);
	virtual void                   SaveMagicItemComponents();
	virtual void                   LoadMagicItemChunk(TESFile*, CHUNK_ID);

	std::list<EffectItem*>* pVisibleEffectsInAltar;
	EffectItem*             pMainTargetEffectInAltar;
	EffectItem*             pMainSelfEffectInAltar;
	EffectItem*             pSecondEffectInAltar;
	bool                    bHasChosenVisibleEffects;
	bool                    bHasAlreadyPlayedHitEffectsInAltar;
};

ASSERT_SIZE(MagicItem, 0x60);