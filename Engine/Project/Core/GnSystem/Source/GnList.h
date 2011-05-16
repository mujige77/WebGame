// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// GnList.h
// This is the Doubly-Linked List class
// ============================================================================
#ifndef GNLIST_H
#define GNLIST_H
#include "GnSystem.h"
#include "GnTAllocatorCollection.h"


// forward declarations of all the classes in this file
template<class Datatype> class GnListNode;
template< class Datatype, template <class> class DataDeallocate = GnDefaultDeallocate >
class GnListIterator;

template< class Datatype, template <class> class DataDeallocate = GnDefaultDeallocate >
class GnList;

//template< class Datatype, template <class> class DataDeallocate = GnDefaultDeallocate >
//struct GnListDef
//{
//	typedef GnList<Datatype, DataDeallocate> type;
//};



// -------------------------------------------------------
// Name:        GnListNode
// Description: This is the Doubly-linked list node class.
// -------------------------------------------------------
template<class Datatype>
class GNSYSTEM_ENTRY GnListNode : public GnMemoryObject
{
public:


	// ----------------------------------------------------------------
	//  Name:           m_data
	//  Description:    This is the data in the node.
	// ----------------------------------------------------------------
	Datatype m_data;

	// ----------------------------------------------------------------
	//  Name:           m_next
	//  Description:    This is a pointer to the next node in the list
	// ----------------------------------------------------------------
	GnListNode<Datatype>* m_next;

	// ----------------------------------------------------------------
	//  Name:           m_previous
	//  Description:    This is a pointer to the last node in the list
	// ----------------------------------------------------------------
	GnListNode<Datatype>* m_previous;

	~GnListNode()
	{
		GnT::PointerTraits<Datatype>::SetNull(m_data);
	}
	// ----------------------------------------------------------------
	//  Name:           DeLink
	//  Description:    This delinks this node from the list it is in.
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Delink()
	{
		// if a previous node exists, then make the previous
		// node point to the next node.
		if( m_previous != 0 )
			m_previous->m_next = m_next;

		// if the next node exists, then make the next node
		// point to the previous node.
		if( m_next != 0 )
			m_next->m_previous = m_previous;
	}


	// ----------------------------------------------------------------
	//  Name:           InsertAfter
	//  Description:    This adds a node after the current node.
	//  Arguments:      p_data - The data to store in the new node.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void InsertAfter( Datatype p_data )
	{
		// create the new node.
		GnListNode<Datatype>* newnode = GnNew GnListNode<Datatype>;
		newnode->m_data = p_data;

		// set up newnode's pointers.
		newnode->m_next     = m_next;
		newnode->m_previous = this;

		// if there is a node after this one, make it point to
		// newnode
		if( m_next != 0 )
			m_next->m_previous = newnode;

		// make the current node point to newnode.
		m_next = newnode;
	}


	// ----------------------------------------------------------------
	//  Name:           InsertBefore
	//  Description:    This adds a node before the current node.
	//  Arguments:      p_data - The data to store in the new node.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void InsertBefore( Datatype p_data )
	{
		// create the new node.
		GnListNode<Datatype>* newnode = GnNew GnListNode<Datatype>;
		newnode->m_data = p_data;

		// set up newnode's pointers.
		newnode->m_next     = this;
		newnode->m_previous = m_previous;

		// if there is a node before this one, make it point to
		// newnode
		if( m_previous != 0 )
			m_previous->m_next = newnode;

		// make the current node point to newnode.
		m_previous = newnode;
	}


};

// -------------------------------------------------------
// Name:        GnList
// Description: This is the Doubly-linked list container.
// -------------------------------------------------------
template< class Datatype, template <class> class DataDeallocate >
class GNSYSTEM_ENTRY GnList : public GnMemoryObject
{
public:

