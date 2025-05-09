#pragma once
#include "TESCondition.h"
#include "TESForm.h"

class PackageLocation;
class PackageTarget;

enum PACKAGE_PROCEDURE_TYPE : uint32_t {
	PACKAGE_PROCEDURE_NONE                   = 0xFFFFFFFF,
	PACKAGE_PROCEDURE_EXPLORE_TRAVEL         = 0x0,
	PACKAGE_PROCEDURE_EXPLORE_WANDER         = 0x1,
	PACKAGE_PROCEDURE_EXPLORE_ACTIVATE       = 0x2,
	PACKAGE_PROCEDURE_EXPLORE_AQUIRE         = 0x3,
	PACKAGE_PROCEDURE_SLEEP                  = 0x4,
	PACKAGE_PROCEDURE_EAT                    = 0x5,
	PACKAGE_PROCEDURE_FOLLOW_WITH_ESCORT     = 0x6,
	PACKAGE_PROCEDURE_FOLLOW_WITHOUT_ESCORT  = 0x7,
	PACKAGE_PROCEDURE_ESCORT_ACTOR           = 0x8,
	PACKAGE_PROCEDURE_ESCORT_OBJECT          = 0x9,
	PACKAGE_PROCEDURE_DIALOGUE               = 0xA,
	PACKAGE_PROCEDURE_ALARM                  = 0xB,
	PACKAGE_PROCEDURE_COMBAT                 = 0xC,
	PACKAGE_PROCEDURE_ACTIVATE               = 0xD,
	PACKAGE_PROCEDURE_GREET                  = 0xE,
	PACKAGE_PROCEDURE_OBSERVE_COMBAT         = 0xF,
	PACKAGE_PROCEDURE_OBSERVE_DIALOGUE       = 0x10,
	PACKAGE_PROCEDURE_TALK_TO_DEAD           = 0x11,
	PACKAGE_PROCEDURE_COMBAT_NOT_IN_HIGH     = 0x12,
	PACKAGE_PROCEDURE_FLEE                   = 0x13,
	PACKAGE_PROCEDURE_TRESPASS               = 0x14,
	PACKAGE_PROCEDURE_GET_UP                 = 0x15,
	PACKAGE_PROCEDURE_EXPLORE_NPC            = 0x16,
	PACKAGE_PROCEDURE_MOUNT_HORSE            = 0x17,
	PACKAGE_PROCEDURE_DISMOUNT_HORSE         = 0x18,
	PACKAGE_PROCEDURE_DO_NOTHING             = 0x19,
	PACKAGE_PROCEDURE_EXPLORE_AQUIRE_GENERIC = 0x1A,
	PACKAGE_PROCEDURE_CAST_TARGET_SPELL      = 0x1B,
	PACKAGE_PROCEDURE_CAST_TOUCH_SPELL       = 0x1C,
	PACKAGE_PROCEDURE_ACCOMPANY              = 0x1D,
	PACKAGE_PROCEDURE_USEITEMAT              = 0x1E,
	PACKAGE_PROCEDURE_FEED                   = 0x1F,
	PACKAGE_PROCEDURE_AMBUSH                 = 0x20,
	PACKAGE_PROCEDURE_SURFACE                = 0x21,
	PACKAGE_PROCEDURE_CASTING                = 0x22,
	PACKAGE_PROCEDURE_FLEE_NON_COMBAT        = 0x23,
	PACKAGE_PROCEDURE_SEARCH                 = 0x24,
	PACKAGE_PROCEDURE_CLEAR_MOUNT_POSITION   = 0x25,
	PACKAGE_PROCEDURE_SUMMON_CREATURE_DEFEND = 0x26,
	PACKAGE_PROCEDURE_MOVEMENT_BLOCKED       = 0x27,
	PACKAGE_PROCEDURE_COUNT                  = 0x28,
};

struct PACKAGE_DATA {
	unsigned int iPackFlags;
	char cPackType;
};

struct PACK_SCHED_DATA
{
	char eMonth;
	char eDayOfWeek;
	char cDate;
	char cTime;
	int iDuration;
};

struct PackageSchedule {
	PACK_SCHED_DATA PSData;
};

class TESPackage : TESForm {
public:
	virtual                  ~TESPackage();
	virtual unsigned __int16 GetSaveSize();
	virtual void             SaveGame();
	virtual void             LoadGame();
	virtual void             InitLoadGame();

	PACKAGE_PROCEDURE_TYPE ePROCEDURE_TYPE;
	PACKAGE_DATA           PackData;
	PackageLocation*       pPackLoc;
	PackageTarget*         pPackTarg;
	PackageSchedule        packSched;
	TESCondition           packConditions;
};
