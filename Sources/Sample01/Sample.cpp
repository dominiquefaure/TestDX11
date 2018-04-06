// EmptyProject.cpp : Defines the entry point for the application.
//

#include "Sample.h"
#include <fstream>
#include <vector>

#include "WinResources/Resource.h"

//---------------------------------------------------------------------------------------------
Sample::Sample()
{
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



	float t_vertexSize = sizeof( TriangleVertice );


	m_vertexBuffer											=	a_device->CreateVertexBuffer( RHI_BUFFER_USAGE_IMMUTABLE ,
																								t_vertexSize * 3 ,
																								t_vertexSize,
																								t_vertices );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadVertexShader( RhiGraphicDevice* a_device )
{
	std::ifstream t_vertexShaderFile(  "SimpleVS.cso" , std::ios::binary);
	std::vector<char> t_vertexShaderData = { std::istreambuf_iterator<char>(t_vertexShaderFile), std::istreambuf_iterator<char>() };


	HRESULT t_result										=	a_device->GetD3DDevice()->CreateVertexShader(	t_vertexShaderData.data() ,
																												t_vertexShaderData.size() ,
																												nullptr ,
																												&m_vertexShader );
	D3D11_INPUT_ELEMENT_DESC t_vertexLayout[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	
	};
	t_result										=	a_device->GetD3DDevice()->CreateInputLayout( t_vertexLayout,
																											2,
																											t_vertexShaderData.data(),
																											t_vertexShaderData.size(),
																											&m_inputLayout);

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadPixelShader( RhiGraphicDevice* a_device )
{
	std::ifstream t_pixelShaderFile(  "SimplePS.cso" , std::ios::binary);
	std::vector<char> t_pixelShaderData = { std::istreambuf_iterator<char>(t_pixelShaderFile), std::istreambuf_iterator<char>() };

	HRESULT t_result										=	a_device->GetD3DDevice()->CreatePixelShader(	t_pixelShaderData.data() ,
																												t_pixelShaderData.size() ,
																												nullptr ,
																												&m_pixelShader );


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

	t_renderContext->VSSetShader( m_vertexShader , 0, 0 );
	t_renderContext->PSSetShader( m_pixelShader , 0, 0 );
	t_renderContext->IASetInputLayout( m_inputLayout );

	a_context->SetPrimitiveType( RHI_PRIMITIVE_TYPE_TRIANGLE_LIST );
	a_context->SetWireframe( false );
	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );

	a_context->SetVertexStream( 0 , m_vertexBuffer );

	a_context->DrawPrimitive( 3 );
}
//---------------------------------------------------------------------------------------------
