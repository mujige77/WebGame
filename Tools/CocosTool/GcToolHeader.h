#include "GcMessageDefine.h"
#include "Gn2DTextureAniCtlr.h"
#include "GnExtraData.h"

static const TCHAR gsCollisionType[Gg2DCollision::COLLISION_MAX][256] = {
	_T("Body Box"),
	_T("Attack Box")
};

static const TCHAR gsExtraType[GExtraData::EXTRA_DATA_MAX][256] = {
	_T("Position Data"),
	_T("ID Data")
};

static const TCHAR gsTimeControllerType[][256] = {
	_T("Texture Controller")
};

static int GetExtraDataType(GnExtraData* pExtraData)
{
	if( GnDynamicCast(GnIntExtraData, pExtraData) != NULL )
		return 1;

	if( GnDynamicCast(GnVector2ExtraData, pExtraData) != NULL )
		return 0;
	return -1;
}

static CString GetMakeExtraDataTypeName(gtuint i, int iType)
{
	GtNumberString collisionName;
	gtstring type = _T("_");
	type += gsExtraType[iType];
	collisionName.SetNumber( 2, i, NULL, type.c_str() );
	return collisionName.GetString().c_str();
}

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