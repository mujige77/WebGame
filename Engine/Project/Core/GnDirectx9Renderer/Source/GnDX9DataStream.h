#ifndef GNDX9DATASTREAMELEMENT_H
#define GNDX9DATASTREAMELEMENT_H
#include "GnDataStream.h"

// 1차 렌더링에 사용할 D3D용 버퍼(mpVBBuffer, mpIBBuffer)와 데이터 저장에 사용할 버퍼(mpLocalBuffer)를
// 따로 메모리를 할당한다... 메모리 낭비...
// 쓰레드 생각해서 다시 만들 생각 해야겠다.
class GNDIRECTX9RENDERER_ENTRY GnDX9DataStream : public GnDataStream
{
private:
	union 
	{
		LPDIRECT3DVERTEXBUFFER9 mpVBBuffer;
		LPDIRECT3DINDEXBUFFER9 mpIBBuffer;
	};

protected:
	// mpVBBuffer나 mpIBBuffer가 롹을 했을때 가져오는 임시 저장소
	void* mpLockedData;

public:
	GnDX9DataStream(const GnDataStream::eFormat format, guint32 uiCount);
	virtual ~GnDX9DataStream();

	// NiDX9LockableDataStream에서 락을 하면 어딘가에서 데이터를 셋팅할 변수를 리턴한다.
	void* MapBuffer(guint8 uiLockType, gtuint uiReadLockCount, gtuint uiWriteLockCount);
	// NiDX9LockableDataStream에서 언락하면 버퍼를 되돌린다.
	void UnmapBuffer(guint8 uiLockType, gtuint uiReadLockCount, gtuint uiWriteLockCount);

	bool GetD3DDeclType(D3DDECLTYPE& outType);
	bool GetD3DDeclUsage(D3DDECLUSAGE& outUsage);

	void MakeBuffer();

	const LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer()
	{
		return mpVBBuffer;
	}
		
	virtual gtuint GetStride(const eFormat format);

protected:
	void* DX9Lock(guint8 uiLockMask);
	void DX9Unlock();	
	virtual void Allocate();
	void DX9Allocate();
	virtual void Deallocate();
	void DX9Deallocate();

};

template <class LockPolicy>
class GNDIRECTX9RENDERER_ENTRY NiDX9LockableDataStream : public GnDX9DataStream
{
protected:
	// The LockPolicy implements Locking and Unlocking
	LockPolicy mLockPolicy;

public:
	NiDX9LockableDataStream (const GnDataStream::eFormat format, guint32 uiCount) :
	  GnDX9DataStream(format, uiCount)
	{}

	virtual ~NiDX9LockableDataStream ()
	{
		if (GetLocked())
		{
			GnLog(GnText("Warning: Destroying locked NiDX9DataStream.\n"));
		}

		mLockPolicy.Delete(this);
	}
protected:
	// Locks the underlying buffer with the specified constraints
	virtual void* LockImp(guint8 uiLockMask)
	{
		// bitwise-AND out any tool lock flags
		uiLockMask &= LOCK_READ | LOCK_WRITE;

		switch (uiLockMask)
		{
		case LOCK_READ:
			return mLockPolicy.LockRead(this);
		case LOCK_WRITE:
			return mLockPolicy.LockWrite(this);
		case (LOCK_READ | LOCK_WRITE):
			return mLockPolicy.LockReadWrite(this);
		default:
			GnAssert(false);
			return NULL;
		}
	}

	// Platform specific unlocking mechanism
	virtual void UnlockImp(guint8 uiLockMask)
	{
		// bitwise-AND out any tool lock flags
		uiLockMask &= LOCK_READ | LOCK_WRITE;

		switch (uiLockMask)
		{
		case LOCK_READ:
			mLockPolicy.UnlockRead(this);
			break;
		case LOCK_WRITE:
			mLockPolicy.UnlockWrite(this);
			break;
		case (LOCK_READ | LOCK_WRITE):
			mLockPolicy.UnlockReadWrite(this);
			break;
		default:
			GnAssert(false);
			break;
		}
	}
};

#endif // GNDX9DATASTREAMELEMENT_H