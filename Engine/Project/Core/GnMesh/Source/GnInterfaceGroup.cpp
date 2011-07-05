//
//  GnInterfaceGroup.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 28..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnInterfacePCH.h"
#include "GnInterfaceGroup.h"

bool GnInterfaceGroup::Push(float fPointX, float fPointY)
{
	if( GnInterface::Push( fPointX, fPointY) == false )
		return false;
	
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		if( child->Push( fPointX, fPointY ) )
		{
			GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
			mSignal.EmitSignal( child, &event );
			return true;
		}
	}
	
	return false;
}
void GnInterfaceGroup::Pushup(float fPointX, float fPointY)
{
	if( IsPush() == false )
		return;
	
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		if( child->IsPush() )
		{	
			child->Pushup( fPointX, fPointY );
			GnIInputEvent event(GnIInputEvent::PUSHUP, fPointX, fPointY);
			mSignal.EmitSignal( child, &event );
		}
	}
	SetIsPush( false );
}

void GnInterfaceGroup::SetPosition(GnVector2& cPos)
{
	
}