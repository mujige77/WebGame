#ifndef GNMODELSTREAM_H
#define GNMODELSTREAM_H
#include <GnTStringMap.h>
#include "GnStream.h"

class GnObjectStream : public GnStream
{
protected:
	GnTPrimitiveArray<GnObject*> mRootLevelObjects; // used save, load
	GnTPrimitiveArray<GnObject*> mObjectLists; // used save, load
	GnTObjectArray<GnSimpleString> mFixedStrings; // used save, load
	GnTPrimitiveArray<guint32> mLinkIDs;	// used load
	GnTPrimitiveArray<guint32> mMultiLinkIDBlocks;	// used load
	GnTMap<const GnObject*, guint32> mRegObjects; // used save
	gtuint mLinkIndex;
	gtuint mLinkBlockIndex;

public:
	GnObjectStream();
	virtual ~GnObjectStream(){};

	virtual bool Load(const gchar* pcFilePath);
	virtual bool Save(const gchar* pcFilePath);

	// \277\u02d9\277\302\253\u201c \u2248\u25ca\277\303\u2248\325\u220f\266 \u220f\uf8ff\277\u220f\u221e\314 \265\u2022\277\303\u2248\325\370\260 \346\u2206\277\303\265\uf8ff\u220f\266 \241\u02c6\241\247 \253\u0153\261\u201a \277\337\253\u2014 mRegObjects\370\260 \370\277\u222b\315\241\337\u2206\306\370\325 \253\u2018\u2264\u2264 linkID\265\265 \277\u02d9\277\302
	bool RegisterSaveObject(GnObject* pObject); // Save
	bool RegisterFixedString(GnSimpleString& str); // Save\252\301\370\316
	guint32 GetStringID(const GnSimpleString& str);
	void SaveFixedString(const GnSimpleString& str); // Save \252\301\370\316
	void LoadFixedString(GnSimpleString& str);

	GnObject* GetObjectFromLinkID(); // Load\370\316
	guint32 LoadMultipleLinkIDs(); // Load\370\316
	guint32 GetLinkID(const GnObject* pObject);

	inline gtuint GetObjectCount() {
		return mRootLevelObjects.GetSize();
	}

	inline GnObject* GetObject(gtuint uiIndex) {		
		return mRootLevelObjects.GetAt(uiIndex);
	}

	inline void InsertRootObjects(GnObject* pObject) {
		mRootLevelObjects.Add( pObject );
	}

	inline guint32 GetNumberOfLinkIDs()
	{
		GnAssert( mMultiLinkIDBlocks.GetSize() > mLinkBlockIndex );
		return mMultiLinkIDBlocks.GetAt( mLinkBlockIndex++ );
	}
	inline void LoadLinkID() {
		guint32 linkID = 0;
		LoadStream(linkID);
		mLinkIDs.Add(linkID);
	}

	inline void SaveLinkID(const GnObject* pObject) {
		guint32 linkID = GetLinkID(pObject);
		SaveStream(linkID);
	}

protected:
	bool LoadHeader();
	void RegisterObject();
	void SaveHeader();
	bool LoadRTTI();
	void SaveRTTI();
	void LoadFixedStrings();
	void SaveFixedStrings();
	void LoadRTTiString(gchar* pcStr);
	void SaveObject();
	void LinkObject();
	bool LoadObject();
	void SaveRootObject();
	bool LoadRootObject();

	void RemoveAllObjects();
	void ResetLoadDatas();
};

#endif // GNMODELSTREAM_H\037\037\036