#ifndef GNSMELEMENT_H
#define GNSMELEMENT_H

GnSmartPointer(GnSMElement);
class GNMESH_ENTRY GnSMElement : public GnObjectForm
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
	GnFRect mMeshRect;
	GnIRect mDisplayRect;
	GnScreenMeshPtr mpsMesh;	
	GnSMElement* mpParent;
	
public:
	GnSMElement();
	virtual ~GnSMElement(){};	
	void SetMesh(GnScreenMesh* pMesh, GnIRect iRect);
	void SetMesh(GnScreenMesh* pMesh);
	void SetDisplayRect(GnIRect& val);
	void AttachParent(GnSMElement* pParent);

	virtual void Update(float fTime);
	virtual void UpdateRect(bool bUpdateMeshData);
	virtual GnSMElementPtr DetachChild(GnSMElement* pChild){ return NULL; };
	virtual GnObjectForm* GetObjectByName(const GnSimpleString& kName);

	inline GnScreenMesh* GetMesh() {
		return mpsMesh;
	}

	inline void DetachParent() { 
		mpParent = NULL;
	}
	inline GnIRect& GetDisplayRect() {
		return mDisplayRect;
	}	
	inline bool IsVisible() {
		return GetBit( VISIBLE_MASK );
	}
	inline void SetVisible(bool val) {
		SetBit( VISIBLE_MASK, val );
	}
};
#endif // GNSMELEMENT_H
