#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorInfoDatabase.h"

GnImplementSingleton(GActorInfoDatabase)

GActorInfoDatabase::GActorInfoDatabase() : mSqlite( GetFullPath( "ActorInfo.sqlite" ) )
{

}