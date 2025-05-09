#pragma once
#include <cstdint>

template <typename T = char>
struct BSStringT {
	T* pStr;
	uint16_t sLen;
	uint16_t sMaxLen;
};

static_assert(sizeof(BSStringT<>) == 0x10);