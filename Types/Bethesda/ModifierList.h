#pragma once
#include "BSSimpleList.h"
#include "Modifier.h"

struct FastModifierCollection;

class ModifierList : public BSSimpleList<Modifier*> {
public:
	Modifier* pMagickaModifier;
	Modifier* pFatigueModifier;
	FastModifierCollection* pFastModifiers;
};

struct FastModifierCollection {
	Modifier* pHealthModifier;
	Modifier* pEncumbranceModifier;
	Modifier* pMagickaMultiplierModifier;
	Modifier* pParalysisModifier;
	Modifier* pResponsibilityModifier;
	Modifier* pSilenceModifier;
	Modifier* pPersonalityModifier;
	Modifier* pWaterWalkingModifier;
	Modifier* pChameleonModifier;
	Modifier* pInvisibilityModifier;
	Modifier* pNightEyeBonusModifier;
	Modifier* pAggressionModifier;
	Modifier* pAcrobaticsModifier;
	Modifier* pEnduranceModifier;
	Modifier* pLuckModifier;
	Modifier* pStrengthModifier;
	Modifier* pSpeedModifier;
	Modifier* pAthleticsModifier;
};
