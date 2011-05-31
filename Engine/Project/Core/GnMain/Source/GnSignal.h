#ifndef NIUISIGNAL_H
#define NIUISIGNAL_H

#include <GnTSet.h>
class GnBaseSlot0;
template <typename Arg1Type>
class GnBaseSlot1;
template <typename Arg1Type, typename Arg2Type>
class GnBaseSlot2;

class GnSignal0 : public GnMemoryObject
{
public:
    GnSignal0();
    virtual ~GnSignal0();
    void EmitSignal() const;
    void Subscribe(GnBaseSlot0* pkSlot);
    void Unsubscribe(GnBaseSlot0* pkSlot);
    bool IsSubscribed(GnBaseSlot0* pkSlot) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnBaseSlot0*> m_pkSlots;
};

template <typename Arg1Type>
class GnSignal1 : public GnMemoryObject
{
public:
    GnSignal1();
    virtual ~GnSignal1();
    void EmitSignal(Arg1Type Arg1) const;
    void Subscribe(GnBaseSlot1<Arg1Type>* pkSlot);
    void Unsubscribe(GnBaseSlot1<Arg1Type>* pkSlot);
    bool IsSubscribed(GnBaseSlot1<Arg1Type>* pkSlot) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnBaseSlot1<Arg1Type>*> m_pkSlots;
};

template <typename Arg1Type, typename Arg2Type>
class GnSignal2 : public GnMemoryObject
{
public:
    GnSignal2();
    virtual ~GnSignal2();
    void EmitSignal(Arg1Type Arg1, Arg2Type Arg2) const;
    void Subscribe(GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot);
    void Unsubscribe(GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot);
    bool IsSubscribed(GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot) const;
    unsigned int NumSubscribed() const;
protected:
    GnTPrimitiveSet <GnBaseSlot2<Arg1Type, Arg2Type>*> m_pkSlots;
};

#include "GnSignalSlotMacros.h"
#include "GnSignalSlot.h"
inline GnSignal0::GnSignal0()
{
}

// All code in NiUISignal* methods are implemented in the macros defined in
// NiUISignalSlotMacros.h.
inline GnSignal0::~GnSignal0()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	GnUnsubscribeFromAll(m_pkSlots);
}

inline void GnSignal0::EmitSignal() const
{
	GnEmitSignalToAll(m_pkSlots, ());
}

inline void GnSignal0::Subscribe(GnBaseSlot0* pkSlot)
{
	GnSubscribeToMe(m_pkSlots, pkSlot);
}

inline void GnSignal0::Unsubscribe(GnBaseSlot0* pkSlot)
{
	GnUnsubscribeToMe(m_pkSlots, pkSlot);
}

inline bool GnSignal0::IsSubscribed(GnBaseSlot0* pkSlot) const
{
	return GnIsElementInGroup(m_pkSlots, pkSlot);
}

inline unsigned int GnSignal0::NumSubscribed() const
{
	return GnNumElements(m_pkSlots);
}

template <typename Arg1Type>
inline GnSignal1<Arg1Type>::GnSignal1()
{
}

template <typename Arg1Type>
inline GnSignal1<Arg1Type>::~GnSignal1()
{
	GnUnsubscribeFromAll(m_pkSlots);
}

template <typename Arg1Type> 
inline void GnSignal1<Arg1Type>::EmitSignal(Arg1Type Arg1) const
{
	GnEmitSignalToAll(m_pkSlots, (Arg1));
}

template <typename Arg1Type>
inline void GnSignal1<Arg1Type>::Subscribe(GnBaseSlot1<Arg1Type>* pkSlot)
{
	GnSubscribeToMe(m_pkSlots, pkSlot);
}

template <typename Arg1Type> inline
	void GnSignal1<Arg1Type>::Unsubscribe(GnBaseSlot1<Arg1Type>* pkSlot)
{
	GnUnsubscribeToMe(m_pkSlots, pkSlot);
}

template <typename Arg1Type> inline
	bool GnSignal1<Arg1Type>::IsSubscribed(GnBaseSlot1<Arg1Type>* pkSlot) const
{
	return GnIsElementInGroup(m_pkSlots, pkSlot);
}

template <typename Arg1Type> inline
	unsigned int GnSignal1<Arg1Type>::NumSubscribed() const
{
	return GnNumElements(m_pkSlots);
}

template <typename Arg1Type, typename Arg2Type> inline
	GnSignal2<Arg1Type, Arg2Type>::GnSignal2()
{
}

// All code in NiUISignal* methods are implemented in the macros defined in
// NiUISignalSlotMacros.h.
template <typename Arg1Type, typename Arg2Type> inline
	GnSignal2<Arg1Type, Arg2Type>::~GnSignal2()
{
	// Note: None of the pointers in any of these destructors is owned by
	// this instance: Therefore, it should not delete them
	GnUnsubscribeFromAll(m_pkSlots);
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnSignal2<Arg1Type, Arg2Type>::EmitSignal(Arg1Type Arg1, Arg2Type Arg2) 
	const
{
	GnEmitSignalToAll(m_pkSlots, (Arg1, Arg2));
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnSignal2<Arg1Type, Arg2Type>::Subscribe(
	GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot)
{
	GnSubscribeToMe(m_pkSlots, pkSlot);
}

template <typename Arg1Type, typename Arg2Type> inline
	void GnSignal2<Arg1Type, Arg2Type>::Unsubscribe(GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot)
{
	GnUnsubscribeToMe(m_pkSlots, pkSlot);
}

template <typename Arg1Type, typename Arg2Type> inline
	bool GnSignal2<Arg1Type, Arg2Type>::IsSubscribed(GnBaseSlot2<Arg1Type, Arg2Type>* pkSlot) const
{
	return GnIsElementInGroup(m_pkSlots, pkSlot);
}

template <typename Arg1Type, typename Arg2Type> inline
	unsigned int GnSignal2<Arg1Type, Arg2Type>::NumSubscribed() const
{
	return GnNumElements(m_pkSlots);
}



#endif // NIUISIGNAL_H

