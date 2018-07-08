#include "JSonIntArrayProperty.h"
#include "../../../Core/CoreMacros.h"


//-------------------------------------------------------------------------------------------------
JSonIntArrayProperty::JSonIntArrayProperty()
{
	m_type													=	JSON_PROPERTY_TYPE_INT_ARRAY;

	m_values												=	nullptr;
	m_count													=	0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonIntArrayProperty::~JSonIntArrayProperty()
{
	SAFE_DELETE_ARRAY( m_values );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint32 JSonIntArrayProperty::GetCount()const
{
	return m_count;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::GetValues64( TUint64* a_array )const
{
	memcpy( a_array , m_values , sizeof( TUint64) * m_count );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::GetValues32( TUint32* a_array )const
{
	for( int i = 0 ; i < m_count ; i ++ )
	{
		a_array[ i ]										=	static_cast<TUint32>( m_values[ i ] );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::GetValues16( TUint16* a_array )const
{
	for( int i = 0 ; i < m_count ; i ++ )
	{
		a_array[ i ]										=	static_cast<TUint16>( m_values[ i ] );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::SetValues( TUint32 a_count , const TUint64* a_values )
{
	m_count													=	a_count;

	m_values												=	new TUint64[ m_count ];

	for( int i = 0 ; i < m_count ; i ++ )
	{
		m_values[ i ]										=	a_values[ i ];
	}

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::SetValues( TUint32 a_count , const TUint32* a_values )
{
	m_count													=	a_count;

	m_values												=	new TUint64[ m_count ];

	for( int i = 0 ; i < m_count ; i ++ )
	{
		m_values[ i ]										=	a_values[ i ];
	}

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::SetValues( TUint32 a_count , const TUint16* a_values )
{
	m_count													=	a_count;

	m_values												=	new TUint64[ m_count ];

	for( int i = 0 ; i < m_count ; i ++ )
	{
		m_values[ i ]										=	a_values[ i ];
	}

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonIntArrayProperty::SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer )
{
	a_writer.StartArray();

	for( int i = 0 ; i < m_count ; i ++ )
	{
		a_writer.Int64( m_values[ i ] );
	}


	a_writer.EndArray();
}
//-------------------------------------------------------------------------------------------------
