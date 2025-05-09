#pragma once
#include "BaseFormComponent.h"
#include "TESTextureList.h"

class TESModel : public BaseFormComponent {
public:
	BSStringT<> cModel;
	float fBoundSize;
	TESTextureList TextureList;
};

ASSERT_SIZE(TESModel, 0x30);