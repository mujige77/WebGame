#ifndef GNSMRENDERVIEW_H
#define GNSMRENDERVIEW_H

class GnSMRenderView : public GnRenderView
{
public:
	GnSMRenderView(){};
	virtual ~GnSMRenderView(){};

public:
	virtual void Update(float fTime);

protected:
	virtual void AddToPVGeometryArray(GnObjectForm* object);
};

#endif // GNSMRENDERVIEW_H
