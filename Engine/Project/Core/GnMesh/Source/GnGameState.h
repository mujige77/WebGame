#ifndef GNGAMESTATE_H
#define GNGAMESTATE_H

class GnGameState
{
private:
	static GnGameState mSingleton;		
	float mGameScale;
	
public:
	
	static GnGameState* GetSingleton();

	inline float GetGameScale() {
		return mGameScale;
	}
	inline void SetGameScale(float val) {
		mGameScale = val;
	}

private:
	GnGameState();
};

#define GetGameState GnGameState::GetSingleton
#endif // GNGAMESTATE_H