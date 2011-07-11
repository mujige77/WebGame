#ifdef _UNICODE
#define GNUNICODE
#endif // UNICODE

#include <GnMainHeader.h>
#include <GnMeshHeader.h>
#include <GnGameHeader.h>
template<class KeyType>
class GtTCStringMapHash
{
public:
	inline static gtuint HashIndex( KeyType key )
	{
		return key.GetLength();
	}
};

template<class T>
class GtTCStringMap : public GnTMap<CString, T, GnDefaultDeallocate, GtTCStringMapHash>
{
public:
	GtTCStringMap(gtuint size = 5) :GnTMap(size)
	{}
};
static const gchar gsActorPath[] = {
	"Actor/"
};

enum
{
	TYPE_2DOBJECT_EFFECT,
	TYPE_2DOBJECT_OBJECT,
	TYPE_2DOBJECT_MAX,
};
static const gchar gs2DObjectPath[TYPE_2DOBJECT_MAX][64] =
{
	"Effect/",
	"Object/"
};

std::string GetOnlyFileNameAttachNumber(gtint iID, const gchar* filePath);

#include "GnTimer.h"
#include "GtConvertString.h"
#include "GtNumberString.h"
#include "GtToolSettings.h"
#include "GtObject.h"
#include "Gt2DSequence.h"
#include "Gt2DObject.h"
#include "GtActorTool.h"
#include "Gt2DMesh.h"
#include "Gt2DActor.h"
#include "GtObjectNew.h"
#include "GtObjectFactory.h"