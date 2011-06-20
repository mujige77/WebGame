//
//  GLayer.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GLayer__
#define __HiroCat__GLayer__
#include <cocos2d.h>
		
class GLayer : public CCLayer
{
public:
	inline void AddChild(Gn2DMeshObject* pObject) {
		addChild( pObject->GetMesh() );
	}
	inline void AddChild(Gn2DMeshObject* pObject, int iZOrder) {
		addChild( pObject->GetMesh(), iZOrder );
	}
	inline void AddChild(Gn2DMeshObject* pObject, int iZOrder, int iTag) {
		addChild( pObject->GetMesh(), iZOrder, iTag );
	}
	
	inline void RemoveChild(Gn2DMeshObject* pObject) {
		removeChild( pObject->GetMesh(), true );
	}
};

#endif
