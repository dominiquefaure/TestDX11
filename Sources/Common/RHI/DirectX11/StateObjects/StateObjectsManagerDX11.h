#ifndef __RHI_RENDER_STATES_MANAGER_DX11_H__
#define __RHI_RENDER_STATES_MANAGER_DX11_H__

#include <d3d11.h>
#include "../../../Core/CoreIncludes.h"

#include <map>

class GraphicDeviceDX11;

class StateObjectsManagerDX11
{
	friend class GraphicDeviceDX11;

private:

	StateObjectsManagerDX11( );
	~StateObjectsManagerDX11();

	/*
	* Set the Device
	*/
	void Init( ID3D11Device* a_device );

public:


	/*
	* get the Rasterizer State mathcing the given UID , return NULL if none matching
	*
	* @param a_iud	Unique ID for a RasterizerState
	*/
	ID3D11RasterizerState* GetRasterizerState( TUint64 a_uid );

	/*
	* Create a new Rasterizer State, and save it internally with the given UID
	*/
	ID3D11RasterizerState* CreateRasterizerState( TUint64 a_uid ,  D3D11_RASTERIZER_DESC& a_desc );

private:


	// The DX Device representing the Graphic Card
	ID3D11Device*								m_d3dDevice;

	// Map that store the different Rasterizer states, according to an UID
	std::map<TUint64 , ID3D11RasterizerState*>	m_rasterizerStatesMap;

};

#endif