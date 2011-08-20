#pragma once
#include "GcVSListBox.h"
#include "GcMediateObject.h"

class GcActorExtraDataList : public GcVSListBox, public GcMediateObject
{
private:
	static int msLastSelectNumber;
protected:
	GtObject* mpGtObject;
	Gn2DMeshObject* mpMeshObject;
	GnTPrimitiveArray<GnExtraData*>* mpExtraDatas;

public:
	GcActorExtraDataList(void);
	~GcActorExtraDataList(void);

	void ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject);
protected:

	virtual void CreateNewItem();	
	virtual BOOL RemoveItem(int iIndex);
	virtual void OnSelectionChanged();
};

