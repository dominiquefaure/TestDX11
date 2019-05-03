#include "JSonFloatArrayProperty.h"
#include "../../../Core/CoreMacros.h"


//-------------------------------------------------------------------------------------------------
JSonFloatArrayProperty::JSonFloatArrayProperty()
{
	m_type													=	JSON_PROPERTY_TYPE_FLOAT_ARRAY;

	m_values												=	nullptr;
	m_count													=	0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonFloatArrayProperty::~JSonFloatArrayProperty()
{
	SAFE_DELETE_ARRAY( m_values );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint32 JSonFloatArrayProperty::GetCount()const
{
	return m_count;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonFloatArrayProperty::GetValues64( TFloat64* a_array )const
{
	memcpy( a_array , m_values , sizeof( TFloat64) * m_count );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonFloatArrayProperty::GetValues32( TFloat32* a_array )const
{
	for( int i = 0 ; i < m_count ; i ++ )
	{
		a_array[ i ]										=	static_cast<TFloat32>( m_values[ i ] );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TFloat32 JSonFloatArrayProperty::GetValue32At( TUint32 a_index )const
{
	if( a_index < m_count )
	{
		return static_cast<TFloat32>( m_values[ a_index ] );
	}

	return 0.0f;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TFloat64 JSonFloatArrayProperty::GetValue64At( TUint32 a_index )const
{
	if( a_index < m_count )
	{
		return static_cast<TFloat64>( m_values[ a_index ] );
	}

	return 0.0f;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonFloatArrayProperty::SetValues( TUint32 a_count , const TFloat64* a_values )
{
	m_count													=	a_count;

	m_values												=	new TFloat64[ m_count ];

	for( int i = 0 ; i < m_count ; i ++ )
	{
		m_values[ i ]										=	a_values[ i ];
	}

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonFloatArrayProperty::SetValues( TUint32 a_count , const TFloat32* a_values )
{
	m_count													=	a_count;

	m_values												=	new TFloat64[ m_count ];

	for( int i = 0 ; i < m_count ; i ++ )
	{
		m_values[ i ]										=	a_values[ i ];
	}

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonFloatArrayProperty::SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer )
{
	a_writer.StartArray();

	for( int i = 0 ; i < m_count ; i ++ )
	{
		a_writer.Double( m_values[ i ] );
	}

	a_writer.EndArray();
}
//-------------------------------------------------------------------------------------------------
