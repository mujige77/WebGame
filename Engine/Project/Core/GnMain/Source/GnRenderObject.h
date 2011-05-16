#ifndef GNRENDEROBJECT_H
#define GNRENDEROBJECT_H

#include "GnProperty.h"

class GnTransform;
class GnRenderer;
class GNMAIN_ENTRY GnRenderObject : public GnAVObject
{
	GnDeclareRTTI;
	GnDeclareAbstractStream;
public:
	GnRenderObject(GnTransform* pTrans);
	virtual ~GnRenderObject(){};
	virtual void RnderObject(GnRenderer* pRenderer) = 0;

	inline void AttachProperty(GnProperty* pProperty)
	{
		GnAssert( mPropertys.GetSize() == 0 );
		mPropertys.Add(pProperty);
		GnLogA( "AttachProperty" );
	}
	inline void DetachProperty(GnProperty* pProperty)
	{
		mPropertys.RemoveAndFill(pProperty);
		GnLogA( "DetachProperty" );
	}

	inline GnProperty* GetProperty(gtuint uiType)
	{
		for ( gtuint i = 0 ; i < mPropertys.GetSize() ; i++ )
		{
			if( mPropertys[i]->GetType() == uiType )
				return mPropertys[i];
		}
		return NULL;
	}

protected:
	GnTObjectArray<GnPropertyPtr> mPropertys;	

private:	
};

#endif // GNRENDEROBJECT_H