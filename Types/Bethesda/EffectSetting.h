#pragma once
#include "MagicSystem.h"
#include "TESDescription.h"
#include "TESForm.h"
#include "TESFullName.h"
#include "TESIcon.h"
#include "TESModel.h"

class TESEffectShader;
class TESSound;
class TESObjectLIGH;

class EffectSetting : public TESForm, public TESModel, public TESDescription, public TESFullName, public TESIcon {
public:
	virtual ~EffectSetting();

	struct EffectSettingData {
		unsigned int        iFlags;
		float               fBaseCost;
		unsigned int        iAssociatedItem;
		MagicSystem::School iMagicSchool;
		uint8_t             iResistVariable[4];
		__int16             iNumCounterEffects;
		TESObjectLIGH*      pLight;
		float               fSpeed;
		TESEffectShader*    pEffectShader;
		TESEffectShader*    pEnchantEffect;
		TESSound*           pCastSound;
		TESSound*           pBoltSound;
		TESSound*           pHitSound;
		TESSound*           pAreaSound;
		float               fCEEnchantFactor;
		float               fCEBarterFactor;
	};

	bool      (__fastcall* pFilterValidationFunction) (EffectSetting*, void*);
	void*                  pFilterValidationItem;
	EffectSettingData      data;
	uint8_t                iEffectID[4];
	uint8_t*			   pCounterEffects;
	int                    iEffectLoadedCount;
	int                    iAssociatedItemLoadedCount;
};

ASSERT_SIZE(EffectSetting, 0x128);