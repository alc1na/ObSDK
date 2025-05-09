#pragma once
#include "EVUnpairingState.h"
#include "ExtraDataList.h"
#include "IVPairableItem.h"
#include "MiscEnums.h"
#include "NiAVObject.h"
#include "NiPoint3.h"
#include "NiPointer.h"
#include "TESChildCell.h"
#include "TESContainer.h"
#include "TESForm.h"
#include "TESMemContextForm.h"

struct VPairingEntry;

class hkRigidBody;
class bhkSimpleShapePhantom;
class BipedAnim;
class bhkCharacterController;
class BSAnimGroupSequence;
class TESTopic;
class Actor;
class Animation;
class TESActorBase;
class BSFaceGenAnimationData;
class BaseProcess;
class BSFaceGenNiNode;
class TrapEntry;
class TargetEntry;

class TESObjectREFR : public TESForm, public TESChildCell, public IVPairableItem, public TESMemContextForm {
public:
	virtual float VoiceSoundFunction(TESTopic*, Actor*, bool, bool, bool);
	virtual bool GetCastShadows();
	virtual void SetCastShadows(bool);
	virtual bool IsProjectile();
	virtual float GetScale();
	virtual NiPoint3* GetStartingAngle(NiPoint3* result);
	virtual NiPoint3* GetStartingLocation(NiPoint3* result);
	virtual void SetStartingPosition(NiPoint3);
	virtual void UpdateRefLight();
	virtual void AddBoundObjectItem(TESBoundObject*, ExtraDataList*, int);
	virtual TESObjectREFR* RemoveItem(TESBoundObject*, ExtraDataList*, int, bool, bool, TESObjectREFR*, NiPoint3*, NiPoint3*, bool, bool);
	virtual void RemoveItemType(ENUM_FORM_ID, bool, int);
	virtual bool AddWornItem(TESBoundObject*, int, ExtraDataList*, bool);
	virtual bool RemoveWornItem(TESBoundObject*, int, ExtraDataList*);
	virtual void DoTrap(TrapEntry*, TargetEntry*);
	virtual void AddObjecttoContainer(TESBoundObject*, ExtraDataList*, int);
	virtual void ReturnToOblivionEntryPoint();
	virtual NiPoint3* GetLookingAtLocation(NiPoint3* result);
	virtual MagicCaster* GetMagicCaster();
	virtual MagicTarget* GetMagicTarget();
	virtual TESActorBase* GetTemplateActorBase();
	virtual void SetTemplateActorBase(TESActorBase*);
	virtual BSFaceGenNiNode* GetFaceNodeBiped(NiNode*);
	virtual BSFaceGenNiNode* GetFaceNodeSkinned(NiNode*);
	virtual BSFaceGenNiNode* GetFaceNode(NiNode*);
	virtual BSFaceGenAnimationData* GetFaceAnimationData(NiNode*);
	virtual bool ClampToGround();
	virtual bool DetachHavok();
	virtual void InitHavok();
	virtual NiAVObject* Load3D();
	virtual void Set3D(NiAVObject*);
	virtual NiAVObject* Get3D();
	virtual NiPoint3* GetBoundMin(NiPoint3* result);
	virtual NiPoint3* GetBoundMax(NiPoint3* result);
	virtual void UpdateAnimation();
	virtual Animation* GetAnimation();
	virtual BipedAnim* GetBiped();
	virtual void SetBiped(BipedAnim*);
	virtual TESBoundObject* GetObjectReference();
	virtual const NiPoint3* GetLocationOnReference();
	virtual void MoveHavok(bool);
	virtual void SetActionComplete(bool);
	virtual void SetMovementComplete(bool);
	virtual void ResetInventory(bool);
	virtual bool IsMobileObject();
	virtual SIT_SLEEP_STATE GetSitSleepState();
	virtual bool IsActor();
	virtual void SetParentCell(TESObjectCELL*);
	virtual bool IsDead(bool);
	virtual bool IsKnockedOut();
	virtual bool IsParalyzed();
	virtual void OnModelAttached();
	virtual void OnModelDeattached();
	virtual void OnPostModelAttached();
	virtual void OnEnabled();
	virtual void OnDisabled();
	virtual bool IsPairable();
	virtual void PairAnimationInitialization(const BSAnimGroupSequence* const);
	virtual void SendPositionPairingHandler();

	struct OBJ_REFR {
		TESBoundObject* pObjectReference;
		NiPoint3 Angle;
		NiPoint3 Location;
	};

	struct FVDoorTeleportationInfo {
		TESObjectREFR* TeleportingDoor;
		bool bIdFlag;
		TESBoundObject* ObjectToGet;
		int Count;
	};

	OBJ_REFR data;
	float fRefScale;
	NiPointer<NiAVObject> m_spData3D;
	TESObjectCELL* pParentCell;
	ExtraDataList m_Extra;
	unsigned int AsyncFlowHash;
	bool bIsOblivionRefLoaded;
	bool bIsAltarRefLoaded;
	hkRigidBody* AltarFakeRigidBody;
	bhkSimpleShapePhantom* AltarFakePhantom;
	bool HasTrapContinuityBeenCheckedInReverse;
	TESObjectREFR* DockedActor;
	EVUnpairingState UnpairingState;
	VPairingEntry* pDroppedBy;
	bool bIsBeingTeleported;
	FVDoorTeleportationInfo PendingDoorTeleportationInfo;
	unsigned int LevelCreatureFormID;
	TESContainer ChosenCreatures;
	bool bisContainerInit;
	unsigned __int8 LastLoadFileCompileIndex;
};

static_assert(sizeof(TESObjectREFR) == 0x138);