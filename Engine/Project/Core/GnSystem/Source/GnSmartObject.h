#ifndef GNTSMARTPOINTER_H
#define GNTSMARTPOINTER_H
#include "GnSystemDefine.h"
#include "GnMemoryObject.h"

class GNSYSTEM_ENTRY GnSmartObject : public GnMemoryObject
{
public:
	inline GnSmartObject() : mRefCount(0)
	{}
	virtual ~GnSmartObject()
	{}
	inline void IncRefCount()
	{
		GnAtomicIncrement(mRefCount);
	}
	inline void DecRefCount()
	{
		if( GnAtomicDecrement(mRefCount) == 0 )
			DeleteThis();
	}
	inline guint32  GetRefCount()
	{
		return mRefCount;
	}
	virtual void DeleteThis()
	{
		GnDelete this;
	}

private:
	guint32 mRefCount;
};

template <class T> class GnPointer : public GnMemoryObject
{
public:
    // construction and destruction
    inline GnPointer(T* pObject = (T*) 0)
	{
		m_pObject = pObject;
		if (m_pObject)
			m_pObject->IncRefCount();
	}
    inline GnPointer(const GnPointer& ptr)
	{
		m_pObject = ptr.m_pObject;
		if (m_pObject)
			m_pObject->IncRefCount();
	}
    ~GnPointer()
	{
		if (m_pObject)
			m_pObject->DecRefCount();
	}

    // implicit conversions
    GNFORCEINLINE operator T*() const
	{
		return m_pObject;
	}
    GNFORCEINLINE T& operator*() const
	{
		return *m_pObject;
	}
    GNFORCEINLINE T* operator->() const
	{
		return m_pObject;
	}

    // assignment
    inline GnPointer& operator=(const GnPointer& ptr)
	{
		if (m_pObject != ptr.m_pObject)
		{
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = ptr.m_pObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

    inline GnPointer& operator=(T* pObject)
	{
		if (m_pObject != pObject)
		{
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = pObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

    GNFORCEINLINE bool operator==(T* pObject) const
	{
		return (m_pObject == pObject);
	}
    GNFORCEINLINE bool operator!=(T* pObject) const
	{
		return (m_pObject != pObject);
	}
    GNFORCEINLINE bool operator==(const GnPointer& ptr) const
	{
		return (m_pObject == ptr.m_pObject);
	}
	GNFORCEINLINE bool operator!=(const GnPointer& ptr) const
	{
		return (m_pObject != ptr.m_pObject);
	}

protected:
    // the managed pointer
    T* m_pObject;
};

#define GnSmartPointer(classname) \
class classname; \
	typedef GnPointer<classname> classname##Ptr

#endif // GNTSMARTPOINTER_H