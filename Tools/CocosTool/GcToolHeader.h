#include "GcMessageDefine.h"

static const TCHAR gsCollisionType[Gg2DCollision::COLLISION_MAX][256] = {
	_T("Body Box"),
	_T("Attack Box")
};

static const TCHAR gsTextureFileFilter[] = 
	_T("Image (*.BMP, *.PNG, *.JPG)|*.BMP;*.PNG;*.JPG|All Files(*.*)|*.*||");

enum
{
	ID_CTRL_TEMPLATELIST = 20000,
	ID_VIEW_TEMPLATETASKPANE,
	ID_VIEW_SEQUENCEDOCKABLE,
	ID_VIEW_SEQUENCEMODIFYDOCKABLE,
};