#ifndef __CORE_IO_JSON_INT_PROPERTY_H__
#define __CORE_IO_JSON_INT_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNodeWriter;


class JSonIntProperty : public AJsonProperty
{
	friend class JSonNodeWriter;

public:

	JSonIntProperty();
	virtual ~JSonIntProperty();

	/*
	* Get the value in 64 bits
	*/
	TUint64 GetValue( )const;

protected:

	/*
	* Set the value
	*/
	void SetValue( TUint64 a_value );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	TUint64	m_value;

};


#endif