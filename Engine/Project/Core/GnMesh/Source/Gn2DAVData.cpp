#include "GnMeshPCH.h"
#include "Gn2DAVData.h"

GnImplementRTTI( Gn2DAVData, GnObject );

Gn2DAVData::Gn2DAVData() : mAnchorPoint(0.0f, 0.0f)
{
	SetMeshStream( true );
	//SetExistCollision( false );
	//SetExistAttack( false );
}


GnImplementCreateObject(Gn2DAVData);
void Gn2DAVData::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );

	mAnchorPoint.LoadStream( pStream );
	guint32 size = 0;
	pStream->LoadStream( size );
	if( size )
	{
		mCollisionRects.SetSize( size );
		for( gtuint i = 0 ; i < mCollisionRects.GetAllocatedSize() ; i++ )
		{
			CollisionRect rect;
			pStream->LoadStream( rect.mType );
			rect.mRect.LoadStream( pStream );

			mCollisionRects.SetAt( i, rect );
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
