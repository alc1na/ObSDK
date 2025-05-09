#pragma once
#include "IVPairableItem.h"
#include "TESForm.h"
#include "TESFullName.h"

struct ExtraDataList;
class TESWorldspace;
class TESObjectLAND;
class TESPathGrid;

class TESObjectCELL : public TESForm, public TESFullName, public IVPairableItem {
public:
	bool                         bCellFullyPaired;
	BSSimpleList<TESObjectREFR*> PrePlacedActorStillNotPaired;
	bool                         bIsUnpairedBecauseOfCache;
	char                         cCellFlags;
	char                         cCellGameFlags;
	char                         cCellState;
	ExtraDataList                ExtraData;
	void*                        pCellData;
	TESObjectLAND*               pCellLand;
	TESPathGrid*                 pCellGrid;
	BSSimpleList<TESObjectREFR*> listReferences;
	uint32_t                     unkC8;
	NiPointer<NiNode>            spCell3D;
};

static_assert(sizeof(TESObjectCELL) == 0xD8);
static_assert(offsetof(TESObjectCELL, ExtraData) == 0x80);
static_assert(offsetof(TESObjectCELL, cFullName) == 0x38);
