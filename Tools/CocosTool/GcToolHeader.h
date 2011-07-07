#include "GcMessageDefine.h"

static const TCHAR gsCollisionType[Gg2DCollision::COLLISION_MAX][256] = {
	_T("Body Box"),
	_T("Attack Box")
};

static const TCHAR gsExtraType[GExtraData::EXTRA_DATA_MAX][256] = {
	_T("Effect Position Data"),
	_T("Effect Data")
};

static const TCHAR gsTextureFileFilter[] = 
	_T("Image (*.BMP, *.PNG, *.JPG)|*.BMP;*.PNG;*.JPG|All Files(*.*)|*.*||");

enum
{
	ID_CTRL_TEMPLATELIST = 500000,	
	ID_VIEW_TEMPLATETASKPANE,
	ID_VIEW_SEQUENCEDOCKABLE,
	ID_VIEW_SEQUENCEMODIFYDOCKABLE,
	ID_CTRL_EFFECTTEMPLATELIST,
};