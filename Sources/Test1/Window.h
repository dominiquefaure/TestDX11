#pragma once

#include <Windows.h>

class Window
{
public:
	Window( int width, int height );

	HWND GetHandle();

private:
	HWND m_handle;
};
