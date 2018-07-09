#ifndef __CORE_IO_JSON_NODE_WRITER_H__
#define __CORE_IO_JSON_NODE_WRITER_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonIntArrayProperty;
class JSonFloatArrayProperty;
class JSonNodeArrayProperty;
class JSonNodeProperty;

class JSonReader;
class JSonWriter;

class JSonNodeWriter
{
	friend class JSonReader;
	friend class JSonWriter;
	friend class JSonNodeProperty;
	friend class JSonNodeArrayProperty;

public:

	JSonNodeWriter();
	~JSonNodeWriter();

	/////////
	// Accessors
	////////

	/*
	* Get the number of property
	*/
	TUint32 GetPropertyCount()const;

	/*
	* Get the property present at the given index
	*/
	AJsonProperty* GetPropertyAt( TUint32 a_index );

	/*
	* Get the property with the given name
	*/
	AJsonProperty* GetProperty( const std::string& a_name )const;

	/*
	* Get the Bool property value
	*/
	TBool GetBoolProperty( const std::string& a_name )const;

	/*
	* Get the Bool property value
	*/
	TUint64 GetIntProperty( const std::string& a_name , TUint64 a_defaultValue = 0 )const;

	/*
	* Get the Bool property value
	*/
	TFloat64 GetFloatProperty( const std::string& a_name )const;

	/*
	* Get the Bool property value
	*/
	const std::string& GetStringProperty( const std::string& a_name )const;

	/*
	* Get sub node property
	*/
	const JSonNodeWriter* GetNodeProperty( const std::string& a_name )const;

	/*
	* Get a Int Array property
	*/
	const JSonIntArrayProperty* GetIntArray( const std::string& a_name )const;

	/*
	* Get a Float Array property
	*/
	const JSonFloatArrayProperty* GetFloatArray( const std::string& a_name )const;

	/*
	* Get a node Array property
	*/
	const JSonNodeArrayProperty* GetNodeArray( const std::string& a_name )const;


	/////////
	// Modificators
	////////

	/*
	* Add a bool property
	*/
	void AddBoolProperty( const std::string& a_name , TBool a_value );

	/*
	* Add a bool property
	*/
	void AddIntProperty( const std::string& a_name , TUint64 a_value );

	/*
	* Add a Float property
	*/
	void AddFloatProperty( const std::string& a_name , TFloat64 a_value );

	/*
	* Add a bool property
	*/
	void AddStringProperty( const std::string& a_name , const std::string& a_value );

	/*
	* Add a Int array property 
	*/
	void AddIntArray( const std::string& a_name , TUint32 a_count , const TUint64* a_values );

	/*
	* Add a Int array property 
	*/
	void AddIntArray( const std::string& a_name , TUint32 a_count , const TUint32* a_values );

	/*
	* Add a Int array property 
	*/
	void AddIntArray( const std::string& a_name , TUint32 a_count , const TUint16* a_values );



	/*
	* Add a float array property 
	*/
	void AddFloatArray( const std::string& a_name , TUint32 a_count , const TFloat64* a_values );

	/*
	* Add a float array property 
	*/
	void AddFloatArray( const std::string& a_name , TUint32 a_count , const TFloat32* a_values );

	/*
	* add an Empty Node property
	* return the Node so we can populate it
	*/
	JSonNodeWriter* AddNodeProperty( const std::string& a_name );

	/*
	* add an Empty Node property
	* return the Node so we can populate it
	*/
	JSonNodeArrayProperty* AddNodeArrayProperty( const std::string& a_name );

protected:


	void Parse( const rapidjson::Value& a_value );

	void ParseProperty( const std::string& a_name , const rapidjson::Value& a_property );

	void ProcessArrayProperty( const std::string& a_name , const rapidjson::Value& a_property );

	void ProcessNodeArrayProperty( const std::string& a_name , const rapidjson::Value& a_property );
	void ProcessIntArrayProperty( const std::string& a_name , const rapidjson::Value& a_property );
	void ProcessFloatArrayProperty( const std::string& a_name , const rapidjson::Value& a_property );

	/*
	* Serialize this Node content
	*/
	void Serialize( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	// list of Properties
	std::vector<AJsonProperty*> m_properties;
};

#endif