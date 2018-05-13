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

	CreateVertexBuffer( t_device );
	LoadVertexShader( t_device );
	LoadPixelShader( t_device );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnClose()
{
	SAFE_DELETE( m_geometry );

	SAFE_DELETE( m_vertexShader );
	SAFE_DELETE( m_pixelShader );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::CreateVertexBuffer( RhiGraphicDevice* a_device )
{
	m_geometry												=	new StaticGeometry();
	m_geometry->LoadFromJSon( a_device , "SolidCube.geo");
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadVertexShader( RhiGraphicDevice* a_device )
{
	ShaderByteCode t_byteCode;
	t_byteCode.CompileFromFile( VERTEX_SHADER , "SimpleVS.hlsl" );
	m_vertexShader											=	a_device->CreateVertexShader( t_byteCode );


}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadPixelShader( RhiGraphicDevice* a_device )
{
	ShaderByteCode t_byteCode;
	t_byteCode.CompileFromFile( PIXEL_SHADER , "SimplePS.hlsl" );

	m_pixelShader											=	a_device->CreatePixelShader( t_byteCode );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::OnUpdate()
{
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
	a_context->SetVertexShader( m_vertexShader  );
	a_context->SetPixelShader( m_pixelShader  );

	a_context->SetWireframe( false );
	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );

	m_geometry->Draw( a_context );
}
//---------------------------------------------------------------------------------------------
