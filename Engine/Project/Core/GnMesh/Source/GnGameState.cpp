#include "GnMeshPCH.h"
#include "GnGameState.h"

GnGameState GnGameState::mSingleton;

GnGameState* GnGameState::GetSingleton() {
	return &mSingleton;
}

GnGameState::GnGameState() : mGameScale( 1.0f ), mGameWidth(0.0f), mGameHeight(0.0f)
{
	
}