#include "JSonNodeWriter.h"

#include "JSonBoolProperty.h"
#include "JSonIntProperty.h"
#include "JSonFloatProperty.h"
#include "JSonStringProperty.h"
#include "JSonNodeProperty.h"

#include "JSonIntArrayProperty.h"
#include "JSonFloatArrayProperty.h"
#include "JSonNodeArrayProperty.h"

#include "../../CoreMacros.h"

//-------------------------------------------------------------------------------------------------
JSonNodeWriter::JSonNodeWriter()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonNodeWriter::~JSonNodeWriter()
{
}
//-------------------------------------------------------------------------------------------------

/////////
// Accessors
////////

//-------------------------------------------------------------------------------------------------
TUint32 JSonNodeWriter::GetPropertyCount()const
{
	return m_properties.size();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
AJsonProperty* JSonNodeWriter::GetPropertyAt( TUint32 a_index )
{
	return m_properties[ a_index ];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
AJsonProperty* JSonNodeWriter::GetProperty( const std::string& a_name )const
{
	// Serialize all the properties
	TUint32 t_count											=	GetPropertyCount();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		if( m_properties[ i ]->GetName() == a_name )
		{
			return m_properties[ i ];
		}
	}
	return nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TBool JSonNodeWriter::GetBoolProperty( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_BOOL )
		{
			return static_cast<JSonBoolProperty*>(t_property)->GetValue();
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint64 JSonNodeWriter::GetIntProperty( const std::string& a_name , TUint64 a_defaultValue )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_INT )
		{
			return static_cast<JSonIntProperty*>(t_property)->GetValue();
		}
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TFloat64 JSonNodeWriter::GetFloatProperty( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_FLOAT )
		{
			return static_cast<JSonFloatProperty*>(t_property)->GetValue();
		}
	}
	return 0.0f;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const std::string& JSonNodeWriter::GetStringProperty( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_STRING )
		{
			return static_cast<JSonStringProperty*>(t_property)->GetValue();
		}
	}
	return "";
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonNodeWriter* JSonNodeWriter::GetNodeProperty( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_NODE )
		{
			return static_cast<JSonNodeProperty*>(t_property)->GetValue();
		}
	}
	return nullptr;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonIntArrayProperty* JSonNodeWriter::GetIntArray( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_INT_ARRAY )
		{
			return static_cast<JSonIntArrayProperty*>(t_property);
		}
	}
	return nullptr;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonFloatArrayProperty* JSonNodeWriter::GetFloatArray( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_FLOAT_ARRAY )
		{
			return static_cast<JSonFloatArrayProperty*>(t_property);
		}
	}
	return nullptr;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonNodeArrayProperty* JSonNodeWriter::GetNodeArray( const std::string& a_name )const
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_NODE_ARRAY )
		{
			return static_cast<JSonNodeArrayProperty*>(t_property);
		}
	}
	return nullptr;

}
//-------------------------------------------------------------------------------------------------



