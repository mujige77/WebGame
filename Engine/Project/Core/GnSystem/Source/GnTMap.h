// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// HashTable.h
// This file holds the Linekd Hash Table implementation.
// ============================================================================


#ifndef GNMAP_H
#define GNMAP_H

#include "GnSystem.h"
#include "GnList.h"
#include "GnTArray.h"


// -------------------------------------------------------
// Name:        GnHashEntry
// Description: This is the hash table entry class. It
//              stores a key and data pair.
// -------------------------------------------------------
template< class KeyType, class DataType >
class GNSYSTEM_ENTRY GnHashEntry : public GnMemoryObject
{
public:
	KeyType m_key;
	DataType m_data;

	~GnHashEntry()
	{
		GnT::PointerTraits<DataType>::SetNull(m_data);
	}
};

template<class KeyType>
class GnDefaultMapHash
{
public:
	static gtuint HashIndex( KeyType key )
	{
		return (gtuint)key;
	}
};

template<class KeyType>
class GnDefaultEqual
{
public:
	static bool IsEqual(KeyType key1, KeyType key2)
	{
		return key1 == key2;
	}
};


template
<
	class KeyType, class DataType,	
	template<class> class DataDeallocate = GnDefaultDeallocate,
	template<class> class MapHash = GnDefaultMapHash,
	template<class> class MapEqual = GnDefaultEqual
>
class GnTMap;


// -------------------------------------------------------
// Name:        HashTable
// Description: This is the hashtable class.
// -------------------------------------------------------

template
<
	class KeyType, class DataType, 	
	template<class> class DataDeallocate,
	template<class> class MapHash,
	template<class> class MapEqual
>
class GNSYSTEM_ENTRY GnTMap : public GnMemoryObject
{
public:
	// typedef the entry class to make is easier to work with.
	typedef GnHashEntry<KeyType, DataType> Entry;
	typedef GnListIterator<Entry, DataDeallocate> Iterator;

protected:
	gtuint m_size;
	gtuint m_count;
	GnTPrimitiveArray< GnList<Entry, DataDeallocate>* > m_table;

public:
	GnTMap( int p_size = 30 ) : m_table( p_size )
	{
		// set the size, hash function, and count.
		m_size = p_size;		
		m_count = 0;
		for (gtuint  i = 0 ; i < m_size ; i++)
		{
			m_table.SetAt(i, GnNew GnList<Entry, DataDeallocate>);
		}
	}
	virtual ~GnTMap()
	{
		RemoveAll();
		for (gtuint i = 0 ; i < m_size ; i++)
			GnDelete m_table.GetAt(i);
	}


	// ----------------------------------------------------------------
	//  Name:           Insert
	//  Description:    Inserts a new key/data pair into the table. 
	//  Arguments:      p_key: the key
	//                  p_data: the data attached to the key.
	//  Return Value:   None
	// ----------------------------------------------------------------
	void Insert( KeyType p_key, DataType p_data )
	{
		GnAssert( Find(p_key) == false );

		// create an entry structure.
		Entry entry;
		SetValue(entry, p_key, p_data);
		// get the hash value from the key, and modulo it
		// so that it fits within the table.
		gtuint index = MapHash<KeyType>::HashIndex( p_key ) % m_size;		
		// add the entry to the correct index, increment the count.
		m_table[index]->Append( entry );
		m_count++;
	}


	// ----------------------------------------------------------------
	//  Name:           Find
	//  Description:    Finds a key in the table
	//  Arguments:      p_key: the key to search for
	//  Return Value:   a pointer to the entry that has the key/data,
	//                  or 0 if not found.
	// ----------------------------------------------------------------
	Entry* Find( KeyType p_key )
	{
		// find out which index the key should exist in
		gtuint index = MapHash<KeyType>::HashIndex( p_key ) % m_size;

		// get an iterator for the list in that index.
		GnListIterator<Entry, DataDeallocate> itr = m_table[index]->GetIterator();

		// search each item
		while( itr.Valid() )
		{
			// if the keys match, then return a pointer to the entry
			if( MapEqual<KeyType>::IsEqual( itr.Item().m_key, p_key ) )
				return &(itr.Item());
			itr.Forth();
		}

		// no match was found, return 0.
		return 0;
	}

