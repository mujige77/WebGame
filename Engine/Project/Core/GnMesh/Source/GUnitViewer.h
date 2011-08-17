//
//  GUnitViewer.h
//  Core
//
//  Created by Max Yoon on 11. 8. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GUnitViewer_h
#define Core_GUnitViewer_h

#include "GUserHaveItem.h"

class GUnitViewer : public GnInterface
{
	class Unit : public GnMemoryObject
	{
	public:
		Unit(guint32 uiIndex, GActorController* pActor = NULL) : mIndex(uiIndex), mpActorController( pActor )
		{}
		~Unit() 
		{
			if( mpActorController )
				GnDelete mpActorController;
		}
	public:
		guint32  mIndex;
		GActorController* mpActorController;
	};
	
protected:
	GnTPrimitiveArray<GUnitViewer::Unit*> mActors;
	
public:
	static GUnitViewer* CreateUnitViewer(GnList<GUserHaveItem::Item>& cUnitItems);
	
public:
	virtual ~GUnitViewer();	
	
public:
	void Update(float fDeltaTime);
	void SetVisibleActorCtlr(guint32 uiIndex, bool bVisible);
	
public:
	gtuint GetActorCtlrSize() {
		return mActors.GetSize();
	}
	GActorController* GetActorCtrlFromUnitIndex(guint32 uiIndex)
	{
		for( gtuint i = 0 ; i < mActors.GetSize() ; i++ )
		{
			GUnitViewer::Unit* unit = mActors.GetAt( i );
			if( unit->mIndex == uiIndex )
				return unit->mpActorController;
		}
		return NULL;		
	}
	
	GActorController* GetActorCtlr(gtuint uiIndex)
	{		
		return mActors.GetAt( uiIndex )->mpActorController;
	}
	
	GUnitViewer::Unit* GetUnit(gtuint uiIndex)	{
		return mActors.GetAt( uiIndex );
	}
	void AddActorCtlr(guint32 uiIndex, GActorController* pActor) {
		GUnitViewer::Unit* unit = GnNew GUnitViewer::Unit( uiIndex, pActor );
		mActors.Add( unit );
	}
};

#endif
