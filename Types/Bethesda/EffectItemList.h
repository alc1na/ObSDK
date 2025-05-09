#pragma once
#include "BSSimpleList.h"
#include "MagicItem.h"
#include "SkillLevel.h"

class EffectItem;
class Actor;

struct EffectItemList : BSSimpleList<EffectItem*> {
	virtual float GetCost(Actor*);
	virtual int GetMaxEffectCount();
	virtual SkillLevel::Value GetLevel();

	int iHostileCount;
};
