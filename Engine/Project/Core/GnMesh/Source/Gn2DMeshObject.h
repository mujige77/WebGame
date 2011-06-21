#ifndef GNSMELEMENT_H
#define GNSMELEMENT_H

GnSmartPointer(Gn2DMeshObject);
class GNMESH_ENTRY Gn2DMeshObject : public GnObjectForm
{
	GnDeclareRTTI;
	GnDeclareFlags( guint16 );
	GnDeclareStream;
public:
	enum eSMFlag
	{
		VISIBLE_MASK = 0x0001,
	};

protected:
	Gn2DMeshObject* mpParent;	
	GnReal2DMesh*mpMesh;
	Gn2DAVDataPtr mpsAVData;
	GnVector2 mOriginalPosition;

public:	
	Gn2DMeshObject();
	Gn2DMeshObject(GnReal2DMesh* pMesh);
	virtual ~Gn2DMeshObject();

	static Gn2DMeshObject* CreateFromTextureFile(const gchar* pcFilePath);

	void SetMesh(GnReal2DMesh* pMesh);
	void SetAVData(Gn2DAVData* val);
	void AttachParent(Gn2DMeshObject* pParent);
	void SetScale(float val);
	void SetPosition(GnVector2 val);
	void SetFlipX(bool val);

	virtual void Update(float fTime);
	virtual Gn2DMeshObjectPtr DetachChild(Gn2DMeshObject* pChild){ return NULL; };
	virtual GnObjectForm* GetObjectByName(const GnSimpleString& kName);

	inline GnReal2DMesh* GetMesh() {
		return mpMesh;
	}
	inline void DetachParent() { 
		mpParent = NULL;
	}
	inline void StopAllAnimation() {
		mpMesh->stopAllActions();
	}
	inline Gn2DAVData* GetAVData() {
		return mpsAVData;
	}	
	inline bool IsVisible() {
		return GetBit( VISIBLE_MASK );
	}
	inline void SetVisible(bool val) {
		SetBit( val, VISIBLE_MASK );
	}
	inline GnVector2& GetOriginalPosition() {
		//if( mpsAVData )
		//{
		//	if( mpMesh->isFlipX() )
		//		mOriginalPosition = GetPosition() + GetAVData()->GetAnchorPoint();
		//	else
		//		mOriginalPosition = GetPosition() - GetAVData()->GetAnchorPoint();
		//}
		return mOriginalPosition;
	}
	inline void SetOriginalPosition(GnVector2& val) {
		mOriginalPosition = val;
	}
	inline GnVector2& GetPosition() {
		//CCPoint position = mpMesh->getPosition();
		//return GnVector2( position.x, position.y );
		return mOriginalPosition;
	}
	inline float GetAlpha() {
		return mpMesh->getOpacity();
	}
	inline void SetAlpha(guint8 val) {
		mpMesh->setOpacity( val );
	}
	inline float GetScale() {
		return mpMesh->getScale();
	}
	inline bool GetFlipX() {
		return mpMesh->isFlipX();
	}
};
#endif // GNSMELEMENT_H
