#pragma once
#include "BSSimpleList.h"

struct TESConditionItem;

struct TESCondition {
	BSSimpleList<TESConditionItem*> listConditions;
};