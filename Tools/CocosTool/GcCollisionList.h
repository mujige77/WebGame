#pragma once
#include "GcVSListBox.h"
#include "GcMediateObject.h"

class GcCollisionList : public GcVSListBox, public GcMediateObject
{
protected:
	Gn2DAVData* mpAVData;
	Gt2DSequence* mpSequence;

public:
	GcCollisionList(void);
	~GcCollisionList(void);
	
	void ResetData(Gt2DSequence* pSequence);

	CString GetMakeName(gtuint i, int iType);
protected:

	virtual void CreateNewItem();	
	virtual BOOL RemoveItem(int iIndex);
};

