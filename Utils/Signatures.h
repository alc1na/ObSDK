#pragma once
#include "PlayerCharacter.h"
#include "CombatController.h"

namespace Signatures {
	inline void Init() {
		PlayerCharacter::InitSignatures();
		CombatController::InitSignatures();
	}
}
