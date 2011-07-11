#ifndef __HiroCat__GLayer__
#define __HiroCat__GLayer__
		
class GLayer : public CCLayer
{
protected:
	GnTObjectArray<GnInterfacePtr> mInterfaceChildren;
	
public:
	void AddChild(GnInterface* pObject);
	void AddChild(GnInterface* pObject, int iZOrder);
	void RemoveChild(GnInterface* pObject);
	
public:
	virtual inline void MoveLayer(float fDeltaX, float fDeltaY){};
	
public:
	inline void AddChild(Gn2DMeshObject* pObject) {
		addChild( pObject->GetMesh() );
	}
	inline void AddChild(Gn2DMeshObject* pObject, int iZOrder) {
		addChild( pObject->GetMesh(), iZOrder );
	}
	inline void AddChild(Gn2DMeshObject* pObject, int iZOrder, int iTag) {
		addChild( pObject->GetMesh(), iZOrder, iTag );
	}
	inline void RemoveChild(Gn2DMeshObject* pObject) {
		removeChild( pObject->GetMesh(), true );
	}	
	inline void SetUIPoint(CCMenuItemImage* pItem, float fPointX, float fPointY)
	{
		CCSize size = pItem->getContentSize();
		size.width /= 2;
		size.height /= 2;
		pItem->setPosition( CCPointMake(fPointX + size.width, GetGameState()->GetGameHeight() - fPointY - size.height) );	
	}
	
protected:
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
};

class GActorController;
class GDrawActorController : public GnDrawPrimitives
{
	GnDeclareFlags(gushort);
	
protected:
	GActorController* mpController;

public:
	void Draw();
	void SetController(GActorController* pCtlr) {
		mpController = pCtlr;
	}
};

class GnSingleDrawPrimitiveslayer : public GLayer
{
public:
	GDrawActorController mpsDrawObject;
	GDrawActorController* GetDrawObject() {
		return &mpsDrawObject;
	}
	void draw()
	{
		GLayer::draw();
		mpsDrawObject.Draw();
	};
};

class GnExtraDataPrimitivesLayer : public GnDrawPrimitives
{
protected:
	Gn2DMeshObject* mpMeshObject;

public:
	void Draw();
	void SetMeshObject(Gn2DMeshObject* pMeshObject) {
		mpMeshObject = pMeshObject;
	}
};
#endif