/////////
// Modificators
////////

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddBoolProperty( const std::string& a_name , TBool a_value )
{
	JSonBoolProperty* t_property							=	new  JSonBoolProperty();

	// Set the property values
	t_property->SetName( a_name );
	t_property->SetValue( a_value );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddIntProperty( const std::string& a_name , TUint64 a_value )
{
	JSonIntProperty* t_property							=	new  JSonIntProperty();

	// Set the property values
	t_property->SetName( a_name );
	t_property->SetValue( a_value );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddFloatProperty( const std::string& a_name , TFloat64 a_value )
{
	JSonFloatProperty* t_property							=	new  JSonFloatProperty();

	// Set the property values
	t_property->SetName( a_name );
	t_property->SetValue( a_value );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddStringProperty( const std::string& a_name , const std::string& a_value )
{
	JSonStringProperty* t_property							=	new  JSonStringProperty();

	// Set the property values
	t_property->SetName( a_name );
	t_property->SetValue( a_value );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddIntArray( const std::string& a_name , TUint32 a_count , const TUint64* a_values )
{
	JSonIntArrayProperty* t_property						=	new JSonIntArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	t_property->SetValues( a_count , a_values );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddIntArray( const std::string& a_name , TUint32 a_count , const TUint32* a_values )
{
	JSonIntArrayProperty* t_property						=	new JSonIntArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	t_property->SetValues( a_count , a_values );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddIntArray( const std::string& a_name , TUint32 a_count , const TUint16* a_values )
{
	JSonIntArrayProperty* t_property						=	new JSonIntArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	t_property->SetValues( a_count , a_values );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddFloatArray( const std::string& a_name , TUint32 a_count , const TFloat64* a_values )
{
	JSonFloatArrayProperty* t_property						=	new JSonFloatArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	t_property->SetValues( a_count , a_values );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::AddFloatArray( const std::string& a_name , TUint32 a_count , const TFloat32* a_values )
{
	JSonFloatArrayProperty* t_property						=	new JSonFloatArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	t_property->SetValues( a_count , a_values );

	// Add the property to the vector
	m_properties.push_back( t_property );
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
JSonNodeWriter* JSonNodeWriter::AddNodeProperty( const std::string& a_name )
{
	JSonNodeProperty* t_property							=	new  JSonNodeProperty();

	// Set the property values
	t_property->SetName( a_name );

	// Add the property to the vector
	m_properties.push_back( t_property );

	return t_property->GetValue();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonNodeArrayProperty* JSonNodeWriter::AddNodeArrayProperty( const std::string& a_name )
{
	JSonNodeArrayProperty* t_property						=	new  JSonNodeArrayProperty();

	// Set the property values
	t_property->SetName( a_name );

	// Add the property to the vector
	m_properties.push_back( t_property );

	return t_property;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::Parse( const rapidjson::Value& a_value )
{
	int t_count	=	a_value.MemberCount();

	for( rapidjson::Value::ConstMemberIterator itr = a_value.MemberBegin(); itr != a_value.MemberEnd(); ++itr )
	{
		ParseProperty( itr->name.GetString() , itr->value );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::ParseProperty( const std::string& a_name , const rapidjson::Value& a_property )
{
	if( a_property.IsBool() )
	{
		AddBoolProperty( a_name  , a_property.GetBool() );
	}
	else if( a_property.IsString() )
	{
		AddStringProperty( a_name  , a_property.GetString() );
	}
	else if( a_property.IsFloat() )
	{
		AddFloatProperty( a_name  , a_property.GetFloat() );
	}
	else if( a_property.IsDouble() )
	{
		AddFloatProperty( a_name  , a_property.GetDouble() );
	}
	else if( a_property.IsInt() )
	{
		AddIntProperty( a_name  , a_property.GetInt() );
	}
	else if( a_property.IsInt64() )
	{
		AddIntProperty( a_name  , a_property.GetInt64() );
	}
	else if( a_property.IsObject() )
	{
		JSonNodeWriter* t_node								=	AddNodeProperty( a_name );

		t_node->Parse( a_property );
	}
	else if( a_property.IsArray() )
	{
		ProcessArrayProperty( a_name , a_property );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::ProcessArrayProperty( const std::string& a_name , const rapidjson::Value& a_property )
{

	const rapidjson::Value& t_firstElement					=	a_property[ 0 ];
	
	if( t_firstElement.IsObject() )
	{
		ProcessNodeArrayProperty( a_name , a_property );
	}
	else if( t_firstElement.IsInt() || t_firstElement.IsInt64() )
	{
		ProcessIntArrayProperty( a_name , a_property );
	}
	else
	{
		ProcessFloatArrayProperty( a_name , a_property );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::ProcessNodeArrayProperty( const std::string& a_name , const rapidjson::Value& a_property )
{
	JSonNodeArrayProperty* t_array							=	AddNodeArrayProperty( a_name );

	TUint32 t_arraySize										=	a_property.Size();
	for(int i = 0 ; i < t_arraySize ; i ++ )
	{
		JSonNodeWriter* t_node								=	t_array->AddNode();

		t_node->Parse( a_property[ i ] );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::ProcessIntArrayProperty( const std::string& a_name , const rapidjson::Value& a_property )
{
	TUint32 t_arraySize										=	a_property.Size();

	TUint64* t_array										=	new TUint64[ t_arraySize ];

	if(a_property[ 0 ].IsInt64() )
	{
		for( int i = 0 ; i < t_arraySize ; i ++ )
		{
			t_array[ i ]									=	a_property[ i ].GetInt64();
		}
	}
	else
	{
		for( int i = 0 ; i < t_arraySize ; i ++ )
		{
			t_array[ i ]									=	a_property[ i ].GetInt();
		}
	}

	AddIntArray( a_name , t_arraySize , t_array );

	SAFE_DELETE_ARRAY( t_array );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::ProcessFloatArrayProperty( const std::string& a_name , const rapidjson::Value& a_property )
{
	TUint32 t_arraySize										=	a_property.Size();

	TFloat64* t_array										=	new TFloat64[ t_arraySize ];

	if(a_property[ 0 ].IsDouble() )
	{
		for( int i = 0 ; i < t_arraySize ; i ++ )
		{
			t_array[ i ]									=	a_property[ i ].GetDouble();
		}
	}
	else
	{
		for( int i = 0 ; i < t_arraySize ; i ++ )
		{
			t_array[ i ]									=	a_property[ i ].GetFloat();
		}
	}

	AddFloatArray( a_name , t_arraySize , t_array );

	SAFE_DELETE_ARRAY( t_array );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonNodeWriter::Serialize( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer )
{
	a_writer.StartObject();

	// Serialize all the properties
	TUint32 t_count											=	GetPropertyCount();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		m_properties[ i ]->Serialize( a_writer );
	}

	a_writer.EndObject();
}
//-------------------------------------------------------------------------------------------------
