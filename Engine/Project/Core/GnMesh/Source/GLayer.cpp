#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GLayer.h"

void GLayer::AddChild(GnInterface* pObject)
{
	AddChild(pObject, 0 );
}

void GLayer::AddChild(GnInterface* pObject, int iZOrder)
{
	if( pObject->GetChildrenSize() == 0 ) 
	{
		addChild( pObject->GetParentUseNode(), iZOrder );
	}
	else
	{
		for ( gtuint i = 0 ; i < pObject->GetChildrenSize(); i++ )
		{
			GnInterface* child = pObject->GetChild( i );
			addChild( child->GetParentUseNode(), iZOrder++ );
		}			
	}
	mInterfaceChildren.Add( pObject );

}

void GLayer::RemoveChild(GnInterface* pObject)
{
	mInterfaceChildren.RemoveAndFill( pObject );
}

void GLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint touchPoint = touch->locationInView( touch->view() );


	for ( gtuint i = 0 ; i < mInterfaceChildren.GetSize(); i++ )
	{
		GnInterface* child = mInterfaceChildren.GetAt( i );
		child->Push( touchPoint.x, touchPoint.y );
	}
}

void GLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
//	CCSetIterator it = pTouches->begin();
//	CCTouch* touch = (CCTouch*)(*it);
//	
//	CCPoint touchPoint = touch->locationInView( touch->view() );
//	if( mBackgroundRect.ContainsPoint( (gint)touchPoint.x, (gint)touchPoint.y ) == false )
//		return;
}

void GLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint touchPoint = touch->locationInView( touch->view() );
	for ( gtuint i = 0 ; i < mInterfaceChildren.GetSize(); i++ )
	{
		GnInterface* child = mInterfaceChildren.GetAt( i );
		child->Pushup( touchPoint.x, touchPoint.y );
	}
}

void GDrawActorController::Draw()
{
	Gn2DAVData* avData = mpController->GetMesh()->GetAVData();
	if( avData == NULL )
		return;
	
	GnColorA tempColor = mColor;
	
	for( gtuint i = 0 ; i < avData->GetCollisionCount() ; i++ )
	{
		GnColorA color[Gg2DCollision::COLLISION_MAX] =
		{
			GnColorA( 255, 255, 0, 1 ),
			GnColorA( 255, 0, 0, 1 )
		};		
		Gn2DAVData::CollisionRect drawRect = avData->GetCollisionRect( i );
		mColor = color[drawRect.mType];
		DrawRect( drawRect.mRect );
	}
	
	Gn2DSequence* attackSequence = NULL;
	GnVerify( mpController->GetActor()->GetSequence( 3, attackSequence ) );
	Gn2DAVData* avDataAttack = attackSequence->GetAVData();
	if( avDataAttack->GetCollisionCount() > 1 )
	{
		avDataAttack->Move( mpController->GetMesh()->GetOriginalPosition() );
		
		if( mpController->GetMesh()->GetFlipX() )
		{
			avDataAttack->FlipX( true, mpController->GetMesh()->GetOriginalPosition().x );		
		}
		
		mColor = GnColorA( 0, 0, 255, 1 );	
		Gn2DAVData::CollisionRect attackRect = avDataAttack->GetCollisionRect( 1 );	
		DrawRect( attackRect.mRect );
	}
	
	
	float temp = mThickness;
	mThickness = 5;
	
	mColor = GnColorA( 0, 255, 255, 1 );
	GnVector2 point = avData->GetImageCenter();
	point += mpController->GetMesh()->GetPosition();
	DrawPoint( point );
	
	mColor = GnColorA( 0, 0, 255, 1 );		
	mThickness = temp;

	
	mColor = tempColor;
}