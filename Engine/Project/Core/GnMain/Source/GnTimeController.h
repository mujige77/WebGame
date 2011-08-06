#ifndef GNTIMECONTROLLER_H
#define GNTIMECONTROLLER_H


class GnObjectForm;
GnSmartPointer(GnTimeController);
class GNMAIN_ENTRY GnTimeController : public GnObject
{
	GnDeclareRTTI;
	GnDeclareAbstractStream;
	GnDeclareFlags(gint);

public:
	enum eCycleType
	{
		LOOP,
		REVERSE,
		ONCE,
		MAX_CYCLE_TYPES
	};

	enum ePlayFlag
	{
		STOP,
		PLAY,
		PLAYING,
	};	

protected:
	GnObjectForm* mpTarget;
	GnTimeControllerPtr mpsNext;
	float mStartTime;
	float mAccumulateDeltaTime;
	gtuint mPlayFlags;
	bool mIsMeshSteram;
	eCycleType mCycleType;

public:
	GnTimeController();
	virtual ~GnTimeController();

	static void SetCycleType(GnTimeController::eCycleType eType, GnObjectForm* pObject);
	static void StartTimeControllers(GnObjectForm* pObject);
	static void StopTimeControllers(GnObjectForm* pObject);
	static bool IsAllStopControllers(GnObjectForm* pObject);
protected:

public:
	virtual void Update(float fDeltaTime) = 0;
	virtual void Start();
	virtual void Stop();	
	virtual bool SetTargetObject(GnObjectForm* pObject);
	
public:
	inline  GnTimeController* GetNext() {
		return mpsNext;
	}
	inline void SetNext( GnTimeController* pNext ) {
		mpsNext = pNext;
	}
	inline bool IsStreamable() const {
		return true;
	}
	inline void SetIsMeshStreamble(bool val) {
		mIsMeshSteram = val;
	}
	inline bool IsMeshStreamble() const {
		return mIsMeshSteram;
	}
	inline eCycleType GetCycleType() {
		return mCycleType;
	}
	inline void SetCycleType(eCycleType val) {
		mCycleType = val;
	}
	inline gtuint GetPlayFlags() {
		return mPlayFlags;
	}
	inline void SetPlayFlags(gtuint val) {
		mPlayFlags = val;
	}
protected:	
	virtual void Playing(float fTime);

protected:
	inline float GetAccumulateTime() {
		return mAccumulateDeltaTime;
	}
	void SetAccumulateTime(float fTime) {
		mAccumulateDeltaTime = fTime;
	}
};


#endif // GNTIMECONTROLLER_H