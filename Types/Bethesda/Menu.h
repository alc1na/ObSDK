#pragma once
#include "BSSimpleList.h"
#include "BSStringT.h"
#include "Interface.h"
#include "IVPairableItem.h"
#include "NiTList.h"
#include "Tile.h"

class TileMenu;

class Menu : public IVPairableItem {
public:
	enum FADE_STATE : __int32 {
		FADE_SHOWN = 0x1,
		FADING_OUT = 0x2,
		FADE_HIDDEN = 0x4,
		FADING_IN = 0x8,
		FADE_ALL = 0xF,
		FADE_IN_SHOWN = 0x9,
		FADE_OUT_SHOWN = 0x3,
		FADE_NOT_HIDDEN = 0xB,
	};

	virtual ~Menu();
	virtual void AttachTileByID(int, Tile*);
	virtual void DoDownClick(int, Tile*);
	virtual void DoClick(int, Tile*);
	virtual void DoEnter(int, Tile*);
	virtual void DoLeave(int, Tile*);
	virtual void DoDragEnter(int, Tile*, Tile*);
	virtual void DoDragLeave(int, Tile*, Tile*);
	virtual void DoStillDown(int, Tile*);
	virtual void DoStillDragOver(int, Tile*);
	virtual void DoWheelMove(int, Tile*);
	virtual void DoIdle();
	virtual bool DoKey(int);
	virtual int GetClass();
	virtual bool DoGamepad(Interface::enumGamepadButtons, float);
	virtual void StartFadeOut();
	virtual void CancelFadeOut();
	virtual void StartFadeIn();

	TileMenu* pMenu;
	BSSimpleList<Tile::TileTemplate*> xTemplates;
	Tile* pLastTile;
	int iIsModal;
	int iMenuThickness;
	bool bForceFadeOut;
	bool bDeleteTemplates;
	int iClass;
	FADE_STATE xFadeState;
};
