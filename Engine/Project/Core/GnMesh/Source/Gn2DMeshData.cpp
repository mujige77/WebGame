#include "GnMeshPCH.h"
#include "Gn2DMeshData.h"

#define GnExcuteCocosChildFunc(arrayVal, funcName) \
	CCObject* child; \
	CCARRAY_FOREACH(arrayVal, child) \
	{ \
		CCSprite* sprite = (CCSprite*)child; \
		if( sprite ) \
		sprite->funcName; \
	}

void Gn2DMeshData::addChild(CCNode *pChild, int zOrder, int tag)
{
	CCSprite::addChild( pChild, zOrder, tag );
	
	CCSprite* sprite = (CCSprite*)pChild;	
	sprite->setColor( getColor() );
	sprite->setOpacity( getOpacity() );
	sprite->setScale( getScale() );
	sprite->setPosition( getPosition() );
	sprite->setAnchorPoint( getAnchorPoint() );
	sprite->setFlipX( isFlipX() );
	sprite->setFlipY( isFlipY() );
	sprite->setRotation( getRotation() );
}

void Gn2DMeshData::setColor(ccColor3B color3)
{
	CCSprite::setColor( color3 );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setColor(color3) );
	}
}
void Gn2DMeshData::setOpacity(GLubyte opacity)
{
	CCSprite::setOpacity( opacity );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setOpacity( opacity ) );
	}
}
void Gn2DMeshData::setScale(float fScale)
{
	CCSprite::setScale( fScale );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setScale( fScale ) );
	}
}
void Gn2DMeshData::setPosition(CCPoint pos)
{
	CCSprite::setPosition( pos );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setPosition( pos ) );
	}
}
void Gn2DMeshData::setAnchorPoint(CCPoint anchor)
{
	CCSprite::setAnchorPoint( anchor );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setAnchorPoint( anchor ) );
	}
}
void Gn2DMeshData::setFlipX(bool bFlipX)
{
	CCSprite::setFlipX( bFlipX );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setFlipX(bFlipX) )
	}
}
void Gn2DMeshData::setFlipY(bool bFlipY)
{
	CCSprite::setFlipY( bFlipY );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setFlipY( bFlipY ) )
	}
}
void Gn2DMeshData::setRotation(float fRotation)
{
	CCSprite::setRotation( fRotation );
	if( m_pChildren && m_pChildren->count() > 0) 
	{
		GnExcuteCocosChildFunc( m_pChildren, setRotation( fRotation ) )
	}
}