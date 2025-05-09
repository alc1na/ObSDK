#pragma once
#include "NiPoint3.h"

struct FurnitureMark {
	NiPoint3 Position;
	unsigned __int16 sHeading;
	unsigned __int8 cNumber;
};

ASSERT_SIZE(FurnitureMark, 0x10);