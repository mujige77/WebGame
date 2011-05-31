// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NIUISLOT_H
#define NIUISLOT_H

#include <GnTSet.h>

class GnSignal0;
template <typename Arg1Type>
class GnSignal1;
template <typename Arg1Type, typename Arg2Type>
class GnSignal2;

class GnBaseSlot0 : public GnMemoryObject
{
public:
    GnBaseSlot0();
    virtual ~GnBaseSlot0();
    virtual void ReceiveSignal() const = 0;
    void Subscribe(GnSignal0* pkSignal);
    void Unsubscribe(GnSignal0* pkSignal);
    bool IsSubscribed(GnSignal0* pkSignal) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnSignal0*> m_pkSignals;
};

// These two classes only add the function callback pointer and the class
// instance pointer (where needed) to the above Base class
class GnStaticSlot0 : public GnBaseSlot0
{
public:
    GnStaticSlot0();
    GnStaticSlot0(void (*pfnCallback)());
    void Initialize(void (*pfnCallback)());
    virtual ~GnStaticSlot0();
    virtual void ReceiveSignal() const;
protected:
    void (*m_pfnCallback)();
};

template <typename ClassType>
class GnMemberSlot0 : public GnBaseSlot0
{
public:
    GnMemberSlot0();
    GnMemberSlot0(ClassType* pkInstance, void (ClassType::*pfnCallback)());
    void Initialize(ClassType* pkInstance, void (ClassType::*pfnCallback)());
    virtual ~GnMemberSlot0();
    virtual void ReceiveSignal() const;
protected:
    ClassType* m_pkInstance;
    void (ClassType::*m_pfnCallback)();
};

// All one parameter slots must inherit from GnBaseSlot1.  This allows for
// a single signal to emit to slots which call member functions as well as
// non-member or static member functions.
template <typename Arg1Type>
class GnBaseSlot1 : public GnMemoryObject
{
public:
    GnBaseSlot1();
    virtual ~GnBaseSlot1();
    virtual void ReceiveSignal(Arg1Type Arg1) const = 0;
    void Subscribe(GnSignal1<Arg1Type>* pkSignal);
    void Unsubscribe(GnSignal1<Arg1Type>* pkSignal);
    bool IsSubscribed(GnSignal1<Arg1Type>* pkSignal) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnSignal1<Arg1Type>*> m_pkSignals;
};

// These two classes only add the function callback pointer and the class
// instance pointer (where needed) to the above Base class
template <typename Arg1Type>
class GnStaticSlot1 : public GnBaseSlot1<Arg1Type>
{
public:
    GnStaticSlot1();
    GnStaticSlot1(void (*pfnCallback)(Arg1Type));
    void Initialize(void (*pfnCallback)(Arg1Type));
    virtual ~GnStaticSlot1();
    virtual void ReceiveSignal(Arg1Type Arg1) const;
protected:
    void (*m_pfnCallback)(Arg1Type);
};

template <typename ClassType, typename Arg1Type>
class GnMemberSlot1 : public GnBaseSlot1<Arg1Type>
{
public:
    GnMemberSlot1();
    GnMemberSlot1(ClassType* pkInstance, 
        void (ClassType::*pfnCallback)(Arg1Type));
    void Initialize(ClassType* pkInstance, 
        void (ClassType::*pfnCallback)(Arg1Type));
    virtual ~GnMemberSlot1();
    virtual void ReceiveSignal(Arg1Type Arg1) const;
protected:
    ClassType* m_pkInstance;
    void (ClassType::*m_pfnCallback)(Arg1Type);
};

// All two parameter slots must inherit from GnBaseSlot2.  This allows for
// a single signal to emit to slots which call member functions as well as
// non-member or static member functions.
template <typename Arg1Type, typename Arg2Type>
class GnBaseSlot2 : public GnMemoryObject
{
public:
    GnBaseSlot2();
    virtual ~GnBaseSlot2();
    virtual void ReceiveSignal(Arg1Type Arg1, Arg2Type Arg2) const = 0;
    void Subscribe(GnSignal2<Arg1Type, Arg2Type>* pkSignal);
    void Unsubscribe(GnSignal2<Arg1Type, Arg2Type>* pkSignal);
    bool IsSubscribed(GnSignal2<Arg1Type, Arg2Type>* pkSignal) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnSignal2<Arg1Type, Arg2Type>*> m_pkSignals;
};

