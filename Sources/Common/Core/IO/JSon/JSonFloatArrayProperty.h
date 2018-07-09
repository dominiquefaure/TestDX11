#ifndef __CORE_IO_JSON_FLOAT_ARRAY_PROPERTY_H__
#define __CORE_IO_JSON_FLOAT_ARRAY_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;

class JSonFloatArrayProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonFloatArrayProperty();
	virtual ~JSonFloatArrayProperty();

	/*
	* Get the number of Elements
	*/
	TUint32 GetCount()const;

	/*
	* Get the value in 64 bits
	*/
	void GetValues64( TFloat64* a_array )const;

	/*
	* Get the value in 32 bits
	*/
	void GetValues32( TFloat32* a_array )const;


protected:

	/*
	* Set the value
	*/
	void SetValues( TUint32 a_count , const TFloat64* a_values );

	/*
	* Set the value
	*/
	void SetValues( TUint32 a_count , const TFloat32* a_values );


	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	TUint32		m_count;

	TFloat64*	m_values;

};
#endif