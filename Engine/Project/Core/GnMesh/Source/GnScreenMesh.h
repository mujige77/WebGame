#ifndef GNSCREENMESH_H
#define GNSCREENMESH_H

#include "GnMesh.h"


class GNMESH_ENTRY GnScreenMesh : public GnMesh
{
	GnDeclareRTTI;
	GnDeclareFlags(guint8);
	GnDeclareStream;
public:
	enum Streamflags
	{
		VALID_MASK = 0x00001,
		USENORMAL_MASK = 0x00002,
		USECOLOR_MASK = 0x00004,
	};

protected:
	guint mBackBufferWidth;
	guint mBackBufferHeight;
	guint32 mTextureSetCount;

public:	
	virtual ~GnScreenMesh(){};

	static GnScreenMesh* CreateScreenMesh(guint32 numVertex, bool bWantNormals, bool bWantColors, guint32 uiNumTextureSets);

	void Insert(guint32 numVertex = 4);
	void SetRectangle(gint32 iPolygon, float fLeft, float fTop, float fWidth, float fHeight);
	void SetTexture(gtuint uiTextureset, GnFRect& rect);
	void SetColor(GnColorA& changeColor);

	GnVector3* LockVertexStream(guint8 uiLockMask);
	void* LockColorStream(guint8 uiLockMask);
	GnVector2* LockTextureStream(gtuint uiSet, guint8 uiLockMask);
	GnVector3* LockNormalStream(guint8 uiLockMask);

	void UnlockVertexStream(guint8 uiLockMask);
	void UnlockColorStream(guint8 uiLockMask);
	void UnlockTextureStream(gtuint uiSet, guint8 uiLockMask);
	void UnlockNormalStream(guint8 uiLockMask);

	virtual void RnderObject(GnRenderer* pRenderer);

	inline GnDataStream* GetVertexStream()
	{
		return mpMeshData->GetDataStream(GnDataStream::POSTION_STREAM);
	}

	inline GnDataStream* GetColorStream()
	{
		return mpMeshData->GetDataStream(GnDataStream::COLOR_STREAM);
	}

	inline GnDataStream* GetTextureStream(gtuint uiSet)
	{
		return mpMeshData->GetDataStream(GnDataStream::TEXTURE_STREAM, uiSet);
	}

	inline GnDataStream* GetNormalStream()
	{
		return mpMeshData->GetDataStream(GnDataStream::NORMAL_STREAM);
	}

	inline bool IsValid(){ return GetBit(VALID_MASK); }
	inline void SetValid(bool bValue) { SetBit(bValue, VALID_MASK); }
	inline bool UseNormal(){ return GetBit(USENORMAL_MASK); }
	inline void SetUseNormal(bool bValue) { SetBit(bValue, USENORMAL_MASK); }
	inline bool UseColor(){ return GetBit(USECOLOR_MASK); }
	inline void SetUseColor(bool bValue) { SetBit(bValue, USECOLOR_MASK); }
	

protected:
	GnScreenMesh();
	GnScreenMesh(guint32 numVertex, bool bWantNormals, bool bWantColors, guint32 uiNumTextureSets);
};
GnSmartPointer( GnScreenMesh );

#endif // GNSCREENMESH_H