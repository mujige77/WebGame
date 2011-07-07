#ifndef __Core__GCurrentInfo__
#define __Core__GCurrentInfo__

class GCurrentActorInfo
{
private:
	gint32 mHP;
public:
	
public:
	inline gint32 GetHP() {
		return mHP;
	}
	inline void SetHP(gint32 uiHP) {
		if( uiHP < 0 )
		{
			mHP = 0;
			return;
		}
		mHP = uiHP;
	}
};

#endif
