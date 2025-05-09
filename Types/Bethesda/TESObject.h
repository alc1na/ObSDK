#pragma once
#include "TESForm.h"

struct TESObjectList;

class BipedAnim;
class NiAVObject;
class TESObjectCELL;

class TESObject : public TESForm {
public:
	virtual NiAVObject*  Load3D();
	virtual bool         IsBoundAnimObject();
	virtual bool         IsAutoCalc();
	virtual void         SetAutoCalc(bool);
	virtual NiAVObject*  Clone3D(TESObjectREFR*, bool);
	virtual void         UnClone3D(TESObjectREFR*);
	virtual bool         IsMarker();
	virtual void         InitDefaultWorn();
	virtual bool         ReplaceModel();
	virtual bool         ReplaceModel(BipedAnim*);
	virtual void         Set3D(NiAVObject*);
	virtual unsigned int IncRef();
	virtual unsigned int DecRef();
	virtual NiAVObject*  LoadGraphics(TESObjectREFR*);

	TESObjectList* m_pParentList;
	TESObject* nod_lpPrev;
	TESObject* nod_lpNext;
};

struct TESObjectList {
	unsigned int lnk_dwCount;
	TESObject* lnk_lpRoot;
	TESObject* lnk_lpTail;
	TESObjectCELL* pOwner;
};
