#pragma once
#include <cstdint>

class BSExtraData {
public:
	virtual ~BSExtraData();
	virtual bool Compare(BSExtraData*);

	uint8_t type;
	BSExtraData* pNext;
};

static_assert(sizeof(BSExtraData) == 0x18);