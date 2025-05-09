#pragma once
#include "LowProcess.h"

class MiddleLowProcess : public LowProcess {
public:
	virtual		 ~MiddleLowProcess();
	virtual bool ProcessCombatOneHour(Actor*, float);

	int          iHourPackageEvaluated;
	ModifierList pMagicModifiers;
};

ASSERT_SIZE(MiddleLowProcess, 0x138);