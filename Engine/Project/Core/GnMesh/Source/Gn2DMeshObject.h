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
	GnReal2DMesh* mpMesh;
	Gn2DAVDataPtr mpsAVData;
	GnVector2 mOriginalPosition;
	GnVector2 mMeshSize;

public:		
	virtual ~Gn2DMeshObject();

	static Gn2DMeshObject* CreateFromTextureFile(const gchar* pcFilePath);
	static Gn2DMeshObject* Create(bool bUseGn2DMeshData);
	static Gn2DMeshObject* Create(const gchar* pcFilePath, bool bUseGn2DMeshData);
	static Gn2DMeshObject* CreateFullPath(const gchar* pcFullPath, bool bUseGn2DMeshData);
	
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
	inline void SetVisible(bool val)
	{
		mpMesh->setIsVisible( val );
		SetBit( val, VISIBLE_MASK );
	}
	inline GnVector2& GetOriginalPosition() {
		return mOriginalPosition;
	}
	inline void SetOriginalPosition(GnVector2& val) {
		mOriginalPosition = val;
	}
	inline GnVector2& GetPosition() {
		return mOriginalPosition;
	}
	inline GnVector2 GetPositionFromImageCenter() {
		CCPoint pos = mpMesh->getPosition();
		CCSize size = mpMesh->getContentSize();
		size.width /= 2;
		size.height /= 2;
		if( GetAVData() == NULL ) 
			return GnVector2( pos.x + size.width, pos.y + size.height );
		if( mpMesh->isFlipX() )
		{
			return GnVector2( pos.x + size.width, pos.y + size.height );;
		}

		return GnVector2( pos.x + size.width, pos.y + size.height );;
	}
	inline guchar GetAlpha() {
		return mpMesh->getOpacity();
	}
	inline void SetAlpha(float val) {
		mpMesh->setOpacity( (GLubyte)(val * 255) );
	}
	inline void SetAlpha(guchar val) {
		mpMesh->setOpacity( val );
	}
	inline void SetColor(GnColor cColor) {
		mpMesh->setColor( ccc3( (GLubyte)(cColor.r * 255), (GLubyte)(cColor.g * 255.0f)
		   , (GLubyte)(cColor.b * 255.0f) ) );
	}
	inline GnColor GetColor() {
		ccColor3B color = mpMesh->getColor();
		return GnColor( (float)color.r / 255.0f , (float)color.g / 255.0f, (float)color.b / 255.0f ) ;
	}
	inline float GetScale() {
		return mpMesh->getScale();
	}
	inline bool GetFlipX() {
		return mpMesh->isFlipX();
	}
	inline GnVector2 GetSize() {
		return mMeshSize;
	}
	inline void SetSize(GnVector2 cSize) {
		mpMesh->setContentSize( CCSizeMake( cSize.x, cSize.y ) );
		mMeshSize = cSize;
	}
	inline gint32 GetZOrder() {
		return mpMesh->getZOrder();
	}
	inline GnVector2 GetFlipCenter() {
		if( GetAVData() )
			return GetAVData()->GetImageCenter();
		return GnVector2( 0.0f, 0.0f );
	}

protected:
	Gn2DMeshObject(GnReal2DMesh* pMesh);
	void SetVectorExtraDataScale();
	void SetVectorExtraDataFlipX();
	void Create2DAVData(GnVector2 cSize);
	void SetRootMeshFromTextureAniCtlr();
};
#endif // GNSMELEMENT_H
