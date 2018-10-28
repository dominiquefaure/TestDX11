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
void StaticModelInstance::AddToRenderList( RhiGraphicContext* a_context , GeometryRenderList* a_renderList )
{
	if( m_model != nullptr )
	{
		m_vertexConstants.m_worldTransform	=	m_worldTransform;
		m_vertexConstantBuffer.Update( &m_vertexConstants );

		m_vertexConstantBuffer.Flush( a_context );

		m_model->SetupDraw( a_renderList , &m_vertexConstantBuffer );
	}
}
//------------------------------------------------------------------------------------