	// ----------------------------------------------------------------
	//  Name:           GnList
	//  Description:    Constructor; creates an empty list
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	GnList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}


	// ----------------------------------------------------------------
	//  Name:           GnList
	//  Description:    Destructor; destroys every node
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	~GnList()
	{
		RemoveAll();
	}

	inline void RemoveAll(bool bDelete = false) 
	{
		// temporary node pointers.
		GnListNode<Datatype>* node = m_head;
		GnListNode<Datatype>* next;

		while( node != 0 )
		{
			next = node->m_next;
			if( bDelete )
				DataDeallocate<Datatype>::Delete(node->m_data);
			GnDelete node;
			node = next;
		}

		m_head = NULL;
	}

	// ----------------------------------------------------------------
	//  Name:           Append
	//  Description:    Adds a new node to the end of a list
	//  Arguments:      p_data - the data to be added.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Append( Datatype p_data )
	{
		// if there is no head node (ie: list is empty)
		if( m_head == 0 )
		{
			// create a new head node.
			m_head = m_tail = GnNew GnListNode<Datatype>;
			m_head->m_data = p_data;
			m_head->m_next = 0;
			m_head->m_previous = 0;
		}
		else
		{
			// insert a new node after the tail, and reset the tail.
			m_tail->InsertAfter( p_data );
			m_tail = m_tail->m_next;
		}
		m_count++;
	}


	// ----------------------------------------------------------------
	//  Name:           Prepend
	//  Description:    Addss a new node to the beginning of a list
	//  Arguments:      p_data - the data to be added.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Prepend( Datatype p_data )
	{
		// if there is no head node (ie: list is empty)
		if( m_head == 0 )
		{
			// create a new head node.
			m_head = m_tail = GnNew GnListNode<Datatype>;
			m_head->m_data = p_data;
			m_head->m_next = 0;
			m_head->m_previous = 0;
		}
		else
		{
			// insert a new node before the head, and reset the head.
			m_head->InsertBefore( p_data );
			m_head = m_head->m_previous;
		}
		m_count++;
	}

	// ----------------------------------------------------------------
	//  Name:           RemoveHead
	//  Description:    This removes the very first node in the list.
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	inline void RemoveHead(bool bDelete = false)
	{
		GnListNode<Datatype>* node = 0;

		if( m_head != 0 )
		{
			// make node point to the next node.
			node = m_head->m_next;

			// then delete the head, and make the pointer
			// point to node.
			if( bDelete )
				DataDeallocate<Datatype>::Delete(m_head->m_data);
			GnDelete m_head;
			m_head = node;

			// if the head is null, then we've just deleted the only node
			// in the list. set the tail to 0.
			// if not, set the previous pointer to 0.
			if( m_head == 0 )
				m_tail = 0;
			else
				m_head->m_previous = 0;

			m_count--;
		}
	}

	inline void RemoveTail(bool bDelete = false)
	{
		GnListNode<Datatype>* node = 0;

		if( m_tail != 0 )
		{
			// make node point to the next node.
			node = m_tail->m_previous;

			// then delete the head, and make the pointer
			// point to node.
			if( bDelete )
				DataDeallocate<Datatype>::Delete(m_tail->m_data);
			GnDelete m_tail;
			m_tail = node;

			// if the tail is null, then we've just deleted the only node
			// in the list. set the head to 0.
			// if not, set the next pointer to 0.
			if( m_tail == 0 )
				m_head = 0;
			else
				m_tail->m_next = 0;

			m_count--;
		}
	}

	void InsertAfter( GnListIterator<Datatype, DataDeallocate>& p_iterator, Datatype p_data )
	{
		if( p_iterator.m_node != 0 )
		{
			// insert the data after the iterator
			p_iterator.m_node->InsertAfter( p_data );

			// if the iterator was the tail of the list,
			// reset the tail pointer
			if( p_iterator.m_node == m_tail )
				m_tail = m_tail->m_next;

			// increment the count
			m_count++;
		}
		else
		{
			Append( p_data );
		}
	}

	void InsertBefore( GnListIterator<Datatype, DataDeallocate>& p_iterator, Datatype p_data )
	{
		if( p_iterator.m_node != 0 )
		{
			// insert the data before the iterator
			p_iterator.m_node->InsertBefore( p_data );

			// if the iterator was the head of the list,
			// reset the head pointer.
			if( p_iterator.m_node == m_head )
				m_head = m_head->m_previous;

			// increment the count
			m_count++;
		}
		else
		{
			Prepend( p_data );
		}
	}


	// ----------------------------------------------------------------
	//  Name:           Remove
	//  Description:    Removes the node that the iterator points to.
	//                  moves iterator forward to the next node.
	//  Arguments:      p_iterator: The iterator to remove
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Remove( GnListIterator<Datatype, DataDeallocate>& p_iterator, bool bDelete = false )
	{
		// temporary node pointer.
		GnListNode<Datatype>* node;

		// if node is invalid, do nothing.
		if( p_iterator.m_node == 0 )
			return;


		// save the pointer to the node we want to delete.
		node = p_iterator.m_node;

		// if the node we want to remove is the head or the tail
		// nodes, then move the head or tail to the next or
		// previous node.
		if( node == m_head )
		{
			m_head = m_head->m_next;
		}
		else if( node == m_tail )
		{
			m_tail = m_tail->m_previous;
		}

		// move the iterator forward to the next valid node
		p_iterator.Forth();

		// delink and delete the node.
		node->Delink();
		if( bDelete )
			DataDeallocate<Datatype>::Delete(node->m_data);
		GnDelete node;

		// if the head is 0, then set the tail to 0 as well.
		if( m_head == 0 )
			m_tail = 0;

		m_count--;
	}



	// ----------------------------------------------------------------
	//  Name:           GetIterator
	//  Description:    Gets an iterator pointing to the beginning
	//                  of the list.
	//  Arguments:      None.
	//  Return Value:   iterator pointing to the beginning of the list.
	// ----------------------------------------------------------------
	GnListIterator<Datatype, DataDeallocate> GetIterator()
	{
		return GnListIterator<Datatype, DataDeallocate>( this, m_head );
	}


	// ----------------------------------------------------------------
	//  Name:           Size
	//  Description:    Gets the size of the list
	//  Arguments:      None.
	//  Return Value:   size of the list.
	// ----------------------------------------------------------------
	gtuint GetCount()
	{
		return m_count;
	}


	// ----------------------------------------------------------------
	//  Name:           SaveToDisk
	//  Description:    Saves the linked list to disk.
	//  Arguments:      p_filename: name of the file to save to.
	//  Return Value:   true, if successful
	// ----------------------------------------------------------------
	bool SaveToDisk( char* p_filename )
	{
		FILE* outfile = 0;
		GnListNode<Datatype>* itr = m_head;

		// open the file
		outfile = fopen( p_filename, "wb" );

		// return if it couldn't be opened
		if( outfile == 0 )
			return false;

		// write the size of the list first
		fwrite( &m_count, sizeof( int ), 1, outfile );

		// now loop through and write the list.
		while( itr != 0 )
		{
			fwrite( &(itr->m_data), sizeof( Datatype ), 1, outfile );
			itr = itr->m_next;
		}

		fclose( outfile );

		// return success.
		return true;
	}


	// ----------------------------------------------------------------
	//  Name:           ReadFromDisk
	//  Description:    Reads a linked list from a file.
	//  Arguments:      p_filename: the name of the file to read from
	//  Return Value:   true if successful.
	// ----------------------------------------------------------------
	bool ReadFromDisk( char* p_filename )
	{
		FILE* infile = 0;
		Datatype buffer;
		int count = 0;

		// open the file
		infile = fopen( p_filename, "rb" );

		// return if it couldn't be opened
		if( infile == 0 )
			return false;

		// read the size of the list first
		fread( &count, sizeof( int ), 1, infile );

		// now loop through and read the list.
		while( count != 0 )
		{
			fread( &buffer, sizeof( Datatype ), 1, infile );
			Append( buffer );
			count--;
		}

		fclose( infile );

		// return success.
		return true;
	}


	// ----------------------------------------------------------------
	//  Name:           m_head
	//  Description:    The first node in the list
	// ----------------------------------------------------------------
	GnListNode<Datatype>* m_head;

	// ----------------------------------------------------------------
	//  Name:           m_tail
	//  Description:    The last node in the list
	// ----------------------------------------------------------------
	GnListNode<Datatype>* m_tail;

	// ----------------------------------------------------------------
	//  Name:           m_count
	//  Description:    The number of nodes in the list
	// ----------------------------------------------------------------
	gtuint m_count;
};




