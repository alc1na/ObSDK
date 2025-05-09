#pragma once
#include <cstdint>

struct BSExtraData;

struct BaseExtraList {
	virtual ~BaseExtraList();

	BSExtraData* pHead;
	uint8_t cPresenceBitfield[16];
};

static_assert(sizeof(BaseExtraList) == 0x20);