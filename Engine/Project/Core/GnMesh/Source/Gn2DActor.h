#ifndef GNPLANEMODEL_H
#define GNPLANEMODEL_H
#include "Gn2DSequence.h"
#include "GnActorTool.h"

class GNMESH_ENTRY Gn2DActor : public GnSmartObject
{
	const static guint32 NULL_ANI = GINT32_MAX;
protected:
	guint32 mTargetID;
	guint32 mCurrentID;
	Gn2DSequence* mpCurrentSequence;
	GnTObjectDeleteMap<guint32, Gn2DSequence*> mpSequences;
	Gn2DMeshObjectPtr mpsRootNode;
	GnActorToolPtr mpsActorTool;

public:
	Gn2DActor();
	static Gn2DActor* Create(const gchar* pcActorToolFileName, GnObjectStream& stream
		, bool bLoadSequenceFile = true);
	static Gn2DActor* Create(GnActorTool* pActorTool, GnObjectStream& stream
		, bool bLoadSequenceFile = true);

	virtual ~Gn2DActor();
	void Update(float fDeltaTime);
	
	bool SetTargetAnimation(guint32 uiID);
	void StopAnimation();

	bool LoadAllSequence(GnObjectStream& stream);
	bool LoadSequence(guint32 uiID);
	bool AddSequence(GnActorTool::SequenceInfo* pInfo, GnObjectStream& stream, bool bLoadFile);
	Gn2DSequence* CreateSequenceFromFile(GnObjectStream& stream, guint32  uiID);

	bool SaveAllLoadedSequence(GnObjectStream& stream);
	bool SaveSequence(Gn2DSequence* pSequence, GnSimpleString& strFileName,  GnObjectStream* pStream);

	void ChangeSequence(guint32 uiID, Gn2DSequence* pSequences);

	void ChangeRootNode(GnObjectForm* pRootNode);

	inline bool GetSequence(guint32 uiID, Gn2DSequence*& pSequences) {
		return mpSequences.GetAt(uiID, pSequences);
	}
	inline void RemoveSequence(guint32 uiID) {
		StopAnimation();
		mpSequences.Remove(uiID, true);
	}
	inline void RemoveAllSequence() {
		StopAnimation();
		mpSequences.RemoveAll(true);
	}
	inline Gn2DMeshObject* GetRootNode() {
		return mpsRootNode;
	}
	inline void SetRootNode(Gn2DMeshObject* pRootNode ) {
		mpsRootNode = pRootNode;
	}
	inline GnActorTool* GetActorTool() {
		return mpsActorTool;
	}
	inline void SetActorTool(GnActorTool* val) {
		mpsActorTool = val;
	}
protected:
	Gn2DActor(GnActorTool* pActorTool, Gn2DMeshObject* pRootObject);
};

GnSmartPointer(Gn2DActor);
#endif // GNPLANEMODEL_H