#ifndef __CORE_IO_JSON_INT_ARRAY_PROPERTY_H__
#define __CORE_IO_JSON_INT_ARRAY_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;

class JSonIntArrayProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonIntArrayProperty();
	virtual ~JSonIntArrayProperty();

	/*
	* Get the number of Elements
	*/
	TUint32 GetCount()const;

	/*
	* Get the Value present at the given index in the array
	*/
	TUint64 GetValueAt( TUint32 a_index )const;

	/*
	* Get the value in 64 bits
	*/
	void GetValues64( TUint64* a_array )const;

	/*
	* Get the value in 32 bits
	*/
	void GetValues32( TUint32* a_array )const;

	/*
	* Get the value in 16 bits
	*/
	void GetValues16( TUint16* a_array )const;

protected:

	/*
	* Set the value
	*/
	void SetValues( TUint32 a_count , const TUint64* a_values );

	/*
	* Set the value
	*/
	void SetValues( TUint32 a_count , const TUint32* a_values );

	/*
	* Set the value
	*/
	void SetValues( TUint32 a_count , const TUint16* a_values );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	TUint32	m_count;

	TUint64*	m_values;

};
#endif