	inline void SetAt(KeyType p_key, DataType data, bool bDelete = false)
	{
		Entry* entry = Find(p_key);
		if( entry )
		{
			if( bDelete )
				DataDeallocate<Entry>::Delete(*entry);

			entry->m_data = data;			
			return;
		}

		Insert(p_key, data);
	}

	inline bool GetAt(KeyType p_key, DataType& outData)
	{
		Entry* entry = Find(p_key);
		if( entry == NULL )
			return false;

		outData = entry->m_data;
		return true;
	}


	// ----------------------------------------------------------------
	//  Name:           Remove
	//  Description:    Removes an entry based on key 
	//  Arguments:      p_key: the key
	//  Return Value:   true if removed, false if not found.
	// ----------------------------------------------------------------
	bool Remove( KeyType p_key, bool bDelete = false )
	{
		// find the index that the key should be in.
		gtuint index = MapHash<KeyType>::HashIndex( p_key ) % m_size;

		// get an iterator for the list in that index.
		GnListIterator<Entry, DataDeallocate> itr = m_table[index]->GetIterator();

		// search each item
		while( itr.Valid() )
		{
			// if the keys match, then remove the node, and return true.
			if( MapEqual<KeyType>::IsEqual( itr.Item().m_key, p_key ) )
			{
				ClearValue( itr.Item() );
				m_table[index]->Remove( itr, bDelete );				
				m_count--;
				return true;
			}
			itr.Forth();
		}

		// item wasn't found, return false.
		return false;
	}

	inline void RemoveAll(bool bDelete = false)
	{
		for ( gtuint i = 0 ; i < m_size ; i++ )
		{
			GnListIterator<Entry, DataDeallocate> itr = m_table[i]->GetIterator();
			while( itr.Valid() )
			{
				ClearValue( itr.Item() );
				itr.Forth();
			}
			m_table[i]->RemoveAll(bDelete);
		}
		m_count = 0;
	}

	void GetFirstIter(GnListIterator<Entry, DataDeallocate>& outIter)
	{
		for ( gtuint i = 0 ; i < m_size ; i++ )
		{
			GnListIterator<Entry, DataDeallocate> itr = m_table[i]->GetIterator();
			if( itr.Valid() )
			{
				outIter	= itr;
				return;
			}
		}
		outIter.m_list = NULL;
		outIter.m_node = NULL;
	}

	void GetNextIter(GnListIterator<Entry, DataDeallocate>& inOutIter)
	{
		GnAssert(inOutIter.Valid());
		GnListIterator<Entry, DataDeallocate> outIter = inOutIter;
		outIter.Forth();
		if( outIter.Valid() )
		{
			inOutIter = outIter;
			return;
		}

		Entry ent = inOutIter.Item();
		gtuint i = MapHash<KeyType>::HashIndex( ent.m_key ) % m_size;
		for ( ++i ; i < m_size ; i++ )
		{
			GnListIterator<Entry, DataDeallocate> itr = m_table[i]->GetIterator();
			if( itr.Valid() )
			{
				inOutIter = itr;
				return;
			}
		}
		inOutIter.m_list = NULL;
		inOutIter.m_node = NULL;
	}

	// ----------------------------------------------------------------
	//  Name:           Count
	//  Description:    Gets the number of entries in the table.
	//  Arguments:      None
	//  Return Value:   Number of entries in the table.
	// ----------------------------------------------------------------
	int Count()
	{
		return m_count;
	}

protected:
	virtual void SetValue(Entry& item, KeyType key, DataType val)
	{
		item.m_key = key;
		item.m_data = val;
	}

	virtual void ClearValue(Entry& item)
	{
	}
};

template
<
	class KeyType,
	class DataType,
	template<class> class DataDeallocate = GnObjectMapEntityDeallocate,
	template<class> class MapHash = GnDefaultMapHash,
	template<class> class MapEqual = GnDefaultEqual
>
class GnTObjectDeleteMap;

template
<
	class KeyType,
	class DataType,
	template<class> class DataDeallocate,	
	template<class> class MapHash,
	template<class> class MapEqual
>
class GnTObjectDeleteMap : public GnTMap<KeyType, DataType, DataDeallocate, MapHash, MapEqual>
{
public:
	GnTObjectDeleteMap(gtuint size = 5) : GnTMap(size)
	{

	}
};

#endif // #ifndef GNMAP_H

