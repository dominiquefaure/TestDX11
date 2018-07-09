#ifndef __CORE_IO_JSON_STRING_PROPERTY_H__
#define __CORE_IO_JSON_STRING_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;

class JSonStringProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonStringProperty();
	virtual ~JSonStringProperty();

	/*
	* Get the value
	*/
	const std::string& GetValue( )const;

protected:

	/*
	* Set the value
	*/
	void SetValue( const std::string& a_value );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	std::string	m_value;

};

#endif