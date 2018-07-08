#ifndef __CORE_IO_JSON_FLOAT_PROPERTY_H__
#define __CORE_IO_JSON_FLOAT_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNodeWriter;

class JSonFloatProperty : public AJsonProperty
{
	friend class JSonNodeWriter;

public:

	JSonFloatProperty();
	virtual ~JSonFloatProperty();

	/*
	* Get the value
	*/
	TFloat64 GetValue( )const;

protected:

	/*
	* Set the value
	*/
	void SetValue( TFloat64 a_value );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	TFloat64	m_value;

};

#endif