#ifndef __GnSystem__GnTimer__
#define __GnSystem__GnTimer__
GNSYSTEM_ENTRY float GnGetTicks();

class GNSYSTEM_ENTRY GnTimer
{
private:
    float mPerTime;
	// Acumulate Time 
	float mAcumTime;
	
public:
    GnTimer();
    bool Update(float sec);

	
public:
	inline bool IsPullTime() {
		return 1 < mAcumTime/mPerTime;
	}
	inline float GetAmplify() {
		return mAcumTime/mPerTime;
	}
	inline void Reset()	{
		mAcumTime = 0.0f;
	};
	inline void SetPercentTime(float fPerTime) {
		mPerTime = fPerTime;
	}
	
};



#endif
