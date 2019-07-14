#ifndef __CORE_CONTAINERS_ARRAY_H__
#define __CORE_CONTAINERS_ARRAY_H__

#include "Core/CoreMacros.h"
#include "Core/Base/BaseDataTypes.h"

#include <vector>
#include <assert.h>

template<typename T> class TArray
{

public:

	//-------------------------------------------------------------------------------------------------
	TArray()
	{
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	~TArray()
	{
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	FORCE_INLINE TUint32 Count()const
	{
		return m_items.size();
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	FORCE_INLINE T& operator[]( TUint32 a_index )
	{
		CheckRange( a_index );

		return m_items[ a_index ];
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	* Add a new Item to the Array
	*/
	FORCE_INLINE void Add( T a_value )
	{
		m_items.push_back( a_value );
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	* Remove the given element
	*/
	FORCE_INLINE void Remove( T a_value )
	{
		// Get the index of the element in the Array
		TUint32 t_index										=	IndexOf( a_value );

		// if found
		if( t_index != -1 )
		{
			// remove it
			RemoveAtImp( t_index , 1 );
		}
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	* Remove an element at the Given index
	*/
	FORCE_INLINE void RemoveAt( TUint32 a_index )
	{
		RemoveAtImp( a_index , 1 );
	}
	//-------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------
	/*
	* Get the index of the element in the Array, -1 if not found
	*/
	FORCE_INLINE TUint32 IndexOf( T a_value )
	{
		int t_index											=	0;
		for( auto it = m_items.begin() ; it != m_items.end() ; it ++ , t_index ++)
		{
			if(*it == a_value )
			{
				return t_index;
			}
		}
		return -1;
	}
	//-------------------------------------------------------------------------------------------------

// Methods
private:

	//-------------------------------------------------------------------------------------------------
	/*
	* Validate the range is valid
	*/
	FORCE_INLINE void CheckRange( TUint32 a_index )
	{
		assert( ( ( a_index >= 0 ) && ( a_index < m_items.size() ) ) , "Index out of Range" );
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	* Effectively remove the elements
	*/
	void RemoveAtImp( TUint32 a_index , TUint32 a_count )
	{
		m_items.erase( m_items.begin() + a_index );
	}
	//-------------------------------------------------------------------------------------------------

private:


	// Vectgor that store the different items
	std::vector<T>	m_items;
};

#endif
