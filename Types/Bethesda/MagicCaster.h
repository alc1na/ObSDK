#pragma once
#include <cstdint>

#include "InputState.h"
#include "MagicItem.h"

class SpellItem;
class NiNode;
class TESObjectREFR;
class MagicTarget;
class ActiveEffect;
class TESBoundObject;
class MagicLight;
class MagicProjectile;
class EffectItem;

class MagicCaster {
public:
	typedef InputState::ActionMappings State;

	virtual bool           CastSpell(MagicItem*, MagicTarget*, bool);
	virtual void           CastAbility(SpellItem*, bool);
	virtual void           TransferDisease(SpellItem*, MagicTarget*, bool);
	virtual void           CastWornEnchantment(MagicItem*, TESBoundObject*, bool);
	virtual MagicTarget*   GetTouchTarget();
	virtual void           StartAim();
	virtual void           StartCast();
	virtual void           SpellCast(MagicItem*, bool);
	virtual bool           CheckCast(MagicItem*, float*, MagicItem::CannotCastReason*, bool);
	virtual TESObjectREFR* GetCasterStatsObject();
	virtual NiNode*        GetMagicNode();
	virtual bool           TargetSelf(ActiveEffect*);
	virtual float          GetMagicEffectivenessModifier(bool, float);
	virtual MagicItem*     GetCurrentSpell();
	virtual void           SetCurrentSpell(MagicItem*);
	virtual MagicTarget*   GetDesiredTarget();
	virtual void           SetDesiredTarget(MagicTarget*);
	virtual ActiveEffect*  CreateActiveEffect(MagicItem*, EffectItem*, TESBoundObject*);

	MagicLight*      pLight;
	State            eState;
	MagicProjectile* pUsedProjectile;
};

static_assert(sizeof(MagicCaster) == 0x20);