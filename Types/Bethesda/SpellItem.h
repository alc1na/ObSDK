#pragma once
#include "MagicItemForm.h"

class SpellItem : public MagicItemForm {
public:
	struct SpellItemData {
		MagicSystem::SpellType iSpellType;
		int iCostOverride;
		uint8_t eLevelOverride[4];
		uint8_t flags;
	};

	SpellItemData data;
};
