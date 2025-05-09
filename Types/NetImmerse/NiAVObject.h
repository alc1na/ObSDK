#pragma once
#include "NiBound.h"
#include "NiObjectNET.h"
#include "NiTList.h"
#include "NiTransform.h"

class NiCollisionObject;
class NiProperty;
class NiPropertyState;
class NiDynamicEffectState;
class NiCullingProcess;
class NiRenderer;

class NiAVObject : public NiObjectNET {
public:
	virtual ~NiAVObject();
	virtual void UpdateControllers(float);
	virtual void UpdateNodeBound();
	virtual void ApplyTransform(const NiMatrix3*, const NiPoint3*, bool);
	virtual NiAVObject* GetObjectByName(const char*);
	virtual void SetSelectiveUpdateFlags(bool*, bool, bool*);
	virtual void UpdateDownwardPass(float, bool);
	virtual void UpdateSelectedDownwardPass(float);
	virtual void UpdateRigidDownwardPass(float);
	virtual void UpdatePropertiesDownward(NiPropertyState*);
	virtual void UpdateEffectsDownward(NiDynamicEffectState*);
	virtual void UpdateWorldData();
	virtual void UpdateWorldBound();
	virtual void OnVisible(NiCullingProcess*);
	virtual void PurgeRendererData(NiRenderer*);

	unsigned __int16 m_uFlags;
	NiNode* m_pkParent;
	NiBound m_kWorldBound;
	NiTransform m_kLocal;
	NiTransform m_kWorld;
	NiTPointerList<NiPointer<NiProperty>> m_kPropertyList;
	NiPointer<NiCollisionObject> m_spCollisionObject;
};
