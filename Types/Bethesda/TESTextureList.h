#pragma once

struct BSFileEntry;

struct TESTextureList {
	unsigned __int8 cTextureCount;
	BSFileEntry** pTextureOffsetArray;
};
