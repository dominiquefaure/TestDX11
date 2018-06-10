#ifndef __DEBUG_UI_IMGUI_WRAPPER_H___
#define __DEBUG_UI_IMGUI_WRAPPER_H___

#include "../Core/CoreIncludes.h"
#include "../../Thirdparty/ImGui/imgui.h"

#include <d3d11.h>

class ImGuiWrapper: public Singleton<ImGuiWrapper>
{

	friend class Singleton<ImGuiWrapper>;

private:

	ImGuiWrapper();
	virtual ~ImGuiWrapper();


public:

	void InitImGUI( void* a_hwnd , int a_width , int a_height );

	void ProcessWindowsMessages( HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam );

	void BeginFrame();
	void EndFrame();




	static void DrawCallback( ImDrawData* a_drawData );

private:

	/*
	* Create the required font textures
	*/
	void CreateFonts();


private:

	ID3D11ShaderResourceView*	m_fontResourceView;
	ID3D11SamplerState*			m_fontSampler;
};

#endif