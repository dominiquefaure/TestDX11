// EmptyProject.cpp : Defines the entry point for the application.
//

#include "Sample.h"
#include <fstream>
#include <vector>

#include "WinResources/Resource.h"

#include "../Common/Graphics/Importers/Fbx/FbxAssetImporter.h"


//---------------------------------------------------------------------------------------------
Sample::Sample()
{
	m_spriteMesh											=	NULL;
	m_spriteMaterial										=	NULL;
	m_spriteModel											=	NULL;
	m_spriteInstance										=	NULL;
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
//	m_scale.Set( 1.0f , 1.0f , 1.0f );
	m_scale.Set( 10.0f , 10.0f , 1.0f );
	m_rotate.Set( 0 , 0 , 0 );
	m_translate.Set( 2.0f , 0.0f , 0.0f );
	RhiGraphicDevice* t_device								=	RhiManager::GetInstance()->GetGraphicDevice();

	LoadSprite( t_device );

	CreateConstantBuffer( t_device );


	Matrix44 t_projection;
	Matrix44 t_view;

	t_projection.SetPerpectiveProjection( 0.45f , 1280 / 720.0f , 0.1f , 10000.0f );

//	t_projection.SetOrthoProjection( -6.4 , 6.4 , 3.6 , -3.6 , 1.0 , 100.0f );
	t_view.SetLookAt( Vector3F( 0.0f , 0.0f , -15.0f) , Vector3F( 0.0f , 0.0f , 10.0f) , Vector3F( 0.0f , 1.0f , 0.0f) );


#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	m_perFrameConstants.m_viewProjection					=	t_projection * t_view;
#else
	m_perFrameConstants.m_viewProjection					=	t_view *t_projection;
#endif


	m_perFrameConstants.m_lightDirection.Set( 0.3 , 0.0 , 0.7 );
	m_perFrameConstants.m_lightDiffuse.Set( 0.8 , 0.8 , 0.8 );

	m_perDrawConstants.m_matDiffuse.Set( 1.0 , 1.0 , 1.0 );

	m_translate.Set( 0.0f , 0.0f , 0.0f );

	m_testTexture	=	DDSTextureLoader::CreateTexture( RhiManager::GetInstance()->GetGraphicDevice() ,"armor.dds" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::OnClose()
{
	SAFE_DELETE( m_spriteInstance );
//	SAFE_DELETE( m_spriteModel );
//	SAFE_DELETE( m_spriteMaterial );
//	SAFE_DELETE( m_spriteMesh );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Sample::LoadSprite( RhiGraphicDevice* a_device )
{
	m_spriteMaterial										=	new Material();
	m_spriteMaterial->Load( "SpriteMat.mat" );

	m_spriteMesh											=	new StaticMesh();
	m_spriteMesh->LoadFromJSon( "Sprite.mesh" );
	m_spriteMesh->BuildRenderData( a_device );

	m_spriteModel											=	new Model();
	m_spriteModel->SetMesh( m_spriteMesh );
	m_spriteModel->SetMaterial( m_spriteMaterial );

	m_spriteInstance										=	new StaticModelInstance();
	m_spriteInstance->Init( a_device , m_spriteModel );
	m_renderScene.AddElement( m_spriteInstance );
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

//	m_rotate.y												+=	0.2f * a_deltaTime;

	m_perDrawConstants.m_worldTransform.SetTransScaleRot( m_translate , m_scale , m_rotate );


	m_spriteInstance->SetTransform( m_translate , m_perDrawConstants.m_worldTransform );
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
//	a_context->SetCullingMode( RHI_CULLING_MODE_BACK );
	t_mainContext->SetCullingMode( RHI_CULLING_MODE_FRONT );

	t_mainContext->SetTexture( 0 , m_testTexture->GetRhiTexture() );

	m_renderScene.Draw( t_mainContext );

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void Sample::DrawDebugUI()
{
}
//---------------------------------------------------------------------------------------------

