#ifndef GNDATASTREAMELEMENT_H
#define GNDATASTREAMELEMENT_H


class GNMESH_ENTRY GnDataStream : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	enum eFormat
	{
		POSTION_STREAM,
		TEXTURE_STREAM,
		NORMAL_STREAM,
		COLOR_STREAM,
		SEMANTICS_DATASTREAM_MAX,
	};

	enum eLockType
	{
		LOCK_READ = 0x00000001,
		LOCK_WRITE = 0x00000002,
	};

protected:
	// mpVBBuffer나 mpIBBuffer에 넣어줄 데이터를 저장하고 있다 (메모리 할당함)
	void* mpLocalBuffer;
	// 현재 스트림의 버텍스 속성 (POSTION_STREAM 인지 TEXTURE_STREAM인지 COLOR_STREAM 인지)	
	// 생성시 한번 지정 되면 변형 될 수 없다.
	eFormat mFormat; 
	guint32 mVertexCount;
	guint32 mOffset; // 버텍스 속성의 크기라고 생각하면 됨	
	guint8 mNumStream; // 버텍스버퍼 스트림 번호
	guint8 mUsageIndex;	// 현재 스트림의 인덱스 ex) Tex1 Tex2
	bool mLocked; // 현재 락 상태
	bool mUnshaped;	// 아직 완성 되지 않음을 의미

public:
	GnDataStream(eFormat uFormat, guint32 uiCount);
	virtual ~GnDataStream();

	inline guint8 GetNumStream() const { return mNumStream; }
	inline void SetNumStream(guint8 val) { mNumStream = val; }
	inline guint8 GetUsageIndex() const { return mUsageIndex; }
	inline void SetUsageIndex(guint8 val) { mUsageIndex = val; }
	inline bool GetLocked() const { return mLocked; }
	inline void SetLocked(bool val) { mLocked = val; }
	inline guint32 GetOffset() { return mOffset; }
	inline void SetOffset(guint32 val) { mOffset = val; }
	inline eFormat GetFormat() { return mFormat; }

	inline gtuint GetStrideSize()
	{
		return GetStride(mFormat);
	}

	virtual gtuint GetStride(const eFormat format);
	inline void* Lock(guint8 uiLockMask) { return LockImp(uiLockMask); };
	inline void Unlock(guint8 uiLockMask) { UnlockImp(uiLockMask); };

	inline gtuint GetBufferSize() { return GetStrideSize() * GetVertexCount(); }
	inline guint32 GetVertexCount() { return mVertexCount; }
	inline void Resize(guint32 uiVertexCount)
	{
		Deallocate();
		mVertexCount = uiVertexCount;
		Allocate();
	}
	
protected:
	virtual void* LockImp(guint8 uiLockMask) = 0;
	virtual void UnlockImp(guint8 uiLockMask) = 0;

	virtual void Allocate() = 0;
	virtual void Deallocate() = 0;
};


#endif // GNDATASTREAMELEMENT_H