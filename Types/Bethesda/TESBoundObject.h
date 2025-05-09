#pragma once
#include "TESObject.h"

class NiNode;
struct NiPoint3;

class TESBoundObject : public TESObject {
public:
	virtual NiAVObject* Clone3D(TESObjectREFR*);
	virtual bool        ReplaceModel(const char*);
	virtual void        CreateDistant3D(NiPoint3*, NiPoint3*, float*, unsigned int, unsigned int, unsigned int, NiNode*, NiNode*);
};
