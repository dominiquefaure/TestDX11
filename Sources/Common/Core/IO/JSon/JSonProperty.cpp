#include "JSonProperty.h"
#include "JsonNode.h"



//--------------------------------------------------------------------------
JSonProperty::JSonProperty()
{
	m_jsonValue												=	NULL;
	m_type													=	JSON_PROPERTY_TYPE_NONE;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
JSonProperty::JSonProperty( Value* a_value )
{
	m_jsonValue												=	a_value;
	m_type													=	GetJSonPropertyType( m_jsonValue );
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void JSonProperty::SetValue( Value* a_value )
{
	m_jsonValue												=	a_value;
	m_type													=	GetJSonPropertyType( m_jsonValue );
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
JSonPropertyType JSonProperty::GetJSonPropertyType( const rapidjson::Value* a_jsonValue )
{
	if( a_jsonValue != NULL )
	{
		if( a_jsonValue->IsBool() )
		{
			return JSON_PROPERTY_TYPE_BOOL;
		}

		if( a_jsonValue->IsString() )
		{
			return JSON_PROPERTY_TYPE_STRING;
		}

		if( a_jsonValue->IsFloat() )
		{
			return JSON_PROPERTY_TYPE_FLOAT;
		}

		if( a_jsonValue->IsDouble() )
		{
			return JSON_PROPERTY_TYPE_DOUBLE;
		}

		if( a_jsonValue->IsInt64() )
		{
			return JSON_PROPERTY_TYPE_INT64;
		}

		if( a_jsonValue->IsInt() )
		{
			return JSON_PROPERTY_TYPE_INT32;
		}

		if( a_jsonValue->IsArray() )
		{
			return JSON_PROPERTY_TYPE_ARRAY;
		}

		if( a_jsonValue->IsObject() )
		{
			return JSON_PROPERTY_TYPE_NODE;
		}
	}

	return JSON_PROPERTY_TYPE_NONE;
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
JSonPropertyType JSonProperty::GetType()
{
	return m_type;
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
bool JSonProperty::GetBool( )const
{
	if( m_type == JSON_PROPERTY_TYPE_BOOL )
	{
		return m_jsonValue->GetBool();
	}

	return false;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int32_t JSonProperty::GetInt32()const
{
	if( m_type == JSON_PROPERTY_TYPE_INT32 )
	{
		return m_jsonValue->GetInt();
	}

	return 0;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int64_t JSonProperty::GetInt64()const
{
	if( m_type == JSON_PROPERTY_TYPE_INT64 )
	{
		return m_jsonValue->GetInt64();
	}

	return 0;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
float JSonProperty::GetFloat( )const
{
	if( m_type == JSON_PROPERTY_TYPE_FLOAT )
	{
		return m_jsonValue->GetFloat();
	}

	return 0.0f;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
double JSonProperty::GetDouble( )const
{
	if( m_type == JSON_PROPERTY_TYPE_DOUBLE )
	{
		return m_jsonValue->GetDouble();
	}

	return 0.0f;

}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
const char* JSonProperty::GetString( )const
{
	if( m_type == JSON_PROPERTY_TYPE_STRING )
	{
		return m_jsonValue->GetString();
	}

	return "";
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool JSonProperty::IsJSonObject()const
{
	return ( m_type == JSON_PROPERTY_TYPE_NODE );
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
JSonNode JSonProperty::GetJSonObject()
{
	if( IsJSonObject() )
	{
		return JSonNode( m_jsonValue );
	}

	return JSonNode();
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool JSonProperty::IsArray()const
{
	return ( m_type == JSON_PROPERTY_TYPE_ARRAY );
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
JSonPropertyType JSonProperty::GetArrayElementType()
{
	if(  m_type == JSON_PROPERTY_TYPE_ARRAY )
	{
		JSonProperty t_element								=	GetArrayElementAt( 0 );
		return t_element.GetType();
	}

	return JSON_PROPERTY_TYPE_NONE;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int JSonProperty::GetArraySize()const
{
	if( m_type == JSON_PROPERTY_TYPE_ARRAY )
	{
		return m_jsonValue->Size();
	}
	return 0;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int JSonProperty::GetInt32Array( int* a_array , int a_size )
{
	// validate the Type match
	if( GetArrayElementType() == JSON_PROPERTY_TYPE_INT32 ) 
	{
		int t_size											=	GetArraySize();
		if( t_size > a_size )
		{
			t_size											=	a_size;
		}

		for( int i = 0 ; i < t_size ; i ++ )
		{
			a_array[ i ]									=	(*m_jsonValue)[ i ].GetInt();
		}

		return t_size;
	}

	return a_size;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
TUint32 JSonProperty::GetInt64Array( TUint64* a_array , TUint32 a_size )
{
	// validate the Type match
	if( GetArrayElementType() == JSON_PROPERTY_TYPE_INT64 ) 
	{
		TUint32 t_size										=	GetArraySize();
		if( t_size > a_size )
		{
			t_size											=	a_size;
		}

		for( int i = 0 ; i < t_size ; i ++ )
		{
			a_array[ i ]									=	(*m_jsonValue)[ i ].GetInt64();
		}

		return t_size;
	}

	return a_size;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int JSonProperty::GetShortArray( int16_t* a_array , int a_size )
{
	JSonPropertyType t_type									=	GetArrayElementType();

	if( ( t_type == JSON_PROPERTY_TYPE_INT64 ) || ( t_type == JSON_PROPERTY_TYPE_INT32 ) )
	{
		int t_size											=	GetArraySize();
		if( t_size > a_size )
		{
			t_size											=	a_size;
		}

		for( int i = 0 ; i < t_size ; i ++ )
		{
			a_array[ i ]									=	(int16_t)(*m_jsonValue)[ i ].GetInt64();
		}

		return t_size;
	
	}


	return 0;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int JSonProperty::GetFloatArray( float* a_array , int a_size )
{
	// validate the Type match
	if( GetArrayElementType() == JSON_PROPERTY_TYPE_FLOAT ) 
	{
		int t_size											=	GetArraySize();
		if( t_size > a_size )
		{
			t_size											=	a_size;
		}

		for( int i = 0 ; i < t_size ; i ++ )
		{
			a_array[ i ]									=	(*m_jsonValue)[ i ].GetFloat();
		}

		return t_size;
	}

	return a_size;

}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
JSonProperty JSonProperty::GetArrayElementAt( int a_index )
{
	Value& t_subNode										=	(*m_jsonValue)[a_index ];

	return JSonProperty( &t_subNode );
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
JSonNode JSonProperty::GetSubNodeAt( int a_index )
{
	JSonProperty t_property									=	GetArrayElementAt( a_index );

	return t_property.GetJSonObject();
}
//--------------------------------------------------------------------------

