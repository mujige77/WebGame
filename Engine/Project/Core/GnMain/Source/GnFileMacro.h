namespace GnT
{
	template<> struct TypeTraits<GnVector2> : TypeTraitsAux<1>
	{
		inline static bool TestMax(GnVector2& val) {
			return true;
		}
	};
	template<> struct TypeTraits<GnVector3> : TypeTraitsAux<1>
	{
		inline static bool TestMax(GnVector3& val) {
			return true;
		}
	};
}
	