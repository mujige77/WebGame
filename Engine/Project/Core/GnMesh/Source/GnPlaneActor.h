#ifndef GNPLANEMODEL_H
#define GNPLANEMODEL_H
#include "GnSequence.h"
#include "GnActorTool.h"

class GNMESH_ENTRY GnPlaneActor : public GnSmartObject
{
protected:		
	guint32 mTargetID;
	guint32 mCurrentID;
	GnSequence* mpCurrentSequence;
	GnTObjectDeleteMap<guint32, GnSequence*> mpSequences;
	GnSMElementPtr mpsRootNode;
	GnActorToolPtr mpsActorTool;

	const static guint32 NULL_ANI = GINT32_MAX;

public:
	GnPlaneActor();
	GnPlaneActor* Create(const gchar* pcActorToolFileName, GnObjectStream& stream, bool bLoadSequenceFile = true);
	GnPlaneActor* Create(GnActorTool* pActorTool, const gchar* pcActorToolPath, GnObjectStream& stream,
		bool bLoadSequenceFile = true);

	virtual ~GnPlaneActor();
	void Update(float fTime);
	
	bool SetTargetAnimation(guint32 uiID);
	void StopAnimation();

	bool LoadAllSequence(GnObjectStream& stream);
	bool AddSequence(GnActorTool::SequenceInfo* pInfo, GnObjectStream& stream, bool bLoadFile);
	GnSequence* CreateSequenceFromFile(GnObjectStream& stream, const GnSimpleString& strSequenceName);

	bool SaveAllLoadedSequence(GnObjectStream& stream);
	bool SaveSequence(GnSequence* pSequence, GnSimpleString& strFileName,  GnObjectStream* pStream);

	void ChangeSequence(guint32 uiID, GnSequence* pSequences);

	void ChangeRootNode(GnAVObject* pRootNode);

	inline bool GetSequence(guint32 uiID, GnSequence*& pSequences) {
		return mpSequences.GetAt(uiID, pSequences);
	}
	inline void RemoveSequence(guint32 uiID) {
		mpSequences.Remove(uiID, true);
	}
	inline void RemoveAllSequence() {
		mpSequences.RemoveAll(true);
	}
	inline GnSMElement* GetRootNode() {
		return mpsRootNode;
	}
	inline void SetRootNode(GnSMElement* pRootNode ) {
		mpsRootNode = pRootNode;
	}
	inline GnActorTool* GetActorTool() {
		return mpsActorTool;
	}
	inline void SetActorTool(GnActorTool* val) {
		mpsActorTool = val;
	}
protected:
	GnPlaneActor(GnActorTool* pActorTool, GnSMElement* pRootObject);
};

GnSmartPointer(GnPlaneActor);
#endif // GNPLANEMODEL_H