// -------------------------------------------------------
// Name:        GnListIterator
// Description: This is the basic linked list 
//              iterator class.
// -------------------------------------------------------
template<class Datatype, template <class> class DataDeallocate>
class GNSYSTEM_ENTRY GnListIterator
{
public:


	// ----------------------------------------------------------------
	//  Name:           GnListIterator
	//  Description:    Constructor, creates an iterator that points
	//                  to the given list and node. 
	//  Arguments:      p_list: pointer to the list the iterator belongs
	//                          to.
	//                  p_node: pointer to the current node.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	GnListIterator( GnList<Datatype, DataDeallocate>* p_list = 0,
		GnListNode<Datatype>* p_node = 0 )
	{
		m_list = p_list;
		m_node = p_node;
	}


	// ----------------------------------------------------------------
	//  Name:           Start
	//  Description:    Resets the iterator to the beginning of the 
	//                  list
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Start()
	{
		if( m_list != 0 )
			m_node = m_list->m_head;
	}

	// ----------------------------------------------------------------
	//  Name:           End
	//  Description:    Resets the iterator to the end of the list
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void End()
	{
		if( m_list != 0 )
			m_node = m_list->m_tail;
	}


	// ----------------------------------------------------------------
	//  Name:           Forth
	//  Description:    Moves the iterator forward by one position
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Forth()
	{
		if( m_node != 0 )
			m_node = m_node->m_next;
	}


	// ----------------------------------------------------------------
	//  Name:           Back
	//  Description:    Moves the iterator backward by one position.
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Back()
	{
		if( m_node != 0 )
			m_node = m_node->m_previous;
	}


	// ----------------------------------------------------------------
	//  Name:           Item
	//  Description:    Gets the item that the iterator is pointing to.
	//  Arguments:      None.
	//  Return Value:   Reference to the data in the node.
	// ----------------------------------------------------------------
	Datatype& Item()
	{
		return m_node->m_data;
	}


	// ----------------------------------------------------------------
	//  Name:           Valid
	//  Description:    Determines if the node is valid.
	//  Arguments:      None.
	//  Return Value:   true if valid
	// ----------------------------------------------------------------
	bool Valid()
	{
		return (m_node != 0);
	}

	bool Valid() const 
	{
		return (m_node != 0);
	}


	// ----------------------------------------------------------------
	//  Name:           operator==
	//  Description:    Determines if two iterators point to the same
	//                  node.
	//  Arguments:      None.
	//  Return Value:   true if they point to the same node.
	// ----------------------------------------------------------------
	bool operator==( GnListIterator<Datatype, DataDeallocate>& p_rhs )
	{
		if( m_node == p_rhs.m_node && m_list == p_rhs.m_list )
		{
			return true;
		}
		return false;
	}



	// ----------------------------------------------------------------
	//  Name:           m_node
	//  Description:    pointer to the current node
	// ----------------------------------------------------------------
	GnListNode<Datatype>* m_node;


	// ----------------------------------------------------------------
	//  Name:           m_list
	//  Description:    pointer to the current list.
	// ----------------------------------------------------------------
	GnList<Datatype, DataDeallocate>* m_list;
};

template<class Datatype, class FindType>
inline bool GnListFindPos(GnList<Datatype>& gnList, FindType& findData, GnListIterator<Datatype>& outIter)
{
	outIter = gnList.GetIterator();
	while( outIter.Valid() )
	{
		if( findData == outIter.Item() )
			return true;

		outIter.Forth();
	}
	return false;
}

template<class Datatype, template<class> class Deallocate, class FindType>
inline bool GnListRemove(GnList<Datatype, Deallocate>& gnList, FindType& findData, bool bDelete = false)
{
	GnListIterator<Datatype> outIter;
	if( GnListFindPos(gnList, findData, outIter) )
	{
		gnList.Remove(outIter, bDelete);
		return true;
	}
	return false;
}

#endif // #ifndef GNLIST_H

