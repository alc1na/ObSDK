#pragma once
#include "TESForm.h"
#include "MagicItem.h"

class MagicItemForm : public TESForm, public MagicItem {
public:
	virtual ~MagicItemForm();
};
