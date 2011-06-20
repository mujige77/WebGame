#include "GnMeshPCH.h"
#include "Gn2DAVDataConverter.h"

static GnVector2 GetMaxSize(Gn2DTextureAni* pAni)
{
	CCAnimate* animate = pAni->GetAnimate();
	GnAssert( animate );
	CCMutableArray<CCSpriteFrame*>* frameArray = animate->getAnimation()->getFrames();
	
	GnVector2 max;
	for( guint i = 0 ; i < frameArray->count() ; i++ )
	{
		CCSpriteFrame* frame = frameArray->getObjectAtIndex( i );
		CCRect rect = frame->getRect();
		max.x = GnMax( max.x, rect.size.width );
		max.y = GnMax( max.y, rect.size.height );
	}
	return max;
}

static GnVector2 GetMaxSize(GnVector2 size1, GnVector2 size2)
{
	GnVector2 max;
	max.x = GnMax( size1.x, size2.x );
	max.y = GnMax( size1.y, size2.y );
	return max;
}