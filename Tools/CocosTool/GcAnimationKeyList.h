#pragma once
#include "GcVSListBox.h"
class GnAnimationKeyManager;

class GcAnimationKeyList : public GcVSListBox
{
	Gt2DSequencePtr mpsSequence;
	GnAnimationKeyManager* mpAniKeyManager;
	float mCurrentTime;

public:
	GcAnimationKeyList(void);
	~GcAnimationKeyList(void);	

	void ResetData(Gt2DSequence* pSequence);
	gint GetAniKeyIndex(int iItemIndex);
	inline float GetCurrentTime() {
		return mCurrentTime;
	}
	inline void SetCurrentTime(float val) {
		mCurrentTime = val;
	}
protected:
	
	virtual void CreateNewItem();	
	virtual BOOL RemoveItem(int iIndex);
	virtual void CreateTegIDKey();
	CString GetMakeName(int iIndex, guint aniKeyType);
};

