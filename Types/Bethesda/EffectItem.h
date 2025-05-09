#pragma once
#include <cstdint>

#include "BSStringT.h"
#include "MagicSystem.h"

struct ScriptEffectItemData;

class EffectSetting;
class ExportEffectItem;

class EffectItem {
public:
	virtual ~EffectItem();
	virtual void FillExportForm(ExportEffectItem*);
	virtual void UpdateFormValues(const ExportEffectItem*);

	struct EffectItemData {
		uint8_t iEffectID[4];
		int iMagnitude;
		int iArea;
		int iDuration;
		MagicSystem::Range iRange;
		uint8_t iActorValue[4];
	};

	EffectItemData data;
	ScriptEffectItemData* pScriptEffectData;
	EffectSetting* pEffectSetting;
	float fRawCost;
};

struct ScriptEffectItemData {
	unsigned int iScriptID;
	MagicSystem::School iMagicSchool;
	BSStringT<> cEffectName;
	uint8_t iVisualsEffectID[4];
	bool bHostile;
};
