#ifndef GN2DMESHDATA_H
#define GN2DMESHDATA_H

class Gn2DMeshData : public CCSprite
{
public:
	Gn2DMeshData(){};
	virtual ~Gn2DMeshData(){};
	
	virtual void addChild(CCNode *pChild, int zOrder, int tag);
	virtual void setColor(ccColor3B color3);
	virtual void setOpacity(GLubyte opacity);
	virtual void setScale(float fScale);
	virtual void setPosition(CCPoint pos);
	virtual void setAnchorPoint(CCPoint anchor);
	virtual void setFlipX(bool bFlipX);
	virtual void setFlipY(bool bFlipY);
	virtual void setRotation(float fRotation);
private:
};

#endif // GN2DMESHDATA_H