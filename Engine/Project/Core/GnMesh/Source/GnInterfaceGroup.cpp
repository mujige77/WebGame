#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterfaceGroup.h"

GnImplementRTTI(GnInterfaceGroup, GnInterface);
bool GnInterfaceGroup::Push(float fPointX, float fPointY)
{
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
	{
		for ( gtuint i = 0; i < mPersonalChildren.GetSize(); i++ )
		{
			GnInterface* child = mPersonalChildren.GetAt( i );
			if( child->IsVisible() && child->Push( fPointX, fPointY ) )
			{
				GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );
			}
		}
		return false;
	}
	
	for ( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		if( child->IsVisible() && child->Push( fPointX, fPointY ) )
		{
			GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
			mSignal.EmitSignal( child, &event );
		}
	}
	
	AddPushCount();
	return true;
}

bool GnInterfaceGroup::PushUp(float fPointX, float fPointY)
{
	if( GnInterface::PushUp( fPointX, fPointY ) == false )
	{
		for ( gtuint i = 0; i < mPersonalChildren.GetSize(); i++ )
		{
			GnInterface* child = mPersonalChildren.GetAt( i );
			if( child->IsVisible() && child->PushUp( fPointX, fPointY ) )
			{
				GnIInputEvent event(GnIInputEvent::PUSHUP, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );
			}
		}
		return false;
	}
	
	return true;
}

bool GnInterfaceGroup::PushMove(float fPointX, float fPointY)
{
	if( IsEnablePushMove() == false )
		return false;
	
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
	{
		for ( gtuint i = 0; i < mPersonalChildren.GetSize(); i++ )
		{
			GnInterface* child = mPersonalChildren.GetAt( i );
			if( child->IsVisible() && child->PushMove( fPointX, fPointY ) )
			{
				GnIInputEvent event(GnIInputEvent::PUSH, fPointX, fPointY);
				mSignal.EmitSignal( child, &event );
			}
		}
		
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
			if( child->IsVisible() && child->IsPush() == false )
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

void GnInterfaceGroup::SetAlpha(guchar ucAlpha)
{
	GnInterface::SetAlpha( ucAlpha );
	for( gtuint i = 0; i < GetChildrenSize() ; i++ )
	{
		GnInterface* child = GetChild( i );
		child->SetAlpha( ucAlpha );
	}	
}

void GnInterfaceGroup::SetPosition(GnVector2& cPos)
{
	
}