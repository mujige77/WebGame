#ifndef GNSMELEMENT_H
#define GNSMELEMENT_H
#include "Gn2DAVObject.h"

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
	
public:
	Gn2DMeshObject();
	virtual ~Gn2DMeshObject();
	void SetMesh(GnReal2DMesh* pMesh);
	void SetAVData(Gn2DAVData* val);
	void AttachParent(Gn2DMeshObject* pParent);

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

	inline GnVector2 GetPosition() {
		CCPoint position = mpMesh->getPosition();
		return GnVector2( position.x, position.y );
	}
	inline void SetPosition(GnVector2 val) {
		mpMesh->setPosition( CCPointMake(val.x, val.y) );;
	}
};
#endif // GNSMELEMENT_H
