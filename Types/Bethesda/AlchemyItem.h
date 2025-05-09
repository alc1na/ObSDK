#pragma once
#include "MagicItemObject.h"
#include "TESIcon.h"
#include "TESModel.h"
#include "TESScriptableForm.h"
#include "TESWeightForm.h"

class AlchemyItem : public MagicItemObject, public TESModel, public TESIcon, public TESScriptableForm, public TESWeightForm {
public:
	struct AlchemyItemData {
		int iCostOverride;
		unsigned __int8 iFlags;
	};

	AlchemyItemData data;
};

ASSERT_SIZE(AlchemyItem, 0x120);