#include "ImGuiWrapper.h"
#include <d3d11.h>

#include "../../Thirdparty/ImGui/imgui.h"

#include "../RHI/Includes.h"

#include "imgui_impl_dx11.h"

//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::DrawCallback( ImDrawData* a_drawData )
{

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ImGuiWrapper::ImGuiWrapper()
{

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
ImGuiWrapper::~ImGuiWrapper()
{

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::InitImGUI( HWND a_hwnd , int a_width , int a_height )
{
	m_screenHandle											=	a_hwnd;

/*	ImGuiIO& t_io											=	ImGui::GetIO();

	t_io.RenderDrawListsFn									=	ImGuiWrapper::DrawCallback;
	t_io.ImeWindowHandle									=	a_hwnd;
    t_io.DisplaySize										=	ImVec2( (float) a_width, (float)a_height );
	t_io.DeltaTime											=	1/60.0f;

	CreateFonts();
*/
	ID3D11Device* t_d3dDevice	=	RhiManager::GetInstance()->GetGraphicDevice()->GetD3DDevice();

	ID3D11DeviceContext* t_context	=	RhiManager::GetInstance()->GetGraphicDevice()->GetMainContext()->GetContext();

	ImGui_ImplDX11_Init( a_hwnd ,t_d3dDevice , t_context );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::BeginFrame()
{
//	ImGui::NewFrame();

	ImGui_ImplDX11_NewFrame();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::EndFrame()
{

	ImGui::Render();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::CreateFonts()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* t_pixels;
    int t_width, t_height;
    io.Fonts->GetTexDataAsRGBA32( &t_pixels, &t_width, &t_height );

	ID3D11Device* t_d3dDevice	=	RhiManager::GetInstance()->GetGraphicDevice()->GetD3DDevice();

    // Upload texture to graphics system
    {
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = t_width;
        desc.Height = t_height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D *pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = t_pixels;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        t_d3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        t_d3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &m_fontResourceView);
        pTexture->Release();
    }

    // Store our identifier
    io.Fonts->TexID = (void *)m_fontResourceView;

    // Create texture sampler
    {
        D3D11_SAMPLER_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.MipLODBias = 0.f;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.MinLOD = 0.f;
        desc.MaxLOD = 0.f;
        t_d3dDevice->CreateSamplerState(&desc, &m_fontSampler);
    }

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TBool ImGuiWrapper::IsAnyMouseButtonDown()
{
	ImGuiIO& io = ImGui::GetIO();
	for (int n = 0; n < IM_ARRAYSIZE(io.MouseDown); n++)
	{
		if (io.MouseDown[n])
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
void ImGuiWrapper::ProcessWindowsMessages( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    ImGuiIO& io = ImGui::GetIO();
    switch (msg)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
    {
        int button = 0;
        if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
        if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
        if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
        if (!IsAnyMouseButtonDown() && GetCapture() == NULL)
            SetCapture(hwnd);
        io.MouseDown[button] = true;
        break;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    {
        int button = 0;
        if (msg == WM_LBUTTONUP) button = 0;
        if (msg == WM_RBUTTONUP) button = 1;
        if (msg == WM_MBUTTONUP) button = 2;
        io.MouseDown[button] = false;
        if (!IsAnyMouseButtonDown() && GetCapture() == hwnd)
            ReleaseCapture();
        break;
    }
    case WM_MOUSEWHEEL:
        io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
        break;
    case WM_MOUSEHWHEEL:
        io.MouseWheelH += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
        break;
    case WM_MOUSEMOVE:
        io.MousePos.x = (signed short)(lParam);
        io.MousePos.y = (signed short)(lParam >> 16);
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (wParam < 256)
            io.KeysDown[wParam] = 1;
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        if (wParam < 256)
            io.KeysDown[wParam] = 0;
        break;
    case WM_CHAR:
        // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
        if (wParam > 0 && wParam < 0x10000)
            io.AddInputCharacter((unsigned short)wParam);
        break;
    }
}
//-------------------------------------------------------------------------------------------------
