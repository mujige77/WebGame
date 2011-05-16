#ifndef GTOBJECT_H
#define GTOBJECT_H

class GtObject : public GtStreamObject
{
	GnDeclareRootRTTI(GtObject);
public:
	const static  gint8 GTOBJECTTYPE = 0;

protected:
	GnObjectFormPtr mpsRootNode;
	GnSimpleString mObjectName;
	GnSimpleString mFileName;
	gint32 mIndex;
	bool mNewItem; // 툴에서 새로 만들어진 오브젝트인지 확인

public:

	GtObject();
	virtual ~GtObject(){};

	virtual bool EnableLoadGnObject();
	virtual bool SaveStream() { return false; };
	virtual bool LoadStream() { return false; };
	virtual void Update(float fTime) {};
	virtual void ChanageScale(gint32 fX, gint32 fY){};
	virtual GnVector2 GetScale(){ return GnVector2( 10, 10); };

	virtual gint8 GetType() {
		return GTOBJECTTYPE;
	}

	inline GnObjectForm* GetRootNode() {
		return mpsRootNode;
	}
	inline void SetRootNode(GnObjectForm* val) {
		mpsRootNode = val;
	}

	inline const gchar* GetObjectName() {
		return mObjectName;
	}
	inline void SetObjectName(const gchar* val) {
		mObjectName = val;
	}
	
	inline const gchar* GetFileName() {
		return mFileName;
	}
	inline void SetFileName(const gchar* val) {
		mFileName = val;
	}
	inline gint32 GetIndex() {
		return mIndex;
	}
	inline void SetIndex(gint32 val) {
		mIndex = val;
	}
	inline void SetNewItem(bool bNewItem) {
		mNewItem = bNewItem;
	}
};

GnSmartPointer(GtObject);
#endif // GTOBJECT_H
