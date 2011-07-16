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
void GnInterfaceGroup::Pushup(float fPointX, float fPointY)
{
	if( IsPush() == false )
		return;
	
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		child->Pushup( fPointX, fPointY );
		if( child->IsPush() == false )
		{
			GnIInputEvent event(GnIInputEvent::PUSHUP, fPointX, fPointY);
			mSignal.EmitSignal( child, &event );
		}
	}
	
	SubPushCount();
	return;
}

bool GnInterfaceGroup::PushMove(float fPointX, float fPointY)
{
	if( IsEnablePushMove() == false )
		return false;
	
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
	{
		if( IsPush() )
			Pushup( fPointX, fPointY );
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
			child->Pushup( fPointX, fPointY );			
			if( child->IsPush() == false )
			{
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