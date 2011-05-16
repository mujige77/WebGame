#ifndef GNOBJECTFORM_H
#define GNOBJECTFORM_H

class GNMAIN_ENTRY GnObjectForm : public GnObject
{
	GnDeclareRTTI;
	GnDeclareAbstractStream;
private:
	GnSimpleString mName;

public:
	GnObjectForm();
	virtual ~GnObjectForm(){};

public:

	virtual GnObjectForm* GetObjectByName(const GnSimpleString& kName);

	inline GnSimpleString& GetName() {
		return mName;
	}
	inline void SetName(const gchar* val) { mName = val; }

};

GnSmartPointer(GnObjectForm);

#endif // GNOBJECTFORM_H