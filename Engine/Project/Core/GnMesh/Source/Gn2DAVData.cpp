#include "GnMeshPCH.h"
#include "Gn2DAVData.h"

GnImplementRTTI( Gn2DAVData, GnObject );

Gn2DAVData::Gn2DAVData() : mAnchorPoint(0.0f, 0.0f), mImageCenter(0.0f, 0.0f)
{
	SetMeshStream( true );
	//SetExistCollision( false );
	//SetExistAttack( false );
}


GnImplementCreateObject(Gn2DAVData);
void Gn2DAVData::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );

	if( pStream->GetFileVersion() != GnStream::GetVersion( 1, 0, 0, 0 ) )
	{
		mImageCenter.LoadStream( pStream );
		mImageCenter *= GetGameState()->GetGameScale();
	}
	mAnchorPoint.LoadStream( pStream );
	//mAnchorPoint *= GetGameState()->GetGameScale();

	guint32 size = 0;
	pStream->LoadStream( size );
	if( size )
	{
		mCollisionRects.SetSize( size );
		mOriginalCollisionRects.SetSize( size );
		for( gtuint i = 0 ; i < mCollisionRects.GetAllocatedSize() ; i++ )
		{
			CollisionRect rect;
			pStream->LoadStream( rect.mType );
			if( pStream->GetFileVersion() == GnStream::GetVersion( 1, 0, 0, 0 ) )
			{
				GnIRect iRect;
				iRect.LoadStream( pStream );
				rect.mRect = GnFRect( (float)iRect.left, (float)iRect.top, (float)iRect.right
					, (float)iRect.bottom );
			}
			else
			{
				rect.mRect.LoadStream( pStream );
			}
			SetRectScale(rect);

			SetCollisionRect( i, rect );
		}
	}	
}

void Gn2DAVData::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
}

void Gn2DAVData::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	mImageCenter.SaveStream( pStream );
	mAnchorPoint.SaveStream( pStream );

	guint32 size = mCollisionRects.GetSize();
	pStream->SaveStream( size );
	for( gtuint i = 0 ; i < mCollisionRects.GetSize() ; i++ )
	{
		CollisionRect& rect = mCollisionRects.GetAt( i );
		pStream->SaveStream( rect.mType );
		rect.mRect.SaveStream( pStream );
	}
}

void Gn2DAVData::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );
}

void Gn2DAVData::Move(GnVector2& movePoint)
{
	for( gtuint i = 0 ; i < mCollisionRects.GetSize() ; i++ )
	{
		CollisionRect rect = mOriginalCollisionRects.GetAt( i );
		rect.mRect.MoveX( movePoint.x );
		rect.mRect.MoveY( movePoint.y );
		mCollisionRects.SetAt( i, rect );
	}
}

void Gn2DAVData::FlipX(bool bFlip, float postionX)
{
	if( bFlip )
	{	
		for( gtuint i = 0 ; i < mCollisionRects.GetSize() ; i++ )
		{
			CollisionRect& baseRect =  mOriginalCollisionRects.GetAt( 0 );
			CollisionRect& currentRect =  mCollisionRects.GetAt( i );
			CollisionRect rect = mOriginalCollisionRects.GetAt( i );
			float rectAnchor =  baseRect.mRect.left + baseRect.mRect.right;
			rect.mRect = GnFRect( postionX - rect.mRect.left + rectAnchor, currentRect.mRect.top
				, postionX - rect.mRect.right + rectAnchor, currentRect.mRect.bottom );
			mCollisionRects.SetAt( i, rect );
		}
	}
	else
	{
		for( gtuint i = 0 ; i < mCollisionRects.GetSize() ; i++ )
		{
			CollisionRect& currentRect =  mCollisionRects.GetAt( i );
			CollisionRect rect = mOriginalCollisionRects.GetAt( i );
			rect.mRect = GnFRect( rect.mRect.left + postionX, currentRect.mRect.top
				, rect.mRect.right + postionX, currentRect.mRect.bottom );
			mCollisionRects.SetAt( i, rect );
		}
	}
}

void Gn2DAVData::SetRectScale(CollisionRect &rect)
{
	float scale = rect.mRect.GetWidth() * GetGameState()->GetGameScale();
	rect.mRect.SetWidth( scale );
	scale = rect.mRect.GetHeight() * GetGameState()->GetGameScale();
	rect.mRect.SetHeight( scale );
	float move = ( rect.mRect.left * GetGameState()->GetGameScale() ) - rect.mRect.left;
	rect.mRect.MoveX( move );
	move = ( rect.mRect.top * GetGameState()->GetGameScale() ) - rect.mRect.top;
	rect.mRect.MoveY( move );
}