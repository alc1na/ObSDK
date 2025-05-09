#pragma once
#include "BaseFormComponent.h"
#include "BSStringT.h"

class TESFullName : public BaseFormComponent {
public:
	TESFullName() = delete;
	virtual ~TESFullName();

	BSStringT<> cFullName;
};

static_assert(sizeof(TESFullName) == 0x18);