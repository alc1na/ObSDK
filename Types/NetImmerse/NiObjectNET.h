#pragma once
#include <cstdint>

#include "NiObject.h"
#include "NiPointer.h"

struct NiExtraData;
struct NiTimeController;

class NiObjectNET : public NiObject {
public:
	virtual ~NiObjectNET();

	char* m_pcName;
	NiPointer<NiTimeController> m_spControllers;
	NiExtraData** m_ppkExtra;
	uint16_t m_usExtraDataSize;
	uint16_t m_usMaxSize;
};

static_assert(sizeof(NiObjectNET) == 0x30);