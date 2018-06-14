#include "WinMainLauncher.h"


#include "../DebugUI/ImGuiWrapper.h"


#define MAX_LOADSTRING 100

// Callback that will be Called to Handle Windows Messages
LRESULT PASCAL AppWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Static poihter to the launcher , required to handle so windows events
WinMainLauncher* s_launcher;


//---------------------------------------------------------------------------------------------
WinMainLauncher::WinMainLauncher()
{
	m_quitRequested											=	false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
WinMainLauncher::~WinMainLauncher()
{
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
BOOL WinMainLauncher::RegisterWndClass( )
{
	// Define the windows Properties
	m_stWcex.cbSize											=	sizeof(WNDCLASSEX);
	m_stWcex.style											=	CS_HREDRAW | CS_VREDRAW;
    m_stWcex.lpfnWndProc									=	AppWindowProc;
    m_stWcex.cbClsExtra										=	0;
    m_stWcex.cbWndExtra										=	0;
    m_stWcex.hInstance										=	m_hInst;
    m_stWcex.hCursor										=	LoadCursor( NULL, IDC_ARROW );
    m_stWcex.hbrBackground									=	( HBRUSH ) ( COLOR_WINDOW + 1 );
    m_stWcex.lpszClassName									=	m_config.m_className.c_str();

	m_stWcex.hIcon											=	NULL;
	m_stWcex.hIconSm										=	NULL;
	m_stWcex.lpszMenuName									=	NULL;


	if( m_config.m_iconResID != 0 )
	{
	    m_stWcex.hIcon										=	LoadIcon( m_hInst, MAKEINTRESOURCE( m_config.m_iconResID ));
	}

	if( m_config.m_smallIconResID != 0 )
	{
	    m_stWcex.hIconSm									=	LoadIcon( m_hInst, MAKEINTRESOURCE( m_config.m_smallIconResID ));
	}

	if( m_config.m_menuID != 0 )
	{
		m_stWcex.lpszMenuName								=	MAKEINTRESOURCEW( m_config.m_menuID );
	}
	

	if ( !RegisterClassEx( &m_stWcex ) )
	{
		return FALSE;
	}

	return TRUE;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
BOOL WinMainLauncher::CreateWindowDlg( int a_nCmdShow )
{
	m_hWnd													=	CreateWindowW(	m_config.m_className.c_str(),
																				m_config.m_captionText.c_str(),
																				m_config.m_dwStyle,
																				m_config.m_dwXPos,
																				m_config.m_dwYPos,
																				m_config.m_dwWidth,
																				m_config.m_dwHeight,
																				nullptr,
																				nullptr,
																				m_hInst,
																				nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	// display the Window
	ShowWindow( m_hWnd, a_nCmdShow );

	// Force initial refresh
	UpdateWindow( m_hWnd );

	return TRUE;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
BOOL WinMainLauncher::Init( GameApplication* a_application , HINSTANCE a_hInstance, int a_nCmdShow )
{
	s_launcher												=	this;

	// save pointer to the Instance
	m_hInst													=	a_hInstance;

	// Save pointer to the Application
	m_application											=	a_application;

	m_application->SetWindowConfig( m_config );

	RegisterWndClass( );

    // Initialize the Window
	if( !CreateWindowDlg(a_nCmdShow ) )
	{
		return FALSE;
	}

	return TRUE;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void WinMainLauncher::Close()
{
	if( m_application != NULL )
	{
		m_application->Close();
		m_application										=	NULL;
	}

	// Drestroy the Window
	if (m_hWnd)
	{
		SetWindowLong(m_hWnd, GWLP_USERDATA, NULL);
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
int WinMainLauncher::Run( GameApplication* a_application , HINSTANCE a_hInstance, int a_nCmdShow )
{

	Init( a_application , a_hInstance , a_nCmdShow );

	// Initialize the App
	a_application->Init( m_hWnd );

//    HACCEL hAccelTable = LoadAccelerators( m_hInst , MAKEINTRESOURCE(IDC_HELLOTRIANGLE) );


	while( !m_quitRequested )
    {
		// Process all the Windows messages
		ProcessWindowsMessages();

		if( ! m_quitRequested )
		{
			a_application->OnFrame();
		}
    }

	Close();

	return 0;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void WinMainLauncher::ProcessWindowsMessages()
{
    // Main message loop:
	MSG t_msg = { 0 };
	while(  PeekMessage( &t_msg, NULL, 0, 0, PM_REMOVE ) )
    {
		TranslateMessage( &t_msg );
		DispatchMessage( &t_msg );

		// if the User close the window
		if( t_msg.message == WM_QUIT )
		{
			m_quitRequested									=	true;
		}
    }
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void WinMainLauncher::ProcessWindowsMessage( HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam )
{
	ImGuiWrapper::GetInstance()->ProcessWindowsMessages( a_hwnd , a_msg , a_wParam , a_lParam );
}
//---------------------------------------------------------------------------------------------

//
//  FUNCTION: AppWindowProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK AppWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
/*
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
             //   DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
*/
            return DefWindowProc(hWnd, message, wParam, lParam);

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
		s_launcher->ProcessWindowsMessage( hWnd, message, wParam, lParam );
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

/*
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
*/