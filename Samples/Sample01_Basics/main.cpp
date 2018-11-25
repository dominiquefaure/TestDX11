#include "Sample.h"


#include "../Common/Includes.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

	WinMainLauncher	t_launcher;
	Sample t_sample;

	return t_launcher.Run( &t_sample , hInstance , nCmdShow );

}

