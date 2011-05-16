#ifndef GNSMMANAGER_H
#define GNSMMANAGER_H

class GNMESH_ENTRY GnSMManager : public GnMemoryObject
{
protected:
	static GnSMManager* mspSingleton;
	guint mDisplayWidth;
	guint mDisplayHeight;

public:
	GnSMManager();
	virtual ~GnSMManager(){};

	static void Create();
	static void Destory();
	static GnSMManager* GetSingleton();	

	void ChangeDisplay(guint uiWidth, guint uiHeight);
	bool ConvertToVertexRect(GnIRect& rectDisplay, GnFRect& outRect);	
};

#endif // GNSMMANAGER_H
