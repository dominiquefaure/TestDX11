#ifndef __WINMAIN_LAUNCHER_H__
#define __WINMAIN_LAUNCHER_H__

#include <Windows.h>

#include "WindowsAppConfig.h"
#include "GameApplication.h"

#include "../Core/CoreIncludes.h"

class WinMainLauncher
{
public:
	WinMainLauncher();
	~WinMainLauncher();
	


	int Run( GameApplication* a_application , HINSTANCE a_hInstance, int a_nCmdShow );

// MEthods
private:

	BOOL Init( GameApplication* a_application , HINSTANCE a_hInstance, int a_nCmdShow );

	/*
	* Close the Application
	*/
	void Close();

	/*
	* Register the WNDCLASSEX Class
	*/
	BOOL RegisterWndClass( );


	BOOL CreateWindowDlg( int a_nCmdShow );


	void ProcessWindowsMessages();

//// Fields
private:
	HINSTANCE     m_hInst;
	HWND          m_hWnd;


	WNDCLASSEX		m_stWcex;


	WinAppConfig		m_config;

	GameApplication*	m_application;

	TBool				m_quitRequested;
};

#endif