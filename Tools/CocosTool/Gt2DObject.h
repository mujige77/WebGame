#pragma once
class Gt2DObject : public GtObject
{
public:
	const static  gint OBJECT_TYPE = 0;

protected:

public:
	Gt2DObject(void);
	virtual ~Gt2DObject(void);

	virtual gint8 GetType() {
		return OBJECT_TYPE;
	}
};

