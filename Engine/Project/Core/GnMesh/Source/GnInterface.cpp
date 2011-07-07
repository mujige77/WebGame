#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterface.h"

GnInterface::GnInterface()
{
	SetIsPush( false );
	SetIsHover( false );
	SetIsCantPush( false );
	SetIsDisable( false );	
}

bool GnInterface::Push(float fPointX, float fPointY)
{
	if( IsDisable() || IsCantPush() )
		return false;
	
	if( mRect.ContainsPoint(fPointX, fPointY) == false )
	{
		SetIsPush( false );
		return false;
	}

	SetIsPush( true );
	return true;
}
void GnInterface::Pushup(float fPointX, float fPointY)
{
	SetIsPush( false );
}