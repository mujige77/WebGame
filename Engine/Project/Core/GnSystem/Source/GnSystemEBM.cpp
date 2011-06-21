#include "GnSystemPCH.h"
#include "GnSystemEBM.h"
#include "GnMemoryManager.h"
#include "GnSingletonManager.h"

void GnSystemEBM::StartupEBM()
{
	GnMemoryManager::EBMStartup();
	GnSingletonManager::EBMStartup();
}

void GnSystemEBM::ShutdownEBM()
{
	GnSingletonManager::EBMShutdown();
	GnMemoryManager::EBMShutdown();
}