// EmptyProject.cpp : Defines the entry point for the application.
//

#include "Sample.h"
#include <fstream>
#include <vector>

#include "WinResources/Resource.h"

//---------------------------------------------------------------------------------------------
Sample::Sample()
{
	m_geometry												=	NULL;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
Sample::~Sample()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnSetWindowConfig( WinAppConfig& a_config )
{
	a_config.m_captionText									=	L"Sample01_HelloWorld";

	a_config.m_iconResID									=	IDI_HELLOTRIANGLE;
	a_config.m_smallIconResID								=	IDI_SMALL;

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::OnInit( )
{

	RhiGraphicDevice* t_device								=	RhiManager::GetInstance()->GetGraphicDevice();

	LoadGoemetry( t_device );
	LoadShaders( );

	CreateConstantBuffer( t_device );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnClose()
{
	SAFE_DELETE( m_shader );

	SAFE_DELETE( m_geometry );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadGoemetry( RhiGraphicDevice* a_device )
{

	GeometryDataset* t_data									=	new GeometryDataset();
	t_data->LoadFromJSon( "SolidCube.geo" );

	m_geometry												=	new StaticGeometry();
	m_geometry->Build( a_device , t_data );

	SAFE_DELETE( t_data );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadShaders( )
{
	m_shader												=	new ShaderProgram();
	m_shader->Load( "ShaderDef.json" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::CreateConstantBuffer( RhiGraphicDevice* a_device )
{
	m_constantBuffer										=	a_device->CreateConstantBuffer( sizeof( m_transform) );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnUpdate()
{
	KeyboardDevice* t_keyboard								=	InputManager::GetInstance()->GetKeyboard();

	if( t_keyboard->IsPressed( KEY_LEFT ) )
	{
		m_transform.x										-=	0.001f;
	}
	else
	{
		if( t_keyboard->IsPressed( KEY_RIGHT ) )
		{
			m_transform.x									+=	0.001f;
		}
	}

	if( t_keyboard->IsPressed( KEY_UP ) )
	{
		m_transform.y										+=	0.001f;
	}
	else
	{
		if( t_keyboard->IsPressed( KEY_DOWN ) )
		{
			m_transform.y									-=	0.001f;
		}
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnDraw()
{

	RhiGraphicContext* t_mainContext						=	RhiManager::GetInstance()->GetMainContext();

	// Clear the RenderTarget
	t_mainContext->Clear( 0.25f , 0.5f , 1.0f );

	DrawTriangle( t_mainContext );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::DrawTriangle( RhiGraphicContext* a_context )
{
	m_constantBuffer->Update( (TUint8*)&m_transform , 0 , sizeof( m_transform) );
	m_constantBuffer->Commit( a_context , RHI_SHADER_TYPE_VERTEX_SHADER , 0 );

	a_context->SetWireframe( false );
	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );

	m_geometry->Apply( a_context );
	m_shader->Apply( a_context , 0 );

	m_geometry->ProcessDraw( a_context );
}
//---------------------------------------------------------------------------------------------
