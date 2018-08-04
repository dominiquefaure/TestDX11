#ifndef __REFERENCE_COUNTED_PTR_H__
#define __REFERENCE_COUNTED_PTR_H__

/*
* Smart pointer for Reference counted objects
*/
template<class T>
class ReferenceCountedPtr
{
public:

	//------------------------------------------------------------------------
	ReferenceCountedPtr( void ) : m_pointer( NULL )
	{
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	ReferenceCountedPtr( T* a_object )
	{
		// save pointer to the Object
		m_pointer											=	a_object;

		// if the pointer is not NULL, increase it' refernce count ( Need to be a ReferenceCounted objectg ! )
		if( m_pointer )
		{
			m_pointer->IncreaseReferenceCount();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	ReferenceCountedPtr( const ReferenceCountedPtr& a_ptr )
	{
		m_pointer											=	a_ptr.m_pointer;

		// if the pointer is not NULL, increase it' refernce count ( Need to be a ReferenceCounted objectg ! )
		if( m_pointer )
		{
			m_pointer->IncreaseReferenceCount();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	~ReferenceCountedPtr()
	{
		// if the pointer is not NULL, decrease it' refernce count ( Need to be a ReferenceCounted object ! )
		if( m_pointer )
		{
			m_pointer->DecreaseReferenceCount();
		}
	}
	//------------------------------------------------------------------------



	//------------------------------------------------------------------------
	/*
	* return true if this object point to a valid pointer
	*/
	inline bool IsValid()const
	{
		return ( m_pointer != nullptr );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	inline ReferenceCountedPtr& operator=( const ReferenceCountedPtr& a_ptr )
	{
		//if we want to assign the same pointer, just return this one
		if( m_pointer == a_ptr.m_pointer )
		{
			return *this;
		}

		// decrease reference count of the current object pointed, as we don't refernce it anymore
		if( m_pointer != nullptr )
		{
			m_pointer->DecreaseReferenceCount();
		}

		// update the pointer
		m_pointer											=	a_ptr.m_pointer;

		// Increase the counter for the new object pointed
		if( m_pointer != nullptr )
		{
			m_pointer->IncreaseReferenceCount();
		}

		return *this;
	
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* if the Object is not valid, force the game to crash
	*/
	inline T& operator* (void)
	{
		return *m_pointer;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* if the Object is not valid, force the game to crash
	*/
	inline const T& operator* (void) const
	{
		return *m_pointer;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Allow to use like a standard pointer
	* if the Object is not valid, force the game to crash
	*/
	inline T* operator-> (void)
	{
		return m_pointer;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Allow to use like a standard pointer
	* if the Object is not valid, force the game to crash
	*/
	inline const T* operator-> (void)const
	{
		return m_pointer;
	}
	//------------------------------------------------------------------------


	//------------------------------------------------------------------------
	inline bool operator!()const
	{
	    return ( m_pointer == nullptr );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Check if it's the same pointer
	*/
	inline bool operator == ( const ReferenceCountedPtr& a_ptr )const
	{
	    return ( m_pointer == a_ptr.m_pointer );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Check if it's the same pointer
	*/
	inline bool operator == ( const T* a_ptr )const
	{
	    return ( m_pointer == a_ptr );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Check if it's not the same pointer
	*/
	inline bool operator != ( const ReferenceCountedPtr& a_ptr )const
	{
	    return ( m_pointer != a_ptr.m_pointer );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Check if it's not the same pointer
	*/
	inline bool operator != ( const T* a_ptr )const
	{
	    return ( m_pointer != a_ptr );
	}
	//------------------------------------------------------------------------


private:

	// pointer to the ReferenceCounted object
	T*	m_pointer;

};


#endif