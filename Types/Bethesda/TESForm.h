#pragma once
#include "BaseFormComponent.h"
#include "BSSimpleList.h"
#include "BSStringT.h"
#include "EFormFlags.h"
#include "EFormType.h"
#include "EFormID.h"
#include "NiTPointerMap.h"

struct FORM;
struct FORM_GROUP;

class TESFile;
class ExportTESForm;
class TESObjectREFR;
class TESBoundObject;

class TESForm : public BaseFormComponent {
public:
	virtual                  ~TESForm();
	virtual void             InitializeData();
	virtual void             ClearData();
	virtual bool             Load(TESFile*);
	virtual bool             Save(TESFile*);
	virtual void             Save();
	virtual bool             LoadEdit(TESFile*);
	virtual bool             SaveEdit(TESFile*);
	virtual bool             SavesBefore(FORM*);
	virtual bool             SavesBefore(TESForm*);
	virtual TESForm*         CreateDuplicateForm(bool, NiTPointerMap<TESForm*, TESForm*>*);
	virtual void             PostDuplicateProcess(NiTPointerMap<TESForm*, TESForm*>*);
	virtual void             AddChange(unsigned int);
	virtual void             RemoveChange(unsigned int);
	virtual void             ForceChange(unsigned int);
	virtual unsigned __int16 GetSaveSize(unsigned int);
	virtual void             SaveGame(unsigned int);
	virtual void             LoadGame(unsigned int, unsigned int);
	virtual void             InitLoadGame(unsigned int, unsigned int);
	virtual void             FinishInitLoadGame(unsigned int, unsigned int);
	virtual void             Revert(unsigned int);
	virtual void             LoadQueuedFormData(unsigned __int16);
	virtual bool             FindInFileFast(TESFile*);
	virtual void             InitItem();
	virtual ENUM_FORM_ID     GetSavedFormType();
	virtual void             GetFormDetailedString(BSStringT<char>*);
	virtual bool             GetQuestObject();
	virtual bool             GetHasSpokenFlag();
	virtual bool             GetHavokDeath();
	virtual bool             GetNeedtoChangeProcess();
	virtual bool             GetDangerous();
	virtual void             SetDelete(bool);
	virtual void             SetAltered(bool);
	virtual void             SetQuestObject(bool);
	virtual void             SetHasSpokenFlag(bool);
	virtual void             SetHavokDeath(bool);
	virtual void             SetNeedToChangeProcess(bool);
	virtual bool             IsBoundObject();
	virtual bool             IsObject();
	virtual bool             IsMagicItem();
	virtual unsigned int     GetRefCount();
	virtual void             Copy(TESForm*);
	virtual bool             Compare(TESForm*);
	virtual bool             BelongsInGroup(FORM*, bool, bool);
	virtual void             CreateGroupData(FORM*, FORM_GROUP*);
	virtual bool             IsParentForm();
	virtual bool             IsFormTypeChild(unsigned __int8);
	virtual bool             Activate(TESObjectREFR*, TESObjectREFR*, bool, TESBoundObject*, int);
	virtual char*            GetObjectTypeName();
	virtual const char*      GetFormEditorID();
	virtual bool             SetFormEditorID(const char*);
	virtual unsigned __int8  GetLastLoadFileIndex();
	virtual void             FillExportForm(bool);
	virtual void             UpdateFormValues(const ExportTESForm*);
	virtual ExportTESForm*   GetExportForm(bool);
	virtual bool             HasDifferentFormValues(const ExportTESForm*);

	EFormType cFormType;
	EFormFlags iFormFlags;
	uint32_t iFormID;
	BSSimpleList<TESFile*> pSourceFiles;
	ExportTESForm* pExportForm;
};

static_assert(sizeof(TESForm) == 0x30);