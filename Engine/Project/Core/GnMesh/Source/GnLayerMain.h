#ifndef GNLAYERMAIN_H
#define GNLAYERMAIN_H
#include "GnLayerBackground.h"

class GnLayerMain : public GnLayer
{
protected:
	GnLayerBackground* mpBackground;

public:
	GnLayerMain();
	virtual ~GnLayerMain(){};

	bool CreateBackgroundFromFile(const gchar* fileName);

	inline GnLayerBackground* GetBackground() {
		return mpBackground;
	}
	inline void SetBackground(GnLayerBackground* val) {
		mpBackground = val;
	}
};

#endif // GNLAYERMAIN_H