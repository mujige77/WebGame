#include "GnMeshPCH.h"
#include "GnScreenMesh.h"
#include "GnFactoryManager.h"

GnImplementRTTI(GnScreenMesh, GnMesh);

GnScreenMesh* GnScreenMesh::CreateScreenMesh(guint32 numVertex, bool bWantNormals, bool bWantColors, guint32 uiNumTextureSets)
{
	return GnNew GnScreenMesh( numVertex, bWantNormals, bWantColors, uiNumTextureSets );
}

GnScreenMesh::GnScreenMesh() : GnMesh( GnNew Gn2DTransform )
{
	SetUseColor( false );
	SetUseNormal( false );
	mNumVertex = 0;
	mTextureSetCount = 0;
}



GnScreenMesh::GnScreenMesh(guint32 numVertex, bool bWantNormals, bool bWantColors, guint32 uiNumTextureSets) 
	: GnMesh(GnNew Gn2DTransform)
{
	mNumVertex = numVertex;
	mpMeshData = GnFactoryManager::CreateMeshData();
	SetPrimitiveType( PRIMITIVE_TRISTRIPS );
	AddDataStream( GnDataStream::POSTION_STREAM, mNumVertex );

	SetUseColor( bWantColors );
	if ( bWantColors)
		AddDataStream( GnDataStream::COLOR_STREAM, mNumVertex );

	SetUseNormal( bWantNormals );
	if( bWantNormals )
		AddDataStream( GnDataStream::NORMAL_STREAM, mNumVertex );

	mTextureSetCount = uiNumTextureSets;
	if( uiNumTextureSets > 0 )
	{
		for ( gtuint numTexture = 0 ; numTexture < uiNumTextureSets ; numTexture++ )
		{
			AddDataStream( GnDataStream::TEXTURE_STREAM, mNumVertex );
		}
	}
}

void GnScreenMesh::Insert(guint32 numVertex)
{
	mNumVertex += numVertex;
	SetValid( true );
	
	GnDataStream* dataStream = GetVertexStream();
	dataStream->Resize( numVertex );

	if( UseColor() )
	{
		dataStream = GetColorStream();
		dataStream->Resize( numVertex );
	}

	for ( gtuint i = 0 ; i < mTextureSetCount ; i++ )
	{
		dataStream = GetTextureStream( i );
		dataStream->Resize( numVertex );
	}

	if( UseNormal() )
	{
		dataStream = GetNormalStream();
		dataStream->Resize( numVertex );
	}
}

void GnScreenMesh::SetRectangle(gint32 iPolygon, float fLeft, float fTop, float fRight, float fBottom)
{
	if( IsValid() == false )
		return;

	GnVector3* pVertex = LockVertexStream( GnDataStream::LOCK_WRITE );

	gtuint i = 0;
	pVertex[i].x = fLeft;
	pVertex[i].y = fTop;
	pVertex[i++].z = 0;	

	pVertex[i].x = fRight;
	pVertex[i].y = fTop;
	pVertex[i++].z = 0;

	pVertex[i].x = fLeft;
	pVertex[i].y = fBottom;
	pVertex[i++].z = 0;	
	
	pVertex[i].x = fRight;
	pVertex[i].y = fBottom;
	pVertex[i].z = 0;
	
	UnlockVertexStream( GnDataStream::LOCK_WRITE );
}


void GnScreenMesh::SetTexture(gtuint uiTextureset, GnFRect& rect)
{
	if( mTextureSetCount <= uiTextureset )
		return;

	GnVector2* crood = LockTextureStream( uiTextureset, GnDataStream::LOCK_WRITE );

	gtuint i = 0;
	crood[i].x = rect.left;
	crood[i].y = rect.top;
	++i;

	crood[i].x = rect.right;
	crood[i].y = rect.top;
	++i;

	crood[i].x = rect.left;
	crood[i].y = rect.bottom;
	++i;

	crood[i].x = rect.right;
	crood[i].y = rect.bottom;
	++i;

	UnlockTextureStream( uiTextureset, GnDataStream::LOCK_WRITE );

}

void GnScreenMesh::SetColor(GnColorA& changeColor)
{
	if( UseColor() == false )
		return;

	DWORD* color = (DWORD*)LockColorStream( GnDataStream::LOCK_WRITE );
	for ( gtuint i = 0 ; i < mNumVertex ; i++ )
	{		
		color[i] = ((DWORD)((((255)&0xff)<<24)|(((255)&0xff)<<16)|(((0)&0xff)<<8)|((0)&0xff)));
		color[i] = changeColor.GetRGBA();
	}
	UnlockColorStream( GnDataStream::LOCK_WRITE );
}

GnVector3* GnScreenMesh::LockVertexStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetVertexStream();
	if( dataStream == NULL )
		return NULL;
	
	return (GnVector3*)dataStream->Lock( uiLockMask );
}

void* GnScreenMesh::LockColorStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetColorStream();
	if( dataStream == NULL )
		return NULL;

	return dataStream->Lock( uiLockMask );
}

GnVector2* GnScreenMesh::LockTextureStream(gtuint uiSet, guint8 uiLockMask)
{
	GnDataStream* dataStream = GetTextureStream( uiSet );
	if( dataStream == NULL )
		return NULL;

	return (GnVector2*)dataStream->Lock( uiLockMask );
}

GnVector3* GnScreenMesh::LockNormalStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetNormalStream();
	if( dataStream == NULL )
		return NULL;

	return (GnVector3*)dataStream->Lock( uiLockMask );
}

void GnScreenMesh::UnlockVertexStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetVertexStream();
	if( dataStream == NULL )
		return;

	dataStream->Unlock( uiLockMask );
}

void GnScreenMesh::UnlockColorStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetColorStream();
	if( dataStream == NULL )
		return;

	dataStream->Unlock( uiLockMask );
}

void GnScreenMesh::UnlockTextureStream(gtuint uiSet, guint8 uiLockMask)
{
	GnDataStream* dataStream = GetTextureStream(uiSet);
	if( dataStream == NULL )
		return;

	dataStream->Unlock( uiLockMask );
}

void GnScreenMesh::UnlockNormalStream(guint8 uiLockMask)
{
	GnDataStream* dataStream = GetNormalStream();
	if( dataStream == NULL )
		return;

	dataStream->Unlock( uiLockMask );
}


GnImplementCreateObject(GnScreenMesh);
void GnScreenMesh::LoadStream(GnObjectStream* pStream)
{
	GnMesh::LoadStream( pStream );
}

void GnScreenMesh::LinkObject(GnObjectStream* pStream)
{
	GnMesh::LinkObject( pStream );
 
}

void GnScreenMesh::SaveStream(GnObjectStream* pStream)
{
	GnMesh::SaveStream( pStream );
}

void GnScreenMesh::RegisterSaveObject(GnObjectStream* pStream)
{
	GnMesh::RegisterSaveObject( pStream );
}


void GnScreenMesh::RnderObject(GnRenderer* pRenderer)
{
	pRenderer->RenderScreenMesh(this);
	GnLogA( "RnderObject");
}