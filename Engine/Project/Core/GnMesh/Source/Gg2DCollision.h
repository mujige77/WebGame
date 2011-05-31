#ifndef GGCOLLISION_H
#define GGCOLLISION_H

class Gg2DCollision : public GnMemoryObject
{
public:
	enum eCollisionType
	{
		BOX_BODY,
		BOX_ATTACK,
		COLLISION_MAX,
	};
		 
public:
	Gg2DCollision(){};
	virtual ~Gg2DCollision(){};
	
private:
};

#endif // GGCOLLISION_H