// These two classes only add the function callback pointer and the class
// instance pointer (where needed) to the above Base class
template <typename Arg1Type, typename Arg2Type>
class GnStaticSlot2 : public GnBaseSlot2<Arg1Type, Arg2Type>
{
public:
    GnStaticSlot2();
    GnStaticSlot2(void (*pfnCallback)(Arg1Type, Arg2Type));
    void Initialize(void (*pfnCallback)(Arg1Type, Arg2Type));
    virtual ~GnStaticSlot2();
    virtual void ReceiveSignal(Arg1Type Arg1, Arg2Type Arg2) const;
protected:
    void (*m_pfnCallback)(Arg1Type, Arg2Type);
};

template <typename ClassType, typename Arg1Type, typename Arg2Type>
class GnMemberSlot2 : public GnBaseSlot2<Arg1Type, Arg2Type>
{
public:
    GnMemberSlot2();
    GnMemberSlot2(ClassType* pkInstance, 
        void (ClassType::*pfnCallback)(Arg1Type, Arg2Type));
    void Initialize(ClassType* pkInstance, 
        void (ClassType::*pfnCallback)(Arg1Type, Arg2Type));
    virtual ~GnMemberSlot2();
    virtual void ReceiveSignal(Arg1Type Arg1, Arg2Type Arg2) const;
protected:
    ClassType* m_pkInstance;
    void (ClassType::*m_pfnCallback)(Arg1Type, Arg2Type);
};

#include "GnSignalSlotMacros.h"
#include "GnSignal.h"

inline GnBaseSlot0::GnBaseSlot0()
{
}

inline GnBaseSlot0::~GnBaseSlot0()
{
	GnUnsubscribeFromAll(m_pkSignals);
}

inline void GnBaseSlot0::Subscribe(GnSignal0* pkSignal)
{
	GnSubscribeToMe(m_pkSignals, pkSignal);
}

inline void GnBaseSlot0::Unsubscribe(GnSignal0* pkSignal)
{
	GnUnsubscribeToMe(m_pkSignals, pkSignal);
}

inline bool GnBaseSlot0::IsSubscribed(GnSignal0* pkSignal) const
{
	return GnIsElementInGroup(m_pkSignals, pkSignal);
}

inline unsigned int GnBaseSlot0::NumSubscribed() const
{
	return GnNumElements(m_pkSignals);
}

inline GnStaticSlot0::GnStaticSlot0() : GnBaseSlot0(), m_pfnCallback(NULL)
{
}

inline GnStaticSlot0::GnStaticSlot0(void (*pfnCallback)()) :  GnBaseSlot0(), m_pfnCallback(pfnCallback)
{
	GnAssert(pfnCallback != NULL);
}

inline void GnStaticSlot0::Initialize(void (*pfnCallback)()) 
{
	GnAssert(pfnCallback != NULL);
	m_pfnCallback = pfnCallback;
}

inline GnStaticSlot0::~GnStaticSlot0()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	m_pfnCallback = NULL;
}
inline void GnStaticSlot0::ReceiveSignal() const
{
	GnAssert(m_pfnCallback != NULL);
	(*m_pfnCallback)();
}
template <typename ClassType> inline
	GnMemberSlot0<ClassType>::GnMemberSlot0() : m_pkInstance(NULL), m_pfnCallback(NULL)
{
}

template <typename ClassType> inline
	GnMemberSlot0<ClassType>::GnMemberSlot0(ClassType* pkInstance,  void (ClassType::*pfnCallback)())
	: m_pkInstance(pkInstance), m_pfnCallback(pfnCallback)
{
	GnAssert(pkInstance != NULL);
	GnAssert(pfnCallback != NULL);
}

template <typename ClassType> inline
	void GnMemberSlot0<ClassType>::Initialize(ClassType* pkInstance, void (ClassType::*pfnCallback)()) 
{
	GnAssert(pkInstance != NULL);
	GnAssert(pfnCallback != NULL);
	m_pkInstance = pkInstance,
		m_pfnCallback = pfnCallback;
}

template <typename ClassType> inline
	GnMemberSlot0<ClassType>::~GnMemberSlot0()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	m_pkInstance = NULL;
	m_pfnCallback = NULL;
}

template <typename ClassType> inline
	void GnMemberSlot0<ClassType>::ReceiveSignal() const
{
	GnAssert(m_pkInstance != NULL);
	GnAssert(m_pfnCallback != NULL);
	(m_pkInstance->*m_pfnCallback)();
}

template <typename Arg1Type> inline
	GnBaseSlot1<Arg1Type>::GnBaseSlot1()
{
}

