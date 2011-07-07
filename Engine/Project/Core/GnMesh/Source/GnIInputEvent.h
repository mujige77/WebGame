#ifndef __Core__GnIInputEvent__
#define __Core__GnIInputEvent__

class GnIInputEvent
{
public:
	enum eEventType 
	{
		PUSH,
		PUSHUP,
		HOVER,
		MOVE,		
	};
private:
	eEventType mEventType;
	float mPointX;
	float mPointY;
	
public:
	GnIInputEvent(eEventType eType, float fPointX, float fPointY) : mEventType( eType )
		, mPointX( fPointX ), mPointY( fPointY )
	{
		
	}
	inline eEventType GetEventType() {
		return mEventType;
	}
	inline float GetPointX() {
		return mPointX;
	}
	inline float GetPointY() {
		return mPointY;
	}
};

#endif
