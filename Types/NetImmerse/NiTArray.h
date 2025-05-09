#pragma once
#include <cstdint>

template <typename T>
class NiTArray {
public:
	virtual ~NiTArray();

	T** m_pBase;
	uint16_t m_usMaxSize;
	uint16_t m_usSize;
	uint16_t m_usESize;
	uint16_t m_usGrowBy;
};