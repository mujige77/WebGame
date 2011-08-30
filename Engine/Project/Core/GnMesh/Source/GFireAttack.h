//
//  GFireAttack.h
//  Core
//
//  Created by Max Yoon on 11. 8. 29..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GFireAttack_h
#define Core_GFireAttack_h

class GFireAttack : public GFarAttack
{
	GnDeclareCreateAttack;
public:
	static GFarAttack* CreateAttack(guint32 uIndex);
	
public:
	void Update(float fTime);
	//void SetPosition(GnVector2 cPos);
};


#endif
