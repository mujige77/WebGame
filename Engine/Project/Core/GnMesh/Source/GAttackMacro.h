//
//  GAttackMacro.h
//  Core
//
//  Created by Max Yoon on 11. 8. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GAttackMacro_h
#define Core_GAttackMacro_h

class GFarAttack;
#define GnDeclareCreateAttack \
public: \
	static void RegisterCreateFunction(); \


#define GnRegsterCreateFunction(classname) \
	classname::RegisterCreateFunction()

#define GnImplementCreateAttack(classname, id) \
	void classname::RegisterCreateFunction() \
	{	\
		static bool bRegistered = false; \
		if(bRegistered) \
			return; \
		GFarAttack::RegCreateFunction( id, classname::CreateAttack ); \
		bRegistered = true; \
	}	\

#endif
