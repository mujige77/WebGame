#ifndef GTACTOROBJECT_H
#define GTACTOROBJECT_H
#include "GtObject.h"
#include "GtSequenceInfo.h"

class GtActorObject : public GtObject
{
	GnDeclareRTTI;
public:
	const static  gint8 GTPLANEACTORTYPE = GtObject::GTOBJECTTYPE + 1;

protected:
	GnPlaneActorPtr mpsActor;	
	GnSimpleString mGATFileName;
	GnTObjectArray<GtSequenceInfoPtr> mSequences;
	GtSequenceInfo* mpCurrentSequence;
	GnIRect mMeshRect;

public:
	GtActorObject();
	virtual ~GtActorObject();

	GtSequenceInfo* GetSequenceInfo(const gchar* pcSequenceName);
	
	bool AddSequenceInfo(GtSequenceInfo* pInfo);
	void RemvoeSequenceInfo(const gchar* pcSequenceName);

	GnPlaneActor* CreateActorFromExistData();	
	GnActorTool* CreateActorTool();
	GnPlaneActor* ResetSequence();
	bool SaveStream();
	bool LoadStream();

	void MakeRenderDisplayRect() 
	{
		GnSMElement* meshElement = (GnSMElement*)mpsRootNode->GetObjectByName( "Actor" );
		GnAssert( mpsRootNode );
		GnAssert( meshElement );
		meshElement->SetDisplayRect( MakeRenderDisplayRect( mMeshRect ) );
		meshElement->UpdateRect( true );
	}
	void MakeObjectDisplayRect()
	{
		GnSMElement* meshElement = (GnSMElement*)mpsRootNode->GetObjectByName( "Actor" );
		meshElement->SetDisplayRect( mMeshRect );
		meshElement->UpdateRect( true );
	}
	GnIRect MakeRenderDisplayRect(GnIRect objectRect);
	

	virtual void ChanageScale(gint32 iX, gint32 iY);
	virtual GnVector2 GetScale();
	virtual bool EnableLoadGnObject();

	virtual gint8 GetType() { 
		return GTPLANEACTORTYPE;
	}
	virtual void Update(float fTime);

	inline GnPlaneActor* GetActor() {
		return mpsActor;
	}
	inline void SetActor( GnPlaneActor* pActor ) {
		mpsActor = pActor;
	}

	inline gtuint GetLoadedSequenceCount() {
		return mSequences.GetSize();
	}
	GtSequenceInfo* GetSequenceInfo(gtuint uiIndex){
		return mSequences.GetAt( uiIndex );
	}
	inline const gchar* GetSequenceFileName(gtuint uiIndex) {
		GtSequenceInfo* info = mSequences.GetAt( uiIndex );
		return info->GetFileName();
	}
	inline const gchar* GetSequenceName( gtuint uiIndex ) {
		GtSequenceInfo* info = mSequences.GetAt( uiIndex );
		return info->GetName();
	}

	inline GtSequenceInfo* GetCurrentSequenceInfo() {
		return mpCurrentSequence;
	}
	inline void SetCurrentSequenceInfo(GtSequenceInfo* val) {
		mpCurrentSequence = val;
	}
	inline GnSimpleString& GetGATFileName() {
		return mGATFileName;
	}
	inline void SetGATFileName(const gchar* val) {
		mGATFileName = val;
	}

	//inline void SetSequenceNames(gtuint uiIndex, const gchar* pcName , const gchar* pcFileName) {
	//	GnSimpleString name = pcName;
	//	SetSequenceName( uiIndex, name );
	//	name = pcFileName;
	//	SetSequenceFileName( uiIndex, name );
	//}

protected:
	//inline void SetSequenceFileName(gtuint uiIndex, GnSimpleString strFileName) {
	//	GnAssert( uiIndex < mSequenceFileNames.GetAllocatedSize() );
	//	mSequenceFileNames.SetAt( uiIndex, strFileName );
	//}

	//inline void SetSequenceName(gtuint uiIndex, GnSimpleString strName) {
	//	GnAssert( uiIndex < mSequenceNames.GetAllocatedSize() );
	//	mSequenceNames.SetAt( uiIndex, strName );
	//}
	void CreateSequenceFromExistData();
};

GnSmartPointer( GtActorObject );

#endif // GTACTOROBJECT_H
