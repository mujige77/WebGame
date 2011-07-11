#include "GcMessageDefine.h"
#include "Gn2DTextureAniCtlr.h"

static const TCHAR gsCollisionType[Gg2DCollision::COLLISION_MAX][256] = {
	_T("Body Box"),
	_T("Attack Box")
};

static const TCHAR gsExtraType[GExtraData::EXTRA_DATA_MAX][256] = {
	_T("Effect Position Data"),
	_T("Effect Position ID Data")
};

static const TCHAR gsTimeControllerType[][256] = {
	_T("Texture Controller")
};

static const TCHAR* GetTimeControllerName(GnTimeController* pController)
{
	GnAssert( pController );
	GnTimeController* checkCtrl = GnDynamicCast( Gn2DTextureAniCtlr, pController );
	if( checkCtrl )
		return gsTimeControllerType[0];

	return NULL;
}

static const TCHAR gsTextureFileFilter[] = 
	_T("Image (*.BMP, *.PNG, *.JPG)|*.BMP;*.PNG;*.JPG|All Files(*.*)|*.*||");

enum
{
	ID_CTRL_TEMPLATELIST = 500000,	
	ID_VIEW_TEMPLATETASKPANE,
	ID_WINDOW_SEQUENCEDOCKABLE,
	ID_VIEW_SEQUENCEMODIFYDOCKABLE,
	ID_CTRL_EFFECTTEMPLATELIST,
	ID_WINDOW_2DOBJECTDOCKABLE,
};