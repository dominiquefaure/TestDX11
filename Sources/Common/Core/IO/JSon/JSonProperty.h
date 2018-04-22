#ifndef __JSON_PROPERTY_H__
#define __JSON_PROPERTY_H__



#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace rapidjson;


#include "JsonEnums.h"

#include "../../Base/BaseDataTypes.h"



class JSonNode;

/*
* Represent a Property froma JSon Object
*/
class JSonProperty
{

	friend class JSonNode;


public:

	/*
	* Get the Type of Item this Property Represent
	*/
	JSonPropertyType GetType();


	/*
	* Get the Bool value of this Property
	*/
	bool GetBool( )const;

	/*
	* Get the Int32 value of this Property
	*/
	int32_t GetInt32()const;

	/*
	* Get the Int64 value of this Property
	*/
	int64_t GetInt64()const;

	/*
	* Get the value of a Float Property
	*/
	float GetFloat(  )const;

	/*
	* Get the value of a Double Property
	*/
	double GetDouble( )const;

	/*
	* Get the value of a String Property
	*/
	const char* GetString(  )const;


	bool IsJSonObject()const;

	/*
	* Ge the JSonObject stored in this property
	*/
	JSonNode GetJSonObject();

	/*
	* evalaute if this Property represent an Array
	*/
	bool IsArray()const;


	/*
	* If this property represent an array, return the type of the elements presents inside ( use 1st element type )
	*/
	JSonPropertyType GetArrayElementType();

	/*
	* Get the Number of elements presents in this array Property
	*/
	int GetArraySize()const;

	/*
	* Fill the Array with Int32 values presents inside this Array Property
	*
	* return the number of Elements set
	*/
	int GetInt32Array( int* a_array , int a_size );

	/*
	* Fill the Array with Int32 values presents inside this Array Property
	*
	* return the number of Elements set
	*/
	TUint32 GetInt64Array( TUint64* a_array , TUint32 a_size );


	/*
	* Fill the Array with int values , 32 or 64 presents inside this Array Property
	*
	* return the number of Elements set
	*/
	int GetShortArray( int16_t* a_array , int a_size );


	/*
	* Fill the Array with float values  presents inside this Array Property
	*
	* return the number of Elements set
	*/
	int GetFloatArray( float* a_array , int a_size );


	JSonProperty GetArrayElementAt( int a_index );

	JSonNode GetSubNodeAt( int a_index );

private:
	
	JSonProperty();
	JSonProperty( Value* t_value );

	/*
	* Set the Value and then the type 
	*/
	void SetValue( Value* t_value );

	/*
	* Get the Property type for the Given JSON value
	*/
	JSonPropertyType GetJSonPropertyType( const rapidjson::Value* a_jsonValue );

private:

	JSonPropertyType	m_type;

	Value*				m_jsonValue;
};


#endif