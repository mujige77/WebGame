#ifndef __GnSystem__GnTimer__
#define __GnSystem__GnTimer__
GNSYSTEM_ENTRY float GnGetTicks();

class GNSYSTEM_ENTRY GnTimer : public GnMemoryObject
{
public:
    GnTimer();
    void Reset();
    
    
	//원하는 타임을 얻기 위해 메프레임 업데이트 한다.
	// sce = 누적된 타임
	
    bool Update(float sec);    
    inline bool Update();
	
    inline float getDelta();
    
private:
	
    // 이전 프레임과 현재 프레임의 시간차
    float mDeltaTime;
    // 마지막 업데이트 타임
    float mLastTime;
};



#endif
