#pragma once
#include "BSSimpleList.h"

struct ExtraDataList;
class TESBoundObject;

struct ItemChange {
	BSSimpleList<ExtraDataList*>* pExtraObjectList;
	int iNumber;
	TESBoundObject* pContainerObj;
};

ASSERT_SIZE(ItemChange, 0x18);