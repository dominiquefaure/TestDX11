#include "StaticModelInstance.h"


//------------------------------------------------------------------------------------
StaticModelInstance::StaticModelInstance()
{
	m_model													=	nullptr;

	m_vertexConstants.m_worldTransform.SetIdentity();
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
StaticModelInstance::~StaticModelInstance()
{
	m_model													=	nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticModelInstance::Init( RhiGraphicDevice* a_device , const ReferenceCountedPtr<Model>& a_model )
{
	m_vertexConstantBuffer.Init( a_device );

	m_model													=	a_model;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticModelInstance::Draw( RhiGraphicContext* a_context )
{
	if( m_model != nullptr )
	{
		m_vertexConstants.m_worldTransform	=	m_worldTransform;
		m_vertexConstantBuffer.Update( a_context , &m_vertexConstants );
		m_vertexConstantBuffer.Bind( a_context , RHI_SHADER_TYPE_VERTEX_SHADER ,VS_PARAMETER_SLOT_PER_DRAW );

		m_model->Draw( a_context );
	}
}
//------------------------------------------------------------------------------------
