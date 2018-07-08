#include "JSonNodeArrayProperty.h"
#include "../../../Core/CoreMacros.h"

#include "JSonNodeWriter.h"

//-------------------------------------------------------------------------------------------------
JSonNodeArrayProperty::JSonNodeArrayProperty()
{
	m_type													=	JSON_PROPERTY_TYPE_NODE_ARRAY;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonNodeArrayProperty::~JSonNodeArrayProperty()
{
	for( int i = 0 ; i < m_subNodes.size() ; i ++ )
	{
		SAFE_DELETE( m_subNodes[ i ] );
	}

	m_subNodes.clear();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint32 JSonNodeArrayProperty::GetCount()const
{
	return m_subNodes.size();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonNodeWriter* JSonNodeArrayProperty::GetNodeAt( TUint32 a_index )const
{
	assert( a_index < m_subNodes.size() );

	return m_subNodes[ a_index ];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonNodeWriter* JSonNodeArrayProperty::AddNode()
{
	JSonNodeWriter* t_node									=	new JSonNodeWriter();

	m_subNodes.push_back( t_node );

	return t_node;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void JSonNodeArrayProperty::SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer )
{
	a_writer.StartArray();

	for( TUint32 i = 0 ; i < m_subNodes.size() ; i ++ )
	{
		m_subNodes[ i ]->Serialize( a_writer );
	}


	a_writer.EndArray();
}
//-------------------------------------------------------------------------------------------------
