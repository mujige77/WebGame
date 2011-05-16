#ifndef GNRENDEROBJECTARRAY_H
#define GNRENDEROBJECTARRAY_H

class GnRenderObject;
class GNMAIN_ENTRY GnRenderObjectArray : public GnMemoryObject
{
	enum
	{
		DEF_MAX_SIZE = 1024,
		DEF_GROW_BY = 1024
	};
protected:
	GnRenderObject** mppkArray;
	gtuint mCurrentSize;
	gtuint mAllocatedSize;
	gtuint mGrowBy;

public:
	inline GnRenderObjectArray()
	{
		mppkArray = NULL;
		mCurrentSize = 0;
		mAllocatedSize = 0;
		mGrowBy = DEF_GROW_BY;

		SetAllocatedSize(DEF_MAX_SIZE);
	}
	inline GnRenderObjectArray(gtuint uiMaxSize, gtuint uiGrowBy)
	{
		mppkArray = NULL;
		mCurrentSize = 0;
		mAllocatedSize = 0;
		mGrowBy = uiGrowBy;
		if (mGrowBy == 0)
			mGrowBy = 1;

		SetAllocatedSize(uiMaxSize);
	}
	virtual ~GnRenderObjectArray();

	void SetAllocatedSize(gtuint uiSize);

	// adds to the end of the array, incrementing count by one
	inline void Add(GnRenderObject* kObj)
	{
		GnAssert(mCurrentSize <= mAllocatedSize);

		if (mCurrentSize == mAllocatedSize)
			SetAllocatedSize(mAllocatedSize + mGrowBy);

		mppkArray[mCurrentSize] = kObj;
		mCurrentSize++;
	}
	inline void RemoveAll()
	{
		mCurrentSize = 0;
	}
	inline void SetAt(gtuint uiIndex, GnRenderObject* pObj)
	{
		GnAssert(uiIndex < mCurrentSize);
		mppkArray[uiIndex] = pObj;
	}
	// uiIndex 인덱스를 지우고 그자리에 마지막에 있던 오브젝트를 집어 넣고
	// 사이즈를 줄인다.
	inline GnRenderObject* RemoveAtAndFill(gtuint uiIndex)
	{
		GnAssert(mCurrentSize != 0 && uiIndex < mCurrentSize);
		GnRenderObject* deleteObject = mppkArray[uiIndex];
		mCurrentSize--;
		mppkArray[uiIndex] = mppkArray[mCurrentSize];
		return deleteObject;
	}
	inline GnRenderObject* GetAt(gtuint uiIndex)
	{
		GnAssert(uiIndex < mCurrentSize);
		return mppkArray[uiIndex];
	}
	inline GnRenderObject& GetAt(gtuint uiIndex) const
	{
		GnAssert(uiIndex < mCurrentSize);
		return *(mppkArray[uiIndex]);
	}
	inline gtuint GetCount() const
	{
		return mCurrentSize;
	}
	inline gtuint GetAllocatedSize() const
	{
		return mAllocatedSize;
	}
	inline gtuint GetGrowBy() const
	{
		return mGrowBy;
	}
	inline void SetGrowBy(gtuint uiGrowBy)
	{
		if (uiGrowBy == 0)
			mGrowBy = 1;
		else
			mGrowBy = uiGrowBy;
	}
};

#endif // GNRENDEROBJECTARRAY_H