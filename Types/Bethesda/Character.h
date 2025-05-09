#pragma once
#include "Actor.h"

class Character : public Actor {
public:
	BipedAnim* pBiped;
	float fArmorRating;
};

static_assert(sizeof(Character) == 0x328);
