#ifndef __CORE_PATTERNS_REFERENCE_COUNTED_H__
#define __CORE_PATTERNS_REFERENCE_COUNTED_H__

class ReferenceCounted
{
public:

	//------------------------------------------------------------------------
	/*
	* Default Constructor
	*/
	ReferenceCounted() : m_count( 0 )
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
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	virtual ~ReferenceCounted()
	{
		// do nothing !!
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
			PerformDelete();
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
	* Delete this Object
	*/
	inline void PerformDelete()
	{
		// perform custom release Operations
		this->PerformRelease();

		// Delete the object
		delete this;
	}
	//------------------------------------------------------------------------

private:

	unsigned int		m_count;
};



#endif