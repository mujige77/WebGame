#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GLayer.h"

GnInterfacePtr GLayer::smpModalInterface = NULL;

void GLayer::SetModalState(GnInterface* pModalInterface)
{
	smpModalInterface = pModalInterface;
}

GnInterface* GLayer::GetModalState()
{
	return smpModalInterface;
}

void GLayer::AddChild(GnInterface* pObject)
{
	AddChild(pObject, 0 );
}

void GLayer::AddChild(GnInterface* pObject, int iZOrder)
{
//	if( pObject->GetChildrenSize() == 0 ) 
//	{
		addChild( pObject->GetParentUseNode(), iZOrder );
//	}
//	else
//	{
//		
//		for ( gtuint i = 0 ; i < pObject->GetChildrenSize(); i++ )
//		{
//			GnInterface* child = pObject->GetChild( i );
//			addChild( child->GetParentUseNode(), iZOrder++ );
//		}
//	}
	mInterfaceChildren.Add( pObject );

}

void GLayer::RemoveChild(GnInterface* pObject)
{
	mInterfaceChildren.RemoveAndFill( pObject );
}

void GLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{	
	if( smpModalInterface )
	{
		GnInterfacePtr ptr = smpModalInterface;
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
		{
			CCTouch* touch = (CCTouch*)(*it);
			CCPoint touchPoint = touch->locationInView( touch->view() );
			ptr->Push( touchPoint.x, touchPoint.y );
		}
		return;
	}
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
	{
		CCTouch* touch = (CCTouch*)(*it);
		CCPoint touchPoint = touch->locationInView( touch->view() );
		for ( gtuint i = 0 ; i < mInterfaceChildren.GetSize(); i++ )
		{
			GnInterface* child = mInterfaceChildren.GetAt( i );
			if( child->Push( touchPoint.x, touchPoint.y ) )
			{
				break;
			}
		}
	}
}

void GLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	if( smpModalInterface )
	{
		GnInterfacePtr ptr = smpModalInterface;
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
		{
			CCTouch* touch = (CCTouch*)(*it);
			CCPoint touchPoint = touch->locationInView( touch->view() );
			ptr->PushMove( touchPoint.x, touchPoint.y );
		}
		return;
	}
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
	{
		CCTouch* touch = (CCTouch*)(*it);
		CCPoint touchPoint = touch->locationInView( touch->view() );
		for ( gtuint i = 0 ; i < mInterfaceChildren.GetSize(); i++ )
		{
			GnInterface* child = mInterfaceChildren.GetAt( i );
			child->PushMove( touchPoint.x, touchPoint.y );
		}
	}
}

void GLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	if( smpModalInterface )
	{
		GnInterfacePtr ptr = smpModalInterface;
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
		{
			CCTouch* touch = (CCTouch*)(*it);
			CCPoint touchPoint = touch->locationInView( touch->view() );
			ptr->PushUp( touchPoint.x, touchPoint.y );
		}
		return;
	}
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it )
	{
		CCTouch* touch = (CCTouch*)(*it);
		CCPoint touchPoint = touch->locationInView( touch->view() );
		for ( gtuint i = 0 ; i < mInterfaceChildren.GetSize(); i++ )
		{
			GnInterface* child = mInterfaceChildren.GetAt( i );
			if( child->PushUp( touchPoint.x, touchPoint.y ) )
				break;
		}
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
			GnColorA( 155, 155, 0, 1 )
		};		
		Gn2DAVData::CollisionRect drawRect = avData->GetCollisionRect( i );
		mColor = color[drawRect.mType];
		DrawRect( drawRect.mRect );
	}
	
	Gn2DSequence* attackSequence = NULL;
	if( mpController->GetActor()->GetSequence( 3, attackSequence ) == false )
	{
		GnLogA( "Failed Load AttackSquence");
		return;
	}
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
		//float scale = attackRect.mRect.GetWidth() * GetGameState()->GetGameScale();
		//attackRect.mRect.SetWidth( scale );
		//scale = attackRect.mRect.GetHeight() * GetGameState()->GetGameScale();
		//attackRect.mRect.SetHeight( scale  );		
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

void GDrawFarAttack::Draw()
{
	mColor = GnColorA( 255, 0, 0, 1 );	
	DrawRect( mpFarAttack->GetAttackRect() );
}

void GnExtraDataPrimitivesLayer::Draw()
{
	if( mpMeshObject == NULL )
		return;

	for( gtuint i = 0; i < mpMeshObject->GetExtraDataSize(); i++  )
	{
		GnVector2ExtraData* vec2Data = GnDynamicCast(GnVector2ExtraData, mpMeshObject->GetExtraData( i ));
		if( vec2Data )
		{
			GnVector2 point = vec2Data->GetValueVector2();
			point += mpMeshObject->GetPosition();
			DrawPoint( point );
		}
	}
}

