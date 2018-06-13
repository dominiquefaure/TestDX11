// EmptyProject.cpp : Defines the entry point for the application.
//

#include "Sample.h"
#include <fstream>
#include <vector>

#include "WinResources/Resource.h"

#include "../Common/Renderer/Importers/Fbx/FbxAssetImporter.h"


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


	Matrix44 t_projection;
	Matrix44 t_view;

	t_projection.SetPerpectiveProjection( 45.0f , 1280 / 720.0f , 0.1f , 10000.0f );
	t_view.SetLookAt( Vector3F( 0.0f , 2.0f , -5.0f) , Vector3F( 0.0f , 2.0f , 0.0f) , Vector3F( 0.0f , 1.0f , 0.0f) );

	m_perFrameConstants.m_viewProjection					=	t_projection * t_view;


	m_scale.Set( 1.0f , 1.0f , 1.0f );
	m_rotate.Set( 0 , 0 , 0 );

	m_perFrameConstants.m_lightDirection.Set( 0.3 , 0.0 , 0.7 );
	m_perFrameConstants.m_lightDiffuse.Set( 0.8 , 0.8 , 0.8 );

	m_perDrawConstants.m_matDiffuse.Set( 1.0 , 1.0 , 1.0 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnClose()
{
	SAFE_DELETE( m_shader );
	SAFE_DELETE( m_geometry );

	SAFE_DELETE( m_perFrameConstantBuffer );
	SAFE_DELETE( m_perDrawConstantBuffer );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadGoemetry( RhiGraphicDevice* a_device )
{
	FbxAssetImporter t_importer;
	t_importer.LoadFBX( "grendizer.fbx" );

	GeometryDataset* t_data									=	t_importer.ImportMesh();

//	GeometryDataset* t_data									=	new GeometryDataset();
//	t_data->LoadFromJSon( "SolidCube.geo" );

	m_geometry												=	new StaticGeometry();
	m_geometry->Build( a_device , t_data );

	SAFE_DELETE( t_data );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadShaders( )
{
	m_shader												=	new ShaderProgram();
//	m_shader->Load( "ShaderDef.json" );
	m_shader->Load( "PerVertexLighting.json" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::CreateConstantBuffer( RhiGraphicDevice* a_device )
{
	m_perFrameConstantBuffer								=	a_device->CreateConstantBuffer( sizeof( PerFrameConstants) );
	m_perDrawConstantBuffer									=	a_device->CreateConstantBuffer( sizeof( PerDrawConstants) );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnUpdate()
{
	KeyboardDevice* t_keyboard								=	InputManager::GetInstance()->GetKeyboard();

	float t_updateCoef										=	0.001f;

	if( t_keyboard->IsPressed( KEY_LEFT ) )
	{
		m_translate.x										-=	t_updateCoef;
	}
	else
	{
		if( t_keyboard->IsPressed( KEY_RIGHT ) )
		{
			m_translate.x									+=	t_updateCoef;
		}
	}

	if( t_keyboard->IsPressed( KEY_UP ) )
	{
		m_translate.y										+=	t_updateCoef;
	}
	else
	{
		if( t_keyboard->IsPressed( KEY_DOWN ) )
		{
			m_translate.y									-=	t_updateCoef;
		}
	}

	m_rotate.y+=0.0001f;

	m_perDrawConstants.m_worldTransform.SetTransScaleRot( m_translate , m_scale , m_rotate );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnDraw()
{

	RhiGraphicContext* t_mainContext						=	RhiManager::GetInstance()->GetMainContext();

	// Clear the RenderTarget
	t_mainContext->Clear( 0.25f , 0.5f , 1.0f );

	DrawTriangle( t_mainContext );


//	ImGui::ShowDemoWindow();

	if( ImGui::CollapsingHeader( "Material") )
	{
		float t_matDiffuse[3];

		t_matDiffuse[ 0 ]									=	m_perDrawConstants.m_matDiffuse.x;
		t_matDiffuse[ 1 ]									=	m_perDrawConstants.m_matDiffuse.y;
		t_matDiffuse[ 2 ]									=	m_perDrawConstants.m_matDiffuse.z;
		if( ImGui::ColorEdit3( "Mat Diffuse" , t_matDiffuse ) )
		{
			m_perDrawConstants.m_matDiffuse.Set( t_matDiffuse[ 0 ] , t_matDiffuse[ 1 ] , t_matDiffuse[ 2 ] );
		}
	}

	if( ImGui::CollapsingHeader( "Light") )
	{
		float t_dir[3];

		t_dir[ 0 ]									=	m_perFrameConstants.m_lightDirection.x;
		t_dir[ 1 ]									=	m_perFrameConstants.m_lightDirection.y;
		t_dir[ 2 ]									=	m_perFrameConstants.m_lightDirection.z;

		if( ImGui::InputFloat3( "Light Dir", t_dir) )
		{
			m_perFrameConstants.m_lightDirection.Set( t_dir[ 0 ] , t_dir[ 1 ] , t_dir[ 2 ] );
		}


		float t_values[3];

		t_values[ 0 ]									=	m_perFrameConstants.m_lightDiffuse.x;
		t_values[ 1 ]									=	m_perFrameConstants.m_lightDiffuse.y;
		t_values[ 2 ]									=	m_perFrameConstants.m_lightDiffuse.z;
		if( ImGui::ColorEdit3( "Diffuse" , t_values ) )
		{
			m_perFrameConstants.m_lightDiffuse.Set( t_values[ 0 ] , t_values[ 1 ] , t_values[ 2 ] );
		}
	}
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::DrawTriangle( RhiGraphicContext* a_context )
{
	m_perFrameConstantBuffer->Update( (TUint8*)&m_perFrameConstants , 0 , sizeof( m_perFrameConstants) );
	m_perDrawConstantBuffer->Update( (TUint8*)&m_perDrawConstants , 0 , sizeof( m_perDrawConstants) );

	m_perFrameConstantBuffer->Commit( a_context , RHI_SHADER_TYPE_VERTEX_SHADER , 0 );
	m_perDrawConstantBuffer->Commit( a_context , RHI_SHADER_TYPE_VERTEX_SHADER , 1 );

	a_context->SetWireframe( false );
//	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );
	a_context->SetCullingMode( RHI_CULLING_MODE_FRONT );

	m_geometry->Apply( a_context );
	m_shader->Apply( a_context , 0 );

	m_geometry->ProcessDraw( a_context );
}
//---------------------------------------------------------------------------------------------
