#include "GameApplication.h"

#include "../Inputs/Includes.h"

#include "../Includes.h"
#include "../Core/Platforms/PlatformWrapper.h"
#include "../Core/Math/includes.h"

#include "../Core/Utils//Includes.h"

#ifdef _DEBUG
#include "GameApplication.inl"
#endif


//---------------------------------------------------------------------------------------------
GameApplication::GameApplication()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
GameApplication::~GameApplication()
{
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::SetWindowConfig( WinAppConfig& a_config )
{
	// Set Default values
	a_config.m_className									=	L"VTSRenderSampleClass";
	a_config.m_captionText									=	L"DefaultApplication";
	a_config.m_dwStyle										=	WS_OVERLAPPEDWINDOW;
	a_config.m_dwXPos										=	CW_USEDEFAULT;
	a_config.m_dwYPos										=	0;
	a_config.m_dwWidth										=	CW_USEDEFAULT;
	a_config.m_dwHeight										=	0;


	a_config.m_smallIconResID								=	0;
	a_config.m_iconResID									=	0;
	a_config.m_menuID										=	0;
	
	// Allow custom configuration
	OnSetWindowConfig( a_config );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::Init( HWND a_handle )
{
	PlatformTime::Initialize();

	RECT rc;
	GetClientRect(a_handle, &rc);

	AssetManager::CreateInstance();
	RhiManager::CreateInstance();
	RhiManager::GetInstance()->Init( a_handle ,  rc.right - rc.left , rc.bottom - rc.top  );

	InputManager::CreateInstance();

	ImGuiWrapper::CreateInstance();
	ImGuiWrapper::GetInstance()->InitImGUI( a_handle , rc.right - rc.left , rc.bottom - rc.top );

	// by default 60Fps
	m_maxFPS												=	60;

	// perform custom inits
	OnInit( );

	m_timer.Start();
	m_lastFrameDuration										=	0;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::Close()
{
	// Close Application Custom data
	OnClose();

	// Free the Managers
	InputManager::DestroyInstance();
	RhiManager::DestroyInstance();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::OnFrame()
{
	PerformUpdates();
	PerformDraw();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::PerformUpdates()
{
	ProcessFPS();

	InputManager::GetInstance()->Update();
	ImGuiWrapper::GetInstance()->BeginFrame();

	// Custom Updates	
	OnUpdate( m_lastFrameDuration );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::PerformDraw()
{
	RhiManager::GetInstance()->BeginFrame();

	OnDraw();

	DrawDebugUI();

	ImGuiWrapper::GetInstance()->EndFrame();


	RhiManager::GetInstance()->EndFrame();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::ProcessFPS()
{
	TFloat32 t_pulseTime									=	0.0f;
	if( m_maxFPS > 0 )
	{
		t_pulseTime											=	( 1.0f / m_maxFPS );
	}
	m_timer.Pulse(t_pulseTime );

	m_lastFrameDuration										=	m_timer.GetEleapsedSeconds();
}
//---------------------------------------------------------------------------------------------
