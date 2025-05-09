#pragma once
#include <cstdint>

class NiRefObject {
public:
	virtual ~NiRefObject();

	volatile uint32_t m_uiRefCount;
};
