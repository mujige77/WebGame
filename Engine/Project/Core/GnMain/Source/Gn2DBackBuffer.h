#ifndef GN2DBACKBUFFER_H
#define GN2DBACKBUFFER_H

class GNMAIN_ENTRY Gn2DBackBuffer : public GnSmartObject
{
protected:
	guint muiWidth;	
	guint muiHeight;

public:
	virtual ~Gn2DBackBuffer();

	virtual bool Display() = 0;

	inline guint GetWidth() const { return muiWidth; }
	inline void SetWidth(guint val) { muiWidth = val; }
	inline guint GetHeight() const { return muiHeight; }
	inline void SetHeight(guint val) { muiHeight = val; }
};

GnSmartPointer(Gn2DBackBuffer);

#endif // GN2DBACKBUFFER_H