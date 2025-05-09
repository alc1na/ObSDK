#pragma once
#include "MobileObject.h"

class AlchemyItem;
class EnchantmentItem;

class ArrowProjectile : public MobileObject {
public:
	enum ArrowCollisionType : __int32 {
		STATE_STICK_ACTOR = 0x0,
		STATE_STICK_REF = 0x1,
		STATE_STICK_GROUND = 0x2,
		STATE_BOUNCE = 0x3,
		STATE_SIMULATE = 0x4,
	};

	enum ArrowState : __int32 {
		STATE_FLYING = 0x0,
		STATE_COLLISION = 0x1,
		STATE_POST_COLLISION = 0x2,
		STATE_DELETING = 0x3,
	};

	struct CollisionInfo {
		ArrowCollisionType eCollisionType;
		NiPoint3           Point;
		NiPoint3           Normal;
		NiPoint3           Velocity;
		TESObjectREFR*     pCollidee;
		NiAVObject*        pClosestObject;
		NiMatrix3          Rotation;
	};

	CollisionInfo*   psCollisionData;
	ArrowState       eState;
	float            fFadeAlpha;
	float            fAge;
	float            fSpeed;
	float            fDamage;
	float            fWaterSpeed;
	Actor*           pShooter;
	EnchantmentItem* pEnchantment;
	EnchantmentItem* pBowEnchantment;
	AlchemyItem*     pPoison;
	NiPoint3         DeltaS;
	bool             bNeedsFinishInitLoadGame;
	bool             bAddedToInventory;
	bool             bBowIgnoresWeaponsResist;
	bool             bPostForce;
	unsigned int     iLoadGameFlags;
	float            fAgeMax;
	float            fArrowDamage;
	float            fBowAimDuration;
};
