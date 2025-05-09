#pragma once
#include "BaseFormComponent.h"
#include "BSSimpleList.h"

class TESBoundObject;
struct ContainerObject;

class TESContainer : public BaseFormComponent
{
public:
	virtual ~TESContainer();

	char contFlag;
	BSSimpleList<ContainerObject*> objectList;
};

struct ContainerObject {
	int i_count;
	TESBoundObject* pObj;
};