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
	m_mesh													=	NULL;
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
	a_config.m_captionText									=	L"Sample01_Basics";

	a_config.m_iconResID									=	IDI_HELLOTRIANGLE;
	a_config.m_smallIconResID								=	IDI_SMALL;

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::OnInit( )
{
//	m_scale.Set( 1.0f , 1.0f , 1.0f );
	m_scale.Set( 0.5f , 0.5f , 0.5f );
	m_rotate.Set( 0 , 0 , 0 );
	m_translate.Set( 2.0f , 0.0f , 0.0f );
	m_perDrawConstants.m_worldTransform.SetTransScaleRot( m_translate , m_scale , m_rotate );

	RhiGraphicDevice* t_device								=	RhiManager::GetInstance()->GetGraphicDevice();

	LoadModel( t_device );
	InitInstances( t_device );

	CreateConstantBuffer( t_device );


	Matrix44 t_projection;
	Matrix44 t_view;

	t_projection.SetPerpectiveProjection( 45.0f , 1280 / 720.0f , 0.1f , 10000.0f );
	t_view.SetLookAt( Vector3F( 0.0f , 2.0f , -5.0f) , Vector3F( 0.0f , 2.0f , 0.0f) , Vector3F( 0.0f , 1.0f , 0.0f) );

//	m_perFrameConstants.m_viewProjection					=	t_projection * t_view;

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
//	m_perFrameConstants.m_viewProjection					=	t_projection * t_view;
	m_perFrameConstants.m_viewProjection					=	t_view *t_projection;
	m_perFrameConstants.m_viewProjection.Transpose();
#else
	m_perFrameConstants.m_viewProjection					=	t_view *t_projection;
#endif

	m_perFrameConstants.m_lightDirection.Set( 0.3 , 0.0 , 0.7 );
	m_perFrameConstants.m_lightDiffuse.Set( 0.8 , 0.8 , 0.8 );

	m_perDrawConstants.m_matDiffuse.Set( 1.0 , 1.0 , 1.0 );

	m_translate.Set( 0.0f , 0.0f , 0.0f );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnClose()
{
	SAFE_DELETE( m_shader );
	SAFE_DELETE( m_mesh );
	SAFE_DELETE( m_meshInstance1 );
	SAFE_DELETE( m_meshInstance2 );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadModel( RhiGraphicDevice* a_device )
{
	m_material												=	new Material();
	m_material->Load( "DummyMaterial.mat" );

	if( FileSystem::GetInstance()->Exist( "grendizer.mesh" ) )
	{
		m_mesh												=	new StaticMesh();
		m_mesh->LoadFromJSon( "grendizer.mesh" );
	}
	else
	{
		FbxAssetImporter t_importer;
		t_importer.LoadFBX( "grendizer.fbx" );

		m_mesh	=	t_importer.ImportStaticMesh();
		m_mesh->SerializeToJSon( "grendizer.mesh" );
	}
	m_mesh->BuildRenderData( a_device );

	m_model													=	new Model();
	m_model->SetMesh( m_mesh );
	m_model->SetMaterial( m_material );


}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::InitInstances( RhiGraphicDevice* a_device )
{

	m_meshInstance1											=	new StaticModelInstance();
	m_meshInstance1->Init( a_device , m_model );
	m_renderScene.AddElement( m_meshInstance1 );

	m_meshInstance2											=	new StaticModelInstance();
	m_meshInstance2->Init( a_device , m_model );
	m_renderScene.AddElement( m_meshInstance2 );


	m_meshInstance2->SetTransform( m_translate  , m_perDrawConstants.m_worldTransform );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::CreateConstantBuffer( RhiGraphicDevice* a_device )
{
	m_perFrameConstantBuffer.Init( a_device );
	m_perDrawConstantBuffer.Init( a_device );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnUpdate( TFloat32 a_deltaTime )
{
	KeyboardDevice* t_keyboard								=	InputManager::GetInstance()->GetKeyboard();

	float t_updateCoef										=	1.0f * a_deltaTime;

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

//	m_rotate.x += 0.2f * a_deltaTime;
	m_rotate.y += 0.2f * a_deltaTime;
//	m_rotate.z												+=	0.2f * a_deltaTime;

	m_perDrawConstants.m_worldTransform.SetTransScaleRot( m_translate , m_scale , m_rotate );


	m_meshInstance1->SetTransform( m_translate , m_perDrawConstants.m_worldTransform );

	Matrix44 tmp1;
	Matrix44 tmp2;
	Matrix44 tmp3;

	tmp1.SetTranslate( Vector3F( 1.2f , 0.0f , 0.0f ) );
	tmp2.SetRotateX( m_rotate.y * 2 );

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )

	tmp3 = m_perDrawConstants.m_worldTransform  * tmp1 * tmp2;

#else
	tmp3 = tmp2 *  tmp1 * m_perDrawConstants.m_worldTransform;
#endif

	m_meshInstance2->SetTransform( m_translate , tmp3 );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnDraw()
{

	RhiGraphicContext* t_mainContext						=	RhiManager::GetInstance()->GetMainContext();

	// Clear the RenderTarget
	t_mainContext->Clear( 0.25f , 0.5f , 1.0f );

	m_perFrameConstantBuffer.Update( &m_perFrameConstants );
	m_perFrameConstantBuffer.Bind( t_mainContext , RHI_SHADER_TYPE_VERTEX_SHADER ,VS_PARAMETER_SLOT_PER_FRAME );

	t_mainContext->SetWireframe( false );
//	t_mainContext->SetCullingMode( RHI_CULLING_MODE_BACK );
	t_mainContext->SetCullingMode( RHI_CULLING_MODE_FRONT );

	m_renderScene.Draw( t_mainContext );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::DrawDebugUI()
{

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
			m_material->SetParameter( "Color" , Vector3F( t_matDiffuse[ 0 ] , t_matDiffuse[ 1 ] , t_matDiffuse[ 2 ] ) );
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

	ImGui::Checkbox("combine", &Matrix44::s_useCompose );
}
//---------------------------------------------------------------------------------------------
