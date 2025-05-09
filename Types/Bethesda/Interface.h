#pragma once

class Interface {
public:
	enum enumGamepadButtons : uint32_t {
		eButtonNone = 0x0,
		eButtonDPadUp = 0x1,
		eButtonDPadDown = 0x2,
		eButtonDPadRight = 0x3,
		eButtonDPadLeft = 0x4,
		eButtonStart = 0x5,
		eButtonBack = 0x6,
		eButtonLThumb = 0x7,
		eButtonRThumb = 0x8,
		eButtonA = 0x9,
		eButtonB = 0xA,
		eButtonX = 0xB,
		eButtonY = 0xC,
		eButtonLT = 0xD,
		eButtonRT = 0xE,
		eButtonLB = 0xF,
		eButtonRB = 0x10,
		eButtonDownEvent = 0x2,
		eButtonUpEvent = 0x1,
		eButtonStillDownEvent = 0x0,
		eButtonIdleEvent = 0xFFFFFFFF,
		eButtonClick = 0xFFFFFFFE,
	};
};
