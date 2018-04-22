#include "JSonNode.h"
#include "JSonProperty.h"


//-------------------------------------------------------------------------------------
JSonNode::JSonNode( )
{
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
JSonNode::JSonNode( Value* a_value )
{
	m_jsonNode												=	a_value;

}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void JSonNode::SetNode( Value* a_value )
{
	m_jsonNode												=	a_value;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
bool JSonNode::Contains( const std::string & a_propertyName )
{
	return 	m_jsonNode->HasMember( a_propertyName.c_str() );
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
JSonPropertyType JSonNode::GetPropertyType( const std::string & a_propertyName )
{

	if( !Contains( a_propertyName ) )
	{
		return JSON_PROPERTY_TYPE_NONE;
	}

	JSonProperty t_property = GetProperty( a_propertyName );
	return t_property.GetType();
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
TBool JSonNode::GetBoolProperty( const std::string & a_propertyName , TBool a_defaultValue )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	if( t_property.GetType() == JSON_PROPERTY_TYPE_BOOL )
	{
		return t_property.GetBool();
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
TUint32 JSonNode::GetInt32Property( const std::string & a_propertyName , TUint32 a_defaultValue )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	if( t_property.GetType() == JSON_PROPERTY_TYPE_INT32 )
	{
		return t_property.GetInt32();
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
TUint64 JSonNode::GetInt64Property( const std::string & a_propertyName , TUint64 a_defaultValue )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );
	if( t_property.GetType() == JSON_PROPERTY_TYPE_INT64 )
	{
		return t_property.GetInt64();
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
TFloat32 JSonNode::GetFloatProperty( const std::string & a_propertyName , TFloat32 a_defaultValue )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	if( t_property.GetType() == JSON_PROPERTY_TYPE_FLOAT )
	{
		return t_property.GetFloat();
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
TFloat64 JSonNode::GetDoubleProperty( const std::string & a_propertyName , TFloat64 a_defaultValue )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	if( t_property.GetType() == JSON_PROPERTY_TYPE_DOUBLE )
	{
		return t_property.GetDouble();
	}

	return a_defaultValue;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
const char* JSonNode::GetStringProperty( const std::string & a_propertyName )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	return t_property.GetString();

}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
JSonNode JSonNode::GetNodeProperty( const std::string & a_propertyName )
{
	JSonProperty t_property									=	GetProperty( a_propertyName );

	if( t_property.IsJSonObject() )
	{
		return t_property.GetJSonObject();
	}

	return JSonNode();
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
bool JSonNode::HaveSubNodes()
{
	JSonProperty t_property( m_jsonNode );

	if( t_property.IsArray() )
	{
		if( t_property.GetArrayElementType() == JSON_PROPERTY_TYPE_NODE )
		{
			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
int JSonNode::GetSubNodeCount()
{
	if( HaveSubNodes() )
	{
		return m_jsonNode->Size();
	}

	return 0;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
JSonNode JSonNode::GetSubNodeAt( int a_index )
{
	Value& t_subNode										=	(*m_jsonNode)[ a_index ];

	return JSonNode( &t_subNode );

}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
JSonProperty JSonNode::GetProperty( const std::string & a_propertyName )
{
	if( m_jsonNode->HasMember( a_propertyName.c_str() ) )
	{
		return JSonProperty( &( (*m_jsonNode)[ a_propertyName.c_str() ] ) );
	}
	return JSonProperty( );
}
//-------------------------------------------------------------------------------------


