#pragma once
#include "GtObject.h"

class Gt2DActor : public GtObject
{
public:
	const static  gint OBJECT_TYPE = 1;
private:
	Gn2DActorPtr mpsActor;
	GnSimpleString mGATFileName;
	Gt2DSequence* mModifySequence;
	GnTMap<guint32, Gt2DSequencePtr> mpGtSequences;

public:
	Gt2DActor(void);
	virtual ~Gt2DActor(void);

	void AddGtSequence(guint32 uiID, Gt2DSequence* sequence);
	bool GetGtSequence(guint32 uiID, Gt2DSequence*& sequence);
	void RemoveGtSequence(guint32 uiID);
	void RemoveSequenceWithTool(guint32 uiID);
	void ResetSequence(guint32 uiID);

	virtual gint8 GetType() {
		return OBJECT_TYPE;
	}
	virtual bool SaveData(const gchar* pcBasePath = NULL);
	virtual bool LoadData();
	virtual bool CreateData();
	virtual void SetObjectName(const gchar* pcVal);

	inline Gn2DActor* GetActor() {
		return mpsActor;
	}
	inline Gn2DMeshObject* GetRootNode() {
		return mpsActor->GetRootNode();
	}
	inline GtActorTool* GetActorTool() {
		return (GtActorTool*)mpsActor->GetActorTool();
	}

	inline Gt2DSequence* GetModifySequence() {
		return mModifySequence;
	}
	inline void SetModifySequence(Gt2DSequence* pSequence)
	{		
		mModifySequence = pSequence;
	}
	inline const gchar* GetGATFileName() {
		return mGATFileName;
	}
	inline void SetGATFileName(const gchar* val) {
		mGATFileName = val;
	}


};

GnSmartPointer(Gt2DActor);

