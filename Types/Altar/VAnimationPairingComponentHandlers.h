#pragma once

struct VAnimationPairingComponentHandlers {
	struct OblivionAnimSectionInfo {
		__int16 GroupAction;
		unsigned __int16 GroupID;
		int SequenceIdx;
	};

	struct OblivionAnimState {
		int Action;
		unsigned __int16 MoveMode;
		OblivionAnimSectionInfo AnimBodySectionInfos[5];
	};
};
