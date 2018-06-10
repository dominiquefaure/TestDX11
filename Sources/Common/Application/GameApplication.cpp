#include "GameApplication.h"

#include "../Inputs/Includes.h"

#include "../Includes.h"


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
	RECT rc;
	GetClientRect(a_handle, &rc);

	RhiManager::CreateInstance();
	RhiManager::GetInstance()->Init( a_handle ,  rc.right - rc.left , rc.bottom - rc.top  );

	InputManager::CreateInstance();

	// perform custom inits
	OnInit( );

	ImGuiWrapper::CreateInstance();
	ImGuiWrapper::GetInstance()->InitImGUI( a_handle , rc.right - rc.left , rc.bottom - rc.top );
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
	InputManager::GetInstance()->Update();
	ImGuiWrapper::GetInstance()->BeginFrame();

	// Custom Updates	
	OnUpdate();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::PerformDraw()
{
	RhiManager::GetInstance()->BeginFrame();

	OnDraw();

	ImGuiWrapper::GetInstance()->EndFrame();


	RhiManager::GetInstance()->EndFrame();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void GameApplication::ProcessWindowsMessages( HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam )
{
	ImGuiWrapper::GetInstance()->ProcessWindowsMessages( a_hwnd , a_msg , a_wParam , a_lParam );
}
//---------------------------------------------------------------------------------------------
