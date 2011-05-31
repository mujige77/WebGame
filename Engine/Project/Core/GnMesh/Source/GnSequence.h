#ifndef GNANIMATIONCTRL_H
#define GNANIMATIONCTRL_H

class GNMESH_ENTRY GnSequence : public GnObject
{
	GnDeclareRTTI;
	GnDeclareStream;
	GnDeclareFlags(gushort);
	enum
	{
		LOOP_MASK,
	};

protected:
	GnTimeControllerPtr mpsTimeControls;
	GnSimpleString mName;	
	float mStartTime;
	float mEndTime;

public:
	GnSequence(){};
	virtual ~GnSequence(){};

	// 애니메이션을 위한 타임 컨트롤러에 타겟을 셋팅할 오브젝트를 넘겨주고. 오브젝트에도 컨트롤러를 셋팅한다.	
	void SetTargetObject(GnObjectForm* pObject);

	virtual void Update(float fTime){};
	virtual void Start(float fTime);
	virtual void Stop();

	inline GnTimeController* GetTimeControls() {
		return mpsTimeControls;
	}
	inline void SetTimeControls(GnTimeController* val) {
		mpsTimeControls = val;
	}
	inline const gchar* GetName() {
		return mName;
	}
	inline void SetName(const gchar* pcName) {
		mName = pcName;
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
	inline bool IsLoop() { return GetBit(LOOP_MASK); }
	inline void SetLoop(bool val) { SetBit(val, LOOP_MASK); }

};

#endif // GNANIMATIONCTRL_H