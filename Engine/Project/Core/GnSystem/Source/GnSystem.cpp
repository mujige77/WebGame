#include "GnSystemPCH.h"
#include "GnSystem.h"

namespace GnSystem
{
	gchar gWorkDirectory[GN_MAX_PATH] = {0,};

	void SetWorkDirectory(const gchar* pcVal)
	{
		GnStrcpy( gWorkDirectory, pcVal, sizeof( gWorkDirectory ) );
	}

	const gchar* GetWorkDirectory()
	{
		return gWorkDirectory;
	}
}