#pragma once
#include "Scanner.h"
#include "ExtraDataList.h"
#include "PlayerCharacter.h"

namespace Signatures {
	inline void Init() {
		PlayerCharacter::InitSignatures();
	}
}
