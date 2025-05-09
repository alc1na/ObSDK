#pragma once
#include <string>

struct ItemEffectPairingData {
	int Index;
	int EffectID;
	std::basic_string<char> EffectNameLocKey;
	std::basic_string<char> AdditionalEffectNameLocKey;
	uint32_t Range;
	int MagickaCost;
	int Magnitude;
	uint32_t MagnitudeType;
	int AreaOfEffect;
	int Duration;
	std::basic_string<char> IconPath;
	uint8_t MagicType[4];
	bool bIsActiveEffect;
};
