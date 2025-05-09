#pragma once
#include "NiRefObject.h"
#include "NiTArray.h"

struct NiRTTI;

class NiNode;
class NiGeometry;
class NiTriBasedGeom;
class NiParticles;
class NiCloningProcess;
class NiStream;
class NiObjectGroup;

class NiObject : public NiRefObject {
public:
	virtual                 ~NiObject();
	virtual const NiRTTI*   GetRTTI();
	virtual NiNode*         IsNode();
	virtual NiGeometry*     IsGeometry();
	virtual NiTriBasedGeom* IsTriBasedGeom();
	virtual NiParticles*    IsParticlesGeom();
	virtual NiObject*       CreateClone(NiCloningProcess*);
	virtual void            LoadBinary(NiStream*);
	virtual void            LinkObject(NiStream*);
	virtual bool            RegisterStreamables(NiStream*);
	virtual void            SaveBinary(NiStream*);
	virtual bool            IsEqual(NiObject*);
	virtual void            GetViewerStrings(NiTArray<char*>*);
	virtual void            AddViewerStrings(NiTArray<char*>*);
	virtual void            ProcessClone(NiCloningProcess*);
	virtual void            PostLinkObject(NiStream*);
	virtual unsigned int    GetBlockAllocationSize();
	virtual NiObjectGroup*  GetGroup();
	virtual void            SetGroup(NiObjectGroup*);
};

static_assert(sizeof(NiObject) == 0x10);
