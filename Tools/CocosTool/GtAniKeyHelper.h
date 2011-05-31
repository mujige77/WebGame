#ifndef GTANIKEYHELPER_H
#define GTANIKEYHELPER_H
#include "GnAnimationKeyManager.h"
#include "GnTegIDKey.h"

int GetAniKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager
	, GnAnimationKeyManager::AniKey& outKey);

void AddTegIDKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager
	, float keyTime, guint32 tegID);

void RemoveTegIDKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager, guint uiIndex);

#endif // GTANIKEYHELPER_H