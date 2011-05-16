#ifndef GNDATASTREAMLOCKPOLICY_H
#define GNDATASTREAMLOCKPOLICY_H

#include <GnCriticalSection.h>
template<class TDataStream>
class GnDataStreamLockPolicy 
{
public:
	/// Constructor.
	GnDataStreamLockPolicy();

	/// Locks the stream for read access and returns a pointer to the data.
	void* LockRead(TDataStream* pkDS);

	/// Locks the stream for write access and returns a pointer to the data.
	void* LockWrite(TDataStream* pkDS);

	/// Locks the stream for read/write access and returns a pointer to the
	/// data.
	void* LockReadWrite(TDataStream* pkDS);

	/// Unlocks a stream that was previously locked for read access.
	void UnlockRead(TDataStream* pkDS);

	/// Unlocks a stream that was previously locked for write access.
	void UnlockWrite(TDataStream* pkDS);

	/// Unlocks a stream that was previously locked for read/write access.
	void UnlockReadWrite(TDataStream* pkDS);

	/// In debug builds, asserts that the stream is not locked and hence
	/// is safe to delete.
	void Delete(TDataStream* pkDS);

protected:
	GnCriticalSection m_kLock;

	/// Number of read locks.
	gtuint mReadLockCount;

	/// Number of write locks.
	gtuint mWriteLockCount;
};

template <class TDataStream>
GnDataStreamLockPolicy<TDataStream>::GnDataStreamLockPolicy() : mReadLockCount(0), mWriteLockCount(0)
{}
//---------------------------------------------------------------------------
template <class TDataStream>
void* GnDataStreamLockPolicy<TDataStream>::LockRead(TDataStream* pkDS)
{
	m_kLock.Lock();
	++mReadLockCount;
	GnAssert(mReadLockCount > 0);
	void* pvRetVal = pkDS->MapBuffer(GnDataStream::LOCK_READ, mReadLockCount, mWriteLockCount);
	pkDS->SetLocked(pvRetVal != 0);
	return pvRetVal;
}
//---------------------------------------------------------------------------
template <class TDataStream>
void* GnDataStreamLockPolicy<TDataStream>::LockWrite(TDataStream* pkDS)
{
	m_kLock.Lock();
	++mWriteLockCount;
	GnAssert(mWriteLockCount > 0);
	void* pvRetVal = pkDS->MapBuffer(GnDataStream::LOCK_WRITE, mReadLockCount, mWriteLockCount);
	pkDS->SetLocked(pvRetVal != 0);
	return pvRetVal;
}
//---------------------------------------------------------------------------
template <class TDataStream>
void* GnDataStreamLockPolicy<TDataStream>::LockReadWrite(TDataStream* pkDS)
{
	m_kLock.Lock();
	++mReadLockCount;
	++mWriteLockCount;
	GnAssert(mReadLockCount > 0);
	GnAssert(mWriteLockCount > 0);
	void* pvRetVal = pkDS->MapBuffer( GnDataStream::LOCK_WRITE | GnDataStream::LOCK_READ,
		mReadLockCount, mWriteLockCount);
	pkDS->SetLocked(pvRetVal != 0);
	return pvRetVal;
}
//---------------------------------------------------------------------------
template <class TDataStream>
void GnDataStreamLockPolicy<TDataStream>::UnlockRead(TDataStream* pkDS)
{
	--mReadLockCount;
	GnAssert(mReadLockCount != 0xFFFFFFFF);
	pkDS->SetLocked((mWriteLockCount != 0) || (mReadLockCount != 0));
	pkDS->UnmapBuffer(GnDataStream::LOCK_READ, mReadLockCount,
		mWriteLockCount);
	m_kLock.Unlock();
}
//---------------------------------------------------------------------------
template <class TDataStream>
void GnDataStreamLockPolicy<TDataStream>::UnlockWrite(TDataStream* pkDS)
{
	--mWriteLockCount;
	GnAssert(mReadLockCount != 0xFFFFFFFF);
	pkDS->SetLocked((mWriteLockCount != 0) || (mReadLockCount != 0));
	pkDS->UnmapBuffer(GnDataStream::LOCK_WRITE, mReadLockCount,	mWriteLockCount);
	m_kLock.Unlock();
}
//---------------------------------------------------------------------------
template <class TDataStream>
void GnDataStreamLockPolicy<TDataStream>::UnlockReadWrite(TDataStream* pkDS)
{
	--mReadLockCount;
	--mWriteLockCount;
	GnAssert(mReadLockCount != 0xFFFFFFFF);
	GnAssert(mWriteLockCount != 0xFFFFFFFF);
	pkDS->SetLocked((mWriteLockCount != 0) || (mReadLockCount != 0));
	pkDS->UnmapBuffer(GnDataStream::LOCK_READ | GnDataStream::LOCK_WRITE, 
		mReadLockCount, mWriteLockCount);
	m_kLock.Unlock();
}
//---------------------------------------------------------------------------
template <class TDataStream>
void GnDataStreamLockPolicy<TDataStream>::Delete(TDataStream* pkDS)
{
	// Assert that the stream is not currently locked while we're deleting.
	// Deleting a locked stream would indicate a logical error since the
	// locked region would be invalidated.
	GnAssert(mReadLockCount == 0);
	GnAssert(mWriteLockCount == 0);
}


#endif // GNDATASTREAMLOCKPOLICY_H