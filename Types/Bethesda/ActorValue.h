#pragma once
#include "MiscEnums.h"

struct ActorValue {
	typedef EAttributeStat Index;

	enum Section : __int32 {
		ATTRIBUTE = 0x0,
		DERIVED_ATTRIBUTE = 0x1,
		SKILL = 0x2,
		TRAIT = 0x3,
		VIRTUE = 0x4,
		FLOAT_VALUE = 0x5,
		INT_VALUE = 0x6,
	};

	static Index ToArrayIndex(const Section aiSection, const Index aiIndex) {
		const auto index = static_cast<int8_t>(aiIndex);

		switch (aiSection) {
			case ATTRIBUTE: return aiIndex;
			case DERIVED_ATTRIBUTE: return static_cast<Index>(index - 8);
			case SKILL: return static_cast<Index>(index - 12);
			case TRAIT: return static_cast<Index>(index - 33);
			case VIRTUE: return static_cast<Index>(index - 37);
			case FLOAT_VALUE: return static_cast<Index>(index - 40);
			case INT_VALUE: return static_cast<Index>(index - 42);
		}

		return EAttributeStat::STRENGTH;
	}
};
