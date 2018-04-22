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
	TriangleVertice t_vertices[ 3 ];

	// Vertex 0 Position
	t_vertices[ 0 ].x	=	0.0f;
	t_vertices[ 0 ].y	=	0.5f;
	t_vertices[ 0 ].z	=	0.5f;

	// Vertex 0 Color
	t_vertices[ 0 ].r	=	1.0f;
	t_vertices[ 0 ].g	=	0.0f;
	t_vertices[ 0 ].b	=	0.0f;

	// Vertex 1 Position
	t_vertices[ 1 ].x	=	-0.5f;
	t_vertices[ 1 ].y	=	-0.5f;
	t_vertices[ 1 ].z	=	0.5f;

	// Vertex 1 Color
	t_vertices[ 1 ].r	=	0.0f;
	t_vertices[ 1 ].g	=	1.0f;
	t_vertices[ 1 ].b	=	0.0f;

	// Vertex 2 Position
	t_vertices[ 2 ].x	=	0.5f;
	t_vertices[ 2 ].y	=	-0.5f;
	t_vertices[ 2 ].z	=	0.5f;

	// Vertex 2 Color
	t_vertices[ 2 ].r	=	0.0f;
	t_vertices[ 2 ].g	=	0.0f;
	t_vertices[ 2 ].b	=	1.0f;



	int t_vertexSize = sizeof( TriangleVertice );


	m_geometry												=	new StaticGeometry();
	m_geometry->Init( a_device , RHI_PRIMITIVE_TYPE_TRIANGLE_LIST , t_vertices , t_vertexSize , 3 );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadVertexShader( RhiGraphicDevice* a_device )
{
	ShaderByteCode t_byteCode;
	t_byteCode.CompileFromFile( VERTEX_SHADER , "SimpleVS.hlsl" );

	m_vertexShader											=	a_device->CreateVertexShader( t_byteCode );

	D3D11_INPUT_ELEMENT_DESC t_vertexLayout[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	
	};
	HRESULT t_result										=	a_device->GetD3DDevice()->CreateInputLayout( t_vertexLayout,
																											2,
																											t_byteCode.GetByteCode(),
																											t_byteCode.GetSize(),
																											&m_inputLayout);

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
	ID3D11DeviceContext* t_renderContext					=	a_context->GetContext();

	a_context->SetVertexShader( m_vertexShader  );
	a_context->SetPixelShader( m_pixelShader  );
	t_renderContext->IASetInputLayout( m_inputLayout );

	a_context->SetWireframe( false );
	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );

	m_geometry->Draw( a_context );
}
//---------------------------------------------------------------------------------------------
