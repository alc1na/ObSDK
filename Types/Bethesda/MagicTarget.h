#pragma once
#include "BSSimpleList.h"

class MagicTarget {
public:
	virtual bool                         AddTarget(MagicCaster*, MagicItem*, ActiveEffect*, bool);
	virtual TESObjectREFR*               GetTargetStatsObject();
	virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList();
	virtual bool                         MagicTargetIsActor();
	virtual void                         EffectAdded(ActiveEffect*);
	virtual void                         EffectRemoved(ActiveEffect*);
	virtual void                         EffectReflected(MagicCaster*, ActiveEffect*);
	virtual void                         EffectAbsorbed(MagicCaster*, ActiveEffect*);
	virtual float                        CheckResistance(MagicCaster*, MagicItem*, ActiveEffect*);
	virtual bool                         CheckAbsorb(MagicCaster*, MagicItem*, ActiveEffect*, bool);
	virtual bool                         CheckReflect(MagicCaster*, MagicItem*, ActiveEffect*);

	bool bShowTargetStats;
};

static_assert(sizeof(MagicTarget) == 0x10);