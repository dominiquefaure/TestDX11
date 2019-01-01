#include "StateObjectsManagerDX11.h"
#include <assert.h>


//----------------------------------------------------------------------------------------------------
StateObjectsManagerDX11::StateObjectsManagerDX11( )
{
	m_d3dDevice												=	NULL;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
StateObjectsManagerDX11::~StateObjectsManagerDX11()
{
	m_d3dDevice												=	NULL;

	//TODO: release the create rasterizer states
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void StateObjectsManagerDX11::Init( ID3D11Device* a_device )
{
	m_d3dDevice												=	a_device;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
ID3D11RasterizerState* StateObjectsManagerDX11::GetRasterizerState( TUint64 a_uid )
{
	// try to find the rasterizerstate matching the given UID
	auto t_it												=	m_rasterizerStatesMap.find( a_uid );

	// if found return it
	if( t_it != m_rasterizerStatesMap.end() )
	{
		return t_it->second;
	}

	return NULL;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
ID3D11RasterizerState* StateObjectsManagerDX11::CreateRasterizerState( TUint64 a_uid ,  D3D11_RASTERIZER_DESC& a_desc )
{
	ID3D11RasterizerState* t_state;

	HRESULT t_result										=	m_d3dDevice->CreateRasterizerState( &a_desc , &t_state );

	assert( t_result == S_OK );

	// insert the rasterizer to the map
	m_rasterizerStatesMap[ a_uid ]							=	t_state;

	// return the state computed
	return t_state;
}
//----------------------------------------------------------------------------------------------------
