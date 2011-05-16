#ifndef GTSEQUENCEINFO_H
#define GTSEQUENCEINFO_H

class GtSequenceInfo : public GtStreamObject
{
protected:
	GnSequence* mpSequence;
	guint32 mSequenceID;
	GnSimpleString mName;
	GnSimpleString mFileName;	
	float mStartTime;
	float mEndTime;	
	GnTObjectArray<GtTimeControllerPtr> mTimeCtlrs;

public:
	GtSequenceInfo();
	virtual ~GtSequenceInfo(){};

	void RemoveController(GtTimeController* pCtlr);
	void ChangePostionController(GtTimeController* pCtlr1, GtTimeController* pCtlr2);

	void SaveStream(const gchar* objectName, const gchar* basePath);
	void LoadStream(const gchar* objectName, const gchar* basePath);

	GnSequence* CreateSequence();

	inline guint32 GetSequenceID() {
		return mSequenceID;
	}
	inline void SetSequenceID(guint32 val) {
		mSequenceID = val;
	}
	inline GnSimpleString& GetName() {
		return mName;
	}
	inline void SetName(const char* val) {
		mName = val;
	}
	inline GnSimpleString& GetFileName() {
		return mFileName;
	}
	inline void SetFileName(const char* val) {
		mFileName = val;
	}
	inline float GetStartTime() {
		return mStartTime;
	}
	inline void SetStartTime(float val) {
		mStartTime = val;
	}
	inline float GetEndTime() {
		return mEndTime;
	}
	inline void SetEndTime(float val) {
		mEndTime = val;
	}
	inline GnSequence* GetSequence() {
		return mpSequence;
	}
	inline void SetSequence(GnSequence* val) {
		mpSequence = val;
	}

	inline GnTObjectArray<GtTimeControllerPtr>* GetTimeControllers() {
		return &mTimeCtlrs;
	}
	inline gtuint GetTimeControllerCount() {
		return mTimeCtlrs.GetSize();
	}
	inline GtTimeController* GetTimeController(gtuint uiIndex) {
		return mTimeCtlrs.GetAt( uiIndex );
	}
	inline void AddTimeController(GtTimeController* pCtlr) {
		mTimeCtlrs.Add( pCtlr );
	}
};

GnSmartPointer( GtSequenceInfo );

#endif // GTSEQUENCEINFO_H
