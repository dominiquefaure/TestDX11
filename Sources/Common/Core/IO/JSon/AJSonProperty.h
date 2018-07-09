#ifndef __CORE_IO_A_JSON_PROPERTY_H__
#define __CORE_IO_A_JSON_PROPERTY_H__

#include "../../../Core/Base/Includes.h"
#include "JsonEnums.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class JSonNode;

class AJsonProperty
{
	friend class JSonNode;
public:

	AJsonProperty();
	virtual ~AJsonProperty();

	/*
	* Get the Type of Item this Property Represent
	*/
	JSonPropertyType GetType()const;

	/*
	* Get the name of the property
	*/
	const std::string& GetName()const;


protected:

	/*
	* Set the property Name
	*/
	void SetName( const std::string& a_name );

	/*
	* Serialize this Property
	*/
	void Serialize( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer ) {}

// Properties
protected:

	// the Type of the Property
	JSonPropertyType	m_type;

	// Name of the Property
	std::string			m_name;

};



#endif