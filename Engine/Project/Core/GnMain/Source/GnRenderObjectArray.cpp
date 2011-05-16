#include "GnMainPCH.h"
#include "GnRenderObjectArray.h"

void GnRenderObjectArray::SetAllocatedSize(unsigned int uiSize)
{
	if (uiSize == mAllocatedSize)
		return;

	if (uiSize < mCurrentSize)
		mCurrentSize = uiSize;

	GnRenderObject** ppkSaveArray = mppkArray;
	mAllocatedSize = uiSize;
	if (mAllocatedSize > 0)
	{
		mppkArray = GnAlloc(GnRenderObject*, mAllocatedSize);
		if (mCurrentSize)
			memcpy(mppkArray, ppkSaveArray, mCurrentSize * sizeof(GnRenderObject*));
	}
	else
		mppkArray = 0;

	// delete old array
	GnFree(ppkSaveArray);
}

GnRenderObjectArray::~GnRenderObjectArray()
{
	GnFree(mppkArray);
}