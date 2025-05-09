#pragma once
#include "BSSimpleList.h"
#include "BSStringT.h"
#include "NiTList.h"

class NiNode;

class Tile {
public:
	enum enumAction : __int32 {
		eNullAction = 0x0,
		eGroupStart = 0xA,
		eGroupEnd = 0xF,
		eActionStart = 0x14,
		eActionEnd = 0x19,
		eTraitStart = 0x1E,
		eTraitEnd = 0x23,
		eTileStart = 0x28,
		eTileEnd = 0x2D,
		eSimpleTrait = 0x32,
		eSimpleAction = 0x37,
		eTraitLink = 0x3C,
		eTop = 0x65,
		eCopy = 0x7D1,
		eFirstAction = 0x7D1,
		eAdd = 0x7D2,
		eSub = 0x7D3,
		eMult = 0x7D4,
		eDiv = 0x7D5,
		eRand = 0x7D6,
		eUser = 0x7D7,
		eGt = 0x7D8,
		eGte = 0x7D9,
		eEq = 0x7DA,
		eLte = 0x7DB,
		eLt = 0x7DC,
		eMin = 0x7DD,
		eMax = 0x7DE,
		eAnd = 0x7DF,
		eOr = 0x7E0,
		eNeq = 0x7E1,
		eMod = 0x7E2,
		eTrunc = 0x7E3,
		eAbs = 0x7E4,
		eOnlyIf = 0x7E5,
		eOnlyIfNot = 0x7E6,
		eLn = 0x7E7,
		eLog = 0x7E8,
		eCeil = 0x7E9,
		eNot = 0x7EA,
		eRef = 0x7EB,
		eLastAction = 0x7EB,
	};

	struct Action {
		Action* pPrevAction;
		Action* pNextAction;

		struct {
			float fValue;
			struct Value* pOwner;
			enumAction eGroupType;
		} uValue;

		enumAction eAction;
		Action* pPrevReaction;
		Action* pNextReaction;
	};

	struct Value {
		Tile* pParent;
		float fValue;
		BSStringT<char> xString;
		Action* pActions;
		Action* pReactions;
		unsigned __int16 iIndex;
		bool bIsNumber;
	};

	struct FadeControl {
		Tile* pParent;
		int iTrait;
		float fStart;
		float fEnd;
		float fLen;
		Tile::FadeControl* pNext;
	};

	struct TileTemplateItem {
		int iCmd;
		float fVal;
		BSStringT<> xStr;
		union {
			int iTA;
			Tile* pTile;
			struct TileTemplate* pTemplate;
		} u;
		int iLine;
	};

	struct TileTemplate {
		BSStringT<> xName;
		struct BuildStorage* pParent;
		NiTList<TileTemplateItem*> xList;
	};

	struct BuildStorage {
		TileTemplate* pTemplate;
		BSSimpleList<TileTemplate*> xSubTemplates;
		TileTemplate* pCurrentTemplate;
		bool bDeleteTemplates;
	};

	virtual ~Tile();
	virtual void Init(Tile*, const char*, Tile*);
	virtual NiNode* MakeNode();
	virtual int GetType();
	virtual const char* GetTypeName();
	virtual Tile* PostParse(int, float, const char*);
	virtual void ForceTextureRelease();

	bool bReleased;
	bool bMenuDeleting;
	bool bManualUpdateTris;
	bool bScissorHidden;
	BSStringT<> xName;
	Tile* pParent;
	NiTList<Value*> xTraits;
	NiNode* pModel;
	FadeControl* pFadeControls;
	int bfNeedsUpdate;
	NiTList<Tile*> xChildren;
};
