#include "JSonNodeWriter.h"

#include "JSonBoolProperty.h"
#include "JSonIntProperty.h"
#include "JSonFloatProperty.h"
#include "JSonStringProperty.h"
#include "JSonNodeProperty.h"

#include "JSonIntArrayProperty.h"
#include "JSonFloatArrayProperty.h"
#include "JSonNodeArrayProperty.h"


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
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TBool JSonNodeWriter::GetBoolProperty( const std::string& a_name )
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
TUint64 JSonNodeWriter::GetIntProperty( const std::string& a_name )
{
	AJsonProperty* t_property								=	GetProperty( a_name );

	if( t_property != nullptr )
	{
		if( t_property->GetType() == JSON_PROPERTY_TYPE_INT )
		{
			return static_cast<JSonIntProperty*>(t_property)->GetValue();
		}
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TFloat64 JSonNodeWriter::GetFloatProperty( const std::string& a_name )
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
const std::string& JSonNodeWriter::GetStringProperty( const std::string& a_name )
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