template <typename Arg1Type> inline GnBaseSlot1<Arg1Type>::~GnBaseSlot1()
{
	GnUnsubscribeFromAll(m_pkSignals);
}

template <typename Arg1Type> inline
	void GnBaseSlot1<Arg1Type>::Subscribe(GnSignal1<Arg1Type>* pkSignal)
{
	GnSubscribeToMe(m_pkSignals, pkSignal);
}

template <typename Arg1Type> inline
	void GnBaseSlot1<Arg1Type>::Unsubscribe(GnSignal1<Arg1Type>* pkSignal)
{
	GnUnsubscribeToMe(m_pkSignals, pkSignal);
}

template <typename Arg1Type> inline
	bool GnBaseSlot1<Arg1Type>::IsSubscribed(GnSignal1<Arg1Type>* pkSignal) 
	const
{
	return GnIsElementInGroup(m_pkSignals, pkSignal);
}

template <typename Arg1Type> inline unsigned int GnBaseSlot1<Arg1Type>::NumSubscribed() const
{
	return GnNumElements(m_pkSignals);
}

template <typename Arg1Type>
inline GnStaticSlot1<Arg1Type>::GnStaticSlot1() : GnBaseSlot1<Arg1Type>(), m_pfnCallback(NULL)
{
}

template <typename Arg1Type> inline GnStaticSlot1<Arg1Type>::GnStaticSlot1(
	void (*pfnCallback)(Arg1Type)) : GnBaseSlot1<Arg1Type>(), m_pfnCallback(pfnCallback)
{
	GnAssert(pfnCallback != NULL);
}

template <typename Arg1Type> inline
	void GnStaticSlot1<Arg1Type>::Initialize(void (*pfnCallback)(Arg1Type)) 
{
	GnAssert(pfnCallback != NULL);
	m_pfnCallback = pfnCallback;
}

template <typename Arg1Type> inline
	GnStaticSlot1<Arg1Type>::~GnStaticSlot1()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	m_pfnCallback = NULL;
}

template <typename Arg1Type> inline
	void GnStaticSlot1<Arg1Type>::ReceiveSignal(Arg1Type Arg1) const
{
	GnAssert(m_pfnCallback != NULL);
	(*m_pfnCallback)(Arg1);
}

template <typename ClassType, typename Arg1Type> inline
	GnMemberSlot1<ClassType, Arg1Type>::GnMemberSlot1() : GnBaseSlot1<Arg1Type>()
	, m_pkInstance(NULL), m_pfnCallback(NULL)
{
}

template <typename ClassType, typename Arg1Type> inline
	GnMemberSlot1<ClassType, Arg1Type>::GnMemberSlot1(ClassType* pkInstance, 
	void (ClassType::*pfnCallback)(Arg1Type)) : GnBaseSlot1<Arg1Type>(), m_pkInstance(pkInstance)
	, m_pfnCallback(pfnCallback)
{
	GnAssert(pkInstance != NULL);
	GnAssert(pfnCallback != NULL);
}

template <typename ClassType, typename Arg1Type> inline
	void GnMemberSlot1<ClassType, Arg1Type>::Initialize(ClassType* pkInstance, 
	void (ClassType::*pfnCallback)(Arg1Type)) 
{
	GnAssert(pkInstance != NULL);
	GnAssert(pfnCallback != NULL);
	m_pkInstance = pkInstance;
	m_pfnCallback = pfnCallback;
}

template <typename ClassType, typename Arg1Type> inline
	GnMemberSlot1<ClassType, Arg1Type>::~GnMemberSlot1()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	m_pkInstance = NULL;
	m_pfnCallback = NULL;
}

template <typename ClassType, typename Arg1Type> inline
	void GnMemberSlot1<ClassType, Arg1Type>::ReceiveSignal(Arg1Type Arg1) const
{
	GnAssert(m_pkInstance != NULL);
	GnAssert(m_pfnCallback != NULL);
	(m_pkInstance->*m_pfnCallback)(Arg1);
}

template <typename Arg1Type, typename Arg2Type> inline
	GnBaseSlot2<Arg1Type, Arg2Type>::GnBaseSlot2()
{
}

