#pragma once

struct VPairingEntry;

class IVPairableItem {
public:
	virtual bool ShouldBePaired();
	virtual void ProcessPairItem();
	virtual void ProcessUnpairItem();
	virtual void OnPrePairItem();
	virtual void OnPostPairItem();
	virtual void OnPreUnpairItem();
	virtual void OnPostUnpairItem();

	bool bIsActuallyPaired;
	VPairingEntry* pPairingEntry;
};

static_assert(sizeof(IVPairableItem) == 0x18);