#ifndef GNTALLOCATORCOLLECTION_H
#define GNTALLOCATORCOLLECTION_H

template <class T> class GnTMallocInterface 
{
public:
	static T* Allocate(unsigned int uiNumElements)
	{return GnAlloc(T, uiNumElements);};
	static void Deallocate(T* pArray)
	{GnFree(pArray);};
};

template <class T> class GnTNewInterface 
{
public:
	static T* Allocate(unsigned int uiNumElements)
	{return GnNew T[uiNumElements];};
	static void Deallocate(T* pArray)
	{GnDelete [] pArray;}; 
};

template <class T> class GnTExternalNewInterface 
{
public:
	static T* Allocate(unsigned int uiNumElements)
	{return GnExternalNew T[uiNumElements];};
	static void Deallocate(T* pArray)
	{GnExternalDelete [] pArray;}; 
};

template<typename DataType>
class GnDefaultDeallocate
{
public:
	inline static void Delete(DataType&)
	{
	}
};

template<typename DataType>
class GnPrimitiveDeallocate
{
public:
	inline static void Delete(DataType& data)
	{
		if( data )
			GnFree( data );
	}
};

template<typename DataType>
class GnPrimitiveMapEntityDeallocate
{
public:
	inline static void Delete(DataType& data)
	{
		if( data.m_data )
			GnFree( data.m_data );
	}
};

template<typename DataType>
class GnObjectDeallocate
{
public:
	inline static void Delete(DataType& data)
	{
		if( data )
			GnDelete data;
	}
};

template<typename DataType>
class GnObjectMapEntityDeallocate
{
public:
	inline static void Delete(DataType& data)
	{
		if( data.m_data )
			GnDelete data.m_data;
	}
};


#endif // GNTALLOCATORCOLLECTION_H