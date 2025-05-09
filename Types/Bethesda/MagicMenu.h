#pragma once
#include "Menu.h"

class ActiveEffect;
class SpellItem;

class MagicMenu : public Menu {
public:
	struct Pg5Item {
		ActiveEffect* pEffect;
		int iTotMag;
	};

	struct Pg5List : BSSimpleList<Pg5Item*> {};

	Tile* pFocus;
	Tile* pItemList;
	Tile* pScrollBar;
	Tile* pScrollMarker;
	BSSimpleList<SpellItem> xSpellList;
	Pg5List xPg5List;
	Tile* pLastFocus;
	Tile* pEquipped;
	int iFilterFor;
	int iBeginActive;
	float fScrollOffset;
	bool IsVisible;
};
