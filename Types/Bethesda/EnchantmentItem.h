#pragma once
#include "MagicItemForm.h"
#include "MagicSystem.h"

class EnchantmentItem : public MagicItemForm {
public:
	virtual ~EnchantmentItem();

	struct EnchantmentItemData {
		MagicSystem::CastingType eCastingType;
		int iChargeOverride;
		int iCostOverride;
		unsigned __int8 iFlags;
	};

	EnchantmentItemData data;
};

ASSERT_SIZE(EnchantmentItem, 0xA0);