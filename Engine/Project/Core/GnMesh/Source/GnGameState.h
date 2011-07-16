#ifndef GNGAMESTATE_H
#define GNGAMESTATE_H

#define DEFAULT_SCALE 0.7
class GnGameState
{
private:
	static GnGameState mSingleton;		
	float mGameScale;
	float mGameWidth;
	float mGameHeight;
	
public:
	
	static GnGameState* GetSingleton();

	inline float GetGameScale() {
		return mGameScale;
	}
	inline void SetGameScale(float val) {
		mGameScale = val;
	}
	inline float GetGameWidth() {
		return mGameWidth;
	}
	inline float GetGameHeight() {
		return mGameHeight;
	}
	inline void SetGameDisplaySize(float fWidth, float fHeight) {
		mGameWidth = fWidth;
		mGameHeight = fHeight;
	}


private:
	GnGameState();
};

#define GetGameState GnGameState::GetSingleton
#endif // GNGAMESTATE_H