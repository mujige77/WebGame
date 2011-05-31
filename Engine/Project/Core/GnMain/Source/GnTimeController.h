#ifndef GNTIMECONTROLLER_H
#define GNTIMECONTROLLER_H


class GnAVObject;
GnSmartPointer(GnTimeController);
class GNMAIN_ENTRY GnTimeController : public GnObject
{
	GnDeclareRTTI;
	GnDeclareStream;
	GnDeclareFlags(gint);
protected:
	GnAVObject* mpTarget;	
	GnSimpleString mTargetName;
	GnTimeControllerPtr mpsNext;
	float mStartTime;
	gtuint mPlayFlags;	

public:
	GnTimeController();
	virtual ~GnTimeController();
protected:
	enum
	{
		LOOP_MASK = 0x00000001,
		STOP,
		PLAY,
	};	

public:
	virtual void Update(float fTime){};
	virtual void Start(float fTime);
	virtual void Stop();

	inline bool IsLoop() { return GetBit(LOOP_MASK); }
	inline void SetLoop(bool val) { SetBit(val, LOOP_MASK); }
	inline  GnTimeController* GetNext() {
		return mpsNext;
	}
	inline void SetNext( GnTimeController* pNext ) {
		mpsNext = pNext;
	}

	inline GnSimpleString& GetTargetName() {
		return mTargetName;
	}
	inline void SetTargetName(const gchar* val) {
		mTargetName = val;
	}
	
	inline bool IsStreamable() const {
		return true;
	}
	virtual bool SetTargetObject(GnObjectForm* pObject);
};


#endif // GNTIMECONTROLLER_H