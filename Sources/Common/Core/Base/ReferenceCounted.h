#ifndef __CORE_PATTERNS_REFERENCE_COUNTED_H__
#define __CORE_PATTERNS_REFERENCE_COUNTED_H__

class ReferenceCounted
{
public:

	//------------------------------------------------------------------------
	/*
	* Default Constructor
	*/
	ReferenceCounted( bool a_autoDelete) :
	m_autoDelete(a_autoDelete),
	m_count( 0 )
	{
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Reference Constructor
	*/
	ReferenceCounted( const ReferenceCounted& a_ref ) : m_count( 0 )
	{
		// just to make sure that the count is not duplicated

		m_autoDelete										=	a_ref.m_autoDelete;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	virtual ~ReferenceCounted()
	{
		// if the Object is not Referenced
		if( m_count == 0 )
		{
			// delete it
			PerformDelete();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Get the number of times this object is reference
	*/
	inline unsigned int GetReferenceCount()const
	{
		return m_count;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Return true if the reference count is greated than one
	*/
	inline bool IsShared()const
	{
		return (m_count > 0 );
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Increase the Object reference count by 1
	*/
	inline void IncreaseReferenceCount()
	{
		m_count ++;
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Decrease the Object Reference Count by 1.
	* If the counter reach 0, the Object will be deleted
	*/
	inline void DecreaseReferenceCount()
	{
		m_count --;

		// if not referenced anymore , really delete it
		if( m_count == 0 )
		{
			if( m_autoDelete )
			{
				PerformDelete();
			}
			else
			{
				OnUnreferenced();
			}
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Assignement operator
	*/
	ReferenceCounted& operator=( const ReferenceCounted& a_ref )
	{
		// operator defined just to make sure that the counter is not copied

		return *this;
	}
	//------------------------------------------------------------------------


protected:

	//------------------------------------------------------------------------
	/*
	* Release Objects datas
	*/
	virtual void PerformRelease( ){};
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* called for Object that are not auto-delete, when the reference count reach 0
	*/
	virtual void OnUnreferenced(){};
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	/*
	* Delete this Object
	*/
	inline void PerformDelete()
	{
		// perform custom release Operations
		this->PerformRelease();

		// put the count to negative value to be sure it won't be deleted again
		m_count												=	-1;

		// Delete the object
		delete this;
	}
	//------------------------------------------------------------------------

private:

	unsigned int		m_count;

	// does the object get deleted directly when reference count reach 0?
	TBool				m_autoDelete;
};



#endif