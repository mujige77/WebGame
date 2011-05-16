#ifndef GTTIMECONTORLLER_H
#define GTTIMECONTORLLER_H

class GtTimeController : public GtStreamObject
{
protected:
	GnSimpleString mTargetName;

public:
	GtTimeController(){};
	virtual ~GtTimeController(){};

	virtual void SaveStream(const gchar* objectName, const gchar* basePath) = 0;
	virtual void LoadStream(const gchar* objectName, const gchar* basePath) = 0;

	inline GnSimpleString& GetTargetName() {
		return mTargetName;
	}
	inline void SetTargetName(const gchar* val) {
		mTargetName = val;
	}
	virtual bool ExistSaveData() = 0;
	virtual GnTimeController* CreateGnTimeController() = 0;
};

GnSmartPointer( GtTimeController );

#endif // GTTIMECONTORLLER_H
