#include "MaterialTemplate.h"

#ifdef _DEBUG
#include "MaterialTemplate.inl"
#endif

//------------------------------------------------------------------------------------
MaterialTemplate::MaterialTemplate()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
MaterialTemplate::~MaterialTemplate()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::AddScalarParameter( const std::string& a_name , TFloat32 a_defaultValue )
{
	// Create  a new parameter
	MaterialParameterScalarDescriptor* t_param				=	new MaterialParameterScalarDescriptor();

	// Set the correct values
	t_param->Init( a_name , a_defaultValue );

	// add the parameter to the Array
	m_scalarParameters.Add( t_param );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::AddVector3Parameter( const std::string& a_name , const Vector3F& a_defaultValue )
{
	// Create  a new parameter
	MaterialParameterVector3Descriptor* t_param				=	new MaterialParameterVector3Descriptor();

	// Set the correct values
	t_param->Init( a_name , a_defaultValue );

	// add the parameter to the Array
	m_vector3Parameters.Add( t_param );
}
//------------------------------------------------------------------------------------


////////
// Loading Methods
////////

//------------------------------------------------------------------------------------
void MaterialTemplate::Load( const std::string& a_filePath )
{
	// Save the File Path
	m_path													=	a_filePath;

	// Load the Json File
	JSonReader t_reader;
	t_reader.Load( a_filePath );

	LoadFromJSon( t_reader.GetRootNode() );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::LoadFromJSon( const JSonNode* a_rootNode )
{
	LoadShaderProgram( a_rootNode );
	LoadParameters( a_rootNode );
}
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
void MaterialTemplate::LoadShaderProgram( const JSonNode* a_rootNode )
{
	const std::string& t_path								=	a_rootNode->GetStringProperty("Program" );

	m_shaderProgram											=	new ShaderProgram();
	m_shaderProgram->Load( t_path );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::LoadParameters( const JSonNode* a_rootNode )
{
	const JSonNode* t_parameters							=	a_rootNode->GetNodeProperty( "Parameters");

	LoadScalarParameters( t_parameters->GetNodeArray( "Scalar" ) );
	LoadVector3Parameters( t_parameters->GetNodeArray( "Vector3") );

}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::LoadScalarParameters( const JSonNodeArrayProperty* a_parametersNode )
{
	// if there is scalar parameters
	if( a_parametersNode != nullptr )
	{
		TUint32 t_count										=	a_parametersNode->GetCount();
		for( int i = 0 ; i < t_count ; i ++ )
		{
			LoadScalarParameter( a_parametersNode->GetNodeAt( i ) );
		}
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::LoadScalarParameter( const JSonNode* a_parameterNode )
{
	// read the values from json file
	const std::string& t_name								=	a_parameterNode->GetStringProperty( "Name" );
	TFloat32 t_defaultValue									=	a_parameterNode->GetFloatProperty( "DefaultValue" );

	// add the parameter to the scalar list
	AddScalarParameter( t_name , t_defaultValue );
}
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
void MaterialTemplate::LoadVector3Parameters( const JSonNodeArrayProperty* a_parametersNode )
{
	// if there is scalar parameters
	if( a_parametersNode != nullptr )
	{
		TUint32 t_count										=	a_parametersNode->GetCount();
		for( int i = 0 ; i < t_count ; i ++ )
		{
			LoadVector3Parameter( a_parametersNode->GetNodeAt( i ) );
		}
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialTemplate::LoadVector3Parameter( const JSonNode* a_parameterNode )
{
	// read the values from json file
	const std::string& t_name								=	a_parameterNode->GetStringProperty( "Name" );

	Vector3F t_defaultValues;

	//get the array storing the vector default values
	const JSonFloatArrayProperty* t_values					=	a_parameterNode->GetFloatArray( "DefaultValue" );

	// if Default values are present in the json node
	if( t_values != nullptr )
	{
		t_defaultValues.x									=	t_values->GetValue32At( 0 );
		t_defaultValues.y									=	t_values->GetValue32At( 1 );
		t_defaultValues.z									=	t_values->GetValue32At( 2 );
	}

	// add the parameter to the vector3 list
	AddVector3Parameter( t_name , t_defaultValues );
}
//------------------------------------------------------------------------------------
