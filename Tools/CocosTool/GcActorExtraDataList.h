#pragma once
#include "GcVSListBox.h"
#include "GcMediateObject.h"

class GcActorExtraDataList : public GcVSListBox, public GcMediateObject
{
protected:
	GtObject* mpGtObject;
	Gn2DMeshObject* mpMeshObject;
	GnTPrimitiveArray<GnExtraData*>* mpExtraDatas;

public:
	GcActorExtraDataList(void);
	~GcActorExtraDataList(void);

	void ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject);

	CString GetMakeName(gtuint i, int iType);
protected:

	virtual void CreateNewItem();	
	virtual BOOL RemoveItem(int iIndex);
};

