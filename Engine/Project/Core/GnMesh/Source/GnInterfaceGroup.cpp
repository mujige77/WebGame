#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterfaceGroup.h"

bool GnInterfaceGroup::Push(float fPointX, float fPointY)
{
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
		return false;
	
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		if( child->IfUseCheckCollision( fPointX, fPointY ) && child->Push( fPointX, fPointY ) )
		{
			GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
			mSignal.EmitSignal( child, &event );
		}
	}
	
	AddPushCount();
	return true;
}
bool GnInterfaceGroup::Pushup(float fPointX, float fPointY)
{
	if( GnInterface::Pushup( fPointX, fPointY ) == false )
		return false;
	
	return true;
}

bool GnInterfaceGroup::PushMove(float fPointX, float fPointY)
{
	if( IsEnablePushMove() == false )
		return false;
	
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
	{
		if( IsPush() )
			PushUp();
		return false;
	}
	
	if ( IsPush() == false )
	{
		Push( fPointX, fPointY );
		return true;
	}

	for( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		
		
		if( child->IfUseCheckCollision( fPointX, fPointY ) == false )
		{
			if( child->IsPush() )
			{
				child->PushUp();
				GnIInputEvent event(GnIInputEvent::PUSHUP, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );
			}
		}
		else
		{
			if( child->IsPush() == false )
			{
				child->Push( fPointX, fPointY );
				GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );		
			}
			else
			{
				child->PushMove( fPointX, fPointY );
				GnIInputEvent event(GnIInputEvent::MOVE, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );	
			}
		}
	}
	return true;
}

void GnInterfaceGroup::PushUp()
{
	GnInterface::PushUp();
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		if( child->IsPush() )
		{
			child->PushUp();
			GnIInputEvent event(GnIInputEvent::PUSHUP, 0.0f, 0.0f);
			mSignal.EmitSignal( child, &event );
		}
	}
}

void GnInterfaceGroup::Update(float fDeltaTime)
{
	for( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		child->Update( fDeltaTime );
	}
}

void GnInterfaceGroup::SetPosition(GnVector2& cPos)
{
	
}