// All code in GnUIBaseSlot* methods are implemented in the macros defined in
// GnUISignalSlotMacros.h.
template <typename Arg1Type, typename Arg2Type> inline
	GnBaseSlot2<Arg1Type, Arg2Type>::~GnBaseSlot2()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	GnUnsubscribeFromAll(m_pkSignals);
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnBaseSlot2<Arg1Type, Arg2Type>::Subscribe(GnSignal2<Arg1Type, Arg2Type>* pkSignal)
{
	GnSubscribeToMe(m_pkSignals, pkSignal);
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnBaseSlot2<Arg1Type, Arg2Type>::Unsubscribe(GnSignal2<Arg1Type, Arg2Type>* pkSignal)
{
	GnUnsubscribeToMe(m_pkSignals, pkSignal);
}

template <typename Arg1Type, typename Arg2Type>
inline bool GnBaseSlot2<Arg1Type, Arg2Type>::IsSubscribed(GnSignal2<Arg1Type, Arg2Type>* pkSignal) const
{
	return GnIsElementInGroup(m_pkSignals, pkSignal);
}

template <typename Arg1Type, typename Arg2Type>
inline unsigned int GnBaseSlot2<Arg1Type, Arg2Type>::NumSubscribed() const
{
	return GnNumElements(m_pkSignals);
}

template <typename Arg1Type, typename Arg2Type>
inline GnStaticSlot2<Arg1Type, Arg2Type>::GnStaticSlot2() : GnBaseSlot2<Arg1Type, Arg2Type>()
	, m_pfnCallback(NULL)
{
}

template <typename Arg1Type, typename Arg2Type> inline
	GnStaticSlot2<Arg1Type, Arg2Type>::GnStaticSlot2(void (*pfnCallback)(Arg1Type, Arg2Type))
	: GnBaseSlot2<Arg1Type, Arg2Type>(), m_pfnCallback(pfnCallback)
{
	GnAssert(pfnCallback != NULL);
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnStaticSlot2<Arg1Type, Arg2Type>::Initialize(void (*pfnCallback)(Arg1Type, Arg2Type)) 
{
	GnAssert(pfnCallback != NULL);
	m_pfnCallback = pfnCallback;
}

template <typename Arg1Type, typename Arg2Type> inline
	GnStaticSlot2<Arg1Type, Arg2Type>::~GnStaticSlot2()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	m_pfnCallback = NULL;
}

template <typename Arg1Type, typename Arg2Type>
inline void GnStaticSlot2<Arg1Type, Arg2Type>::ReceiveSignal(Arg1Type Arg1, Arg2Type Arg2) const
{
	GnAssert(m_pfnCallback != NULL);
	(*m_pfnCallback)(Arg1, Arg2);
}

template <typename ClassType, typename Arg1Type, typename Arg2Type>
inline GnMemberSlot2<ClassType, Arg1Type, Arg2Type>::GnMemberSlot2()
	: GnBaseSlot2<Arg1Type, Arg2Type>(), m_pkInstance(NULL), m_pfnCallback(NULL)
{
}

template <typename ClassType, typename Arg1Type, typename Arg2Type>
inline GnMemberSlot2<ClassType, Arg1Type, Arg2Type>::GnMemberSlot2(ClassType* pkInstance
	, void (ClassType::*pfnCallback)(Arg1Type, Arg2Type)) : GnBaseSlot2<Arg1Type, Arg2Type>(),
	m_pkInstance(pkInstance), m_pfnCallback(pfnCallback)
{
	GnAssert(m_pkInstance != NULL);
	GnAssert(m_pfnCallback != NULL);
}

template <typename ClassType, typename Arg1Type, typename Arg2Type> inline
	void GnMemberSlot2<ClassType, Arg1Type, Arg2Type>::Initialize(ClassType* pkInstance
	, void (ClassType::*pfnCallback)(Arg1Type, Arg2Type))
{
	GnAssert(m_pkInstance != NULL);
	GnAssert(m_pfnCallback != NULL);

	m_pkInstance = pkInstance;
	m_pfnCallback = pfnCallback;
}

template <typename ClassType, typename Arg1Type, typename Arg2Type> inline
	GnMemberSlot2<ClassType, Arg1Type, Arg2Type>::~GnMemberSlot2()
{
	m_pkInstance = NULL;
	m_pfnCallback = NULL;
}

template <typename ClassType, typename Arg1Type, typename Arg2Type> inline
	void GnMemberSlot2<ClassType, Arg1Type, Arg2Type>::ReceiveSignal(Arg1Type Arg1, Arg2Type Arg2) const
{
	GnAssert(m_pkInstance != NULL);
	GnAssert(m_pfnCallback != NULL);
	(m_pkInstance->*m_pfnCallback)(Arg1, Arg2);
}



#endif // NIUISLOT_H

