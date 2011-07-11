#ifndef GNOBJECTFORM_H
#define GNOBJECTFORM_H
#include "GnTimeController.h"
class GNMAIN_ENTRY GnObjectForm : public GnObject
{
	GnDeclareRTTI;
	GnDeclareAbstractStream;
private:
	GnSimpleString mName;
	GnTPrimitiveArray<GnExtraData*> mExtraDatas;
	GnTimeControllerPtr mpsControls;

public:
	GnObjectForm();
	virtual ~GnObjectForm();

public:
	virtual void Update(float fDeltaTime);
	virtual GnObjectForm* GetObjectByName(const GnSimpleString& kName);
	void SetTimeController(GnTimeController* pCtlr);

public:
	inline GnSimpleString& GetName() {
		return mName;
	}
	inline void SetName(const gchar* val) {
		mName = val;
	}
	inline GnExtraData* GetExtraData(gtuint uiIndex) {
		if( mExtraDatas.GetSize() > uiIndex )
			return mExtraDatas.GetAt( uiIndex );
		return NULL;
	}
	inline GnExtraData* GetExtraDataFromType(guint32 uiType) {
		for( gtuint i = 0 ; i < mExtraDatas.GetSize() ; i++ )
		{
			GnExtraData* extra = mExtraDatas.GetAt( i );
			if( extra->GetType() == uiType )
				return extra;
		}
		return NULL;
	}
	inline GnExtraData* GetExtraDataFromID(guint32 uiID) {
		for( gtuint i = 0 ; i < mExtraDatas.GetSize() ; i++ )
		{
			GnExtraData* extra = mExtraDatas.GetAt( i );
			if( extra->GetID() == uiID )
				return extra;
		}
		return NULL;
	}
	inline gtuint GetExtraDataSize() {
		return mExtraDatas.GetSize();
	}
	inline GnTimeController* GetTimeControllers() {
		return mpsControls;
	}
	inline void SetTimeControllers(GnTimeController* val) {
		mpsControls = val;
	}

protected:
	void RemoveTimeControllerTarget();
	// 툴 때문에 사용 하는 것임
public:
	inline GnTPrimitiveArray<GnExtraData*>* GetExtraDatas() {
		return &mExtraDatas;
	}
	inline void AddExtraData(GnExtraData* pExtra) {
		mExtraDatas.Add( pExtra );
	}
};

GnSmartPointer(GnObjectForm);

#endif // GNOBJECTFORM_H