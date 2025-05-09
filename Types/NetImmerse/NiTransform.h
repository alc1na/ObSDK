#pragma once
#include "NiMatrix3.h"
#include "NiPoint3.h"

struct NiTransform
{
	NiMatrix3 m_Rotate;
	NiPoint3 m_Translate;
	float m_fScale;
};