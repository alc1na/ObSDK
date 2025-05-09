#pragma once
#include "BaseFormComponent.h"

class Script;
class TESScriptableForm : public BaseFormComponent {
public:
	Script* pFormScript;
	bool bIsInitialized;
};