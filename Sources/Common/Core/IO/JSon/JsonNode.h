#ifndef __CORE_IO_JSON_NODE_H__
#define __CORE_IO_JSON_NODE_H__


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace rapidjson;

#include "../../Base/BaseDataTypes.h"

#include "JsonEnums.h"


class JsonDocument;
class JSonProperty;

class JSonNode
{
	friend class JsonDocument;
	friend class JSonProperty;

public:


	/*
	* Does the Gvien property belong to this Node
	*/
	bool Contains( const std::string & a_propertyName );

	/*
	* get the type of the Given Property
	*/
	JSonPropertyType GetPropertyType( const std::string & a_propertyName ); 

	/*
	* Get the value of a Bool Property
	*/
	TBool GetBoolProperty( const std::string & a_propertyName , TBool a_defaultValue = false );

	/*
	* Get the value of a Int Property
	*/
	TUint32 GetInt32Property( const std::string & a_propertyName , TUint32 a_defaultValue = 0 );


	/*
	* Get the value of a Int Property
	*/
	TUint64 GetInt64Property( const std::string & a_propertyName , TUint64 a_defaultValue = 0 );

	/*
	* Get the value of a Float Property
	*/
	TFloat32 GetFloatProperty( const std::string & a_propertyName , TFloat32 a_defaultValue = 0.0f );

	/*
	* Get the value of a Double Property
	*/
	TFloat64 GetDoubleProperty( const std::string & a_propertyName , TFloat64 a_defaultValue = 0.0f );

	/*
	* Get the value of a String Property
	*/
	const char* GetStringProperty( const std::string & a_propertyName );

	/*
	* Get a Sub Node property
	*/
	JSonNode GetNodeProperty( const std::string & a_propertyName );



	/*
	* evalaute if this node represent an Array
	*/
	bool HaveSubNodes();

	int GetSubNodeCount();

	JSonNode GetSubNodeAt(int a_index);

	/*
	* Get the Property with the Given Name
	*/
	JSonProperty GetProperty(const std::string & a_propertyName);

private:

	JSonNode();
	JSonNode(Value* t_value);


	void SetNode(Value* t_value);


private:
	Value * m_jsonNode;


};


#endif