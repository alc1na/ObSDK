#pragma once
#include "MiscEnums.h"

class MagicSystem {
public:
	enum CastingType : __int32 {
		CAST_ONCE = 0x0,
		WHEN_USED = 0x1,
		WHEN_STRIKES = 0x2,
		CONSTANT_EFFECT = 0x3,
		CASTING_COUNT = 0x4,
	};

	enum SpellType : __int32 {
		SPELL = 0x0,
		DISEASE = 0x1,
		POWER = 0x2,
		LESSER_POWER = 0x3,
		ABILITY = 0x4,
		POISON = 0x5,
		ENCHANTMENT = 0x6,
		POTION = 0x7,
		WORTCRAFT = 0x8,
		LEVELED_SPELL = 0x9,
		SPELL_TYPE_COUNT = 0xA,
	};

	enum Range : __int32 {
		SELF = 0x0,
		TOUCH = 0x1,
		TARGET = 0x2,
		RANGE_COUNT = 0x3,
	};

	enum School : __int32 {
		ALTERATION = 0x0,
		CONJURATION = 0x1,
		DESTRUCTION = 0x2,
		ILLUSION = 0x3,
		MYSTICISM = 0x4,
		RESTORATION = 0x5,
		SCHOOL_COUNT = 0x6,
	};

	static ActorValue::Index MagicSchoolToSkill(const School aeSchool) {
		switch (aeSchool) {
			case ALTERATION:
				return ActorValue::Index::ALTERATION;
			case CONJURATION:
				return ActorValue::Index::CONJURATION;
			case DESTRUCTION:
				return ActorValue::Index::DESTRUCTION;
			case ILLUSION:
				return ActorValue::Index::ILLUSION;
			case MYSTICISM:
				return ActorValue::Index::MYSTICISM;
			case RESTORATION:
				return ActorValue::Index::RESTORATION;
			default:
				return ActorValue::Index::MAX;
		}
	}
};
