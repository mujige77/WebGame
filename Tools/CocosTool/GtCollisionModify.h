#pragma once
class GtCollisionModify
{
 	static const int mZrOder = 10;
protected:
	GnLayerDrawPrimitives* mpDrawLayer;
	Gn2DActorPtr mpsBasicCollisionActor;
	Gn2DMeshObjectPtr mpsBasicMeshObject;
	GnDrawPrimitivesPtr mpsDrawSequenceRect;
	bool mVisible;	

public:
	GtCollisionModify(void);
	~GtCollisionModify(void);
	static GtCollisionModify* Create(float fWidth, float fHeight);
		
	bool LoadBasicActor(const char* pcFilePath);
	void SetBasicSequenceID(guint32 uiID);

	void SetVisible(bool val, Gn2DMeshObject* pMesh = NULL);
	inline bool IsVisible() {
		return mVisible;
	}
	void SetScale(float val);
};

