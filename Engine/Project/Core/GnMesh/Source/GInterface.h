//
//  GInterface.h
//  Core
//
//  Created by Max Yoon on 11. 7. 1..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GInterface__
#define __Core__GInterface__

class GnInterfaceGroup;
class GInterface : public GnMemoryObject
{
public:
	GnTPrimitiveArray<GnInterfaceGroup*> mInterfaceGroups;
	
public:
	gtuint AddInterfaceGroup(GnInterfaceGroup* pInterface) {
		mInterfaceGroups.Add( pInterface );
		return mInterfaceGroups.GetSize() - 1;
	}
	GnInterfaceGroup* GetInterfaceGroup(gtuint uiIndex) {
		return mInterfaceGroups.GetAt( uiIndex );
	}
};
#endif
