#pragma once
class GcDrawObjectManager
{
private:
	Gt2DActorPtr mpsActor;
	Gt2DObjectPtr mps2DObject;
	Gt2DSequencePtr mpsSequence;	
	GnLayerDrawPrimitives* mpDrawLayer;
	GnDrawPrimitivesPtr mpsActorExtraDraw;
	GnDrawPrimitivesPtr mps2DObjectExtraDraw;

public:
	GcDrawObjectManager(void);
	~GcDrawObjectManager(void);
	void Update(float fDeltaTime);
	void SelectActor(GtObject* pObject);
	void Select2DObject(GtObject* pObject);	
	void SetObjectPosition(GnVector2 cPosition);
	void SetObjectCenter(bool bCenter);
	void Reset();
	bool SelectSequence(GnActorTool::SequenceInfo* pSecuenceInfo);
	void AttachEffectToActor();
public:
	inline Gt2DActor* GetActor() {
		return mpsActor;
	}
	inline void SetActor(Gt2DActor* val) {
		mpsActor = val;
	}
	inline Gt2DObject* Get2DObject() {
		return mps2DObject;
	}
	inline void Set2DObject(Gt2DObject* val) {
		mps2DObject = val;
	}
	inline Gt2DSequence* GetSequence() {
		return mpsSequence;
	}
	inline void SetSequence(Gt2DSequence* val) {
		mpsSequence = val;
	}
};

