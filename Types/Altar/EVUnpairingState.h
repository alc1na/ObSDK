#pragma once
#include <cstdint>

enum EVUnpairingState : int32_t {
	NotUnpaired = 0x0,
	UnpairedAtDestruction = 0x1,
	UnpairedAtModelDeattachment = 0x2,
	UnpairedDueToCache = 0x3,
};
