#define GnDeclareFlagsFuncs(type, reftype) \
	reftype void SetField(type uVal, type uMask, type uPos) \
		{ \
		m_uFlags = (m_uFlags & ~uMask) | (uVal << uPos); \
		} \
		reftype type GetField(type uMask, type uPos) \
		{ \
		return (m_uFlags & uMask) >> uPos; \
		} \
		reftype void SetBit(bool bVal, type uMask) \
		{ \
		if (bVal) \
			{ \
			m_uFlags |= uMask; \
			} \
			else \
			{ \
			m_uFlags &= ~uMask; \
			} \
		}\
		reftype bool GetBit(type uMask) \
		{ \
		return (m_uFlags & uMask) != 0; \
		}

#define GnDeclareFlags(type) \
	private: \
	type m_uFlags; \
	GnDeclareFlagsFuncs(type, private:)
#define GnStaticDeclareFlags(type) \
	private: \
	static type m_uFlags; \
	GnDeclareFlagsFuncs(type, static)

#define GnStaticDeclareFlagsInit(className, type) type className::m_uFlags = 0;