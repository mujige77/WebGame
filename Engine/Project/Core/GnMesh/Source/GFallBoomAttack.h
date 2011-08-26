#ifndef Core_GFallBoomAttack_h
#define Core_GFallBoomAttack_h

#include "GFarAttack.h"

class GFallBoomAttack : public GFarAttack
{
	GnDeclareCreateAttack;
public:
	static GFarAttack* CreateAttack(guint32 uIndex);
	
public:
	void Update(float fTime);
	void SetPosition(GnVector2 cPos);
	inline eBasicStartPosition GetBasicStartPosition() {
		return eUserPosition;
	}
	
};

#endif
