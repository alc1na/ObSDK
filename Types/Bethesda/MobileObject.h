#pragma once

#include "TESObjectREFR.h"

class MobileObject : public TESObjectREFR {
public:
	virtual bool MovetoHigh();
	virtual bool MovetoLow();
	virtual bool MovetoMiddleLow();
	virtual bool MovetoMiddleHigh();
	virtual bhkCharacterController* Move(float, NiPoint3*, unsigned int);
	virtual bhkCharacterController* Jump();
	virtual void SetAvoidanceDisabled(bool);
	virtual void Process(float);
	virtual bool ChangeProcessLevel();
	virtual bool DetachCharController();
	virtual void SetPosition(const NiPoint3*);
	virtual void GetLinearVelocity(NiPoint3*);
	virtual void EvaluateDetection(float);
	virtual float GetDetectionTimer();
	virtual void ReduceDetectionTimer();
	virtual float GetHeading();
	virtual void SetHeading(TESObjectREFR*);
	virtual void SetHeading(float);
	virtual void SetSize(float);
	virtual bool GetRunsInLow();
	virtual float GetAcrobatics();
	virtual bool IsDying();
	virtual bool IsTransient();
	virtual void SetDisplayGeometry(bool);

	BaseProcess* pCurrentProcess;
	float		 LastCollisionCheckTime;
};

static_assert(offsetof(MobileObject, pCurrentProcess) == 0x138);
static_assert(sizeof(MobileObject) == 0x148);
