#ifndef __RHI_RASTERIZER_STATE_DESCRIPTOR_DX11_H__
#define __RHI_RASTERIZER_STATE_DESCRIPTOR_DX11_H__

#include "../../../../Core/CoreIncludes.h"

#include "../../RhiEnums.h"

#include <d3d11.h>

/*
* Class that Describe an expected Rasterizer State
*/
class RasterizerStateDescriptorDX11
{

public:

	RasterizerStateDescriptorDX11();
	~RasterizerStateDescriptorDX11();

	/*
	* Get the Unique ID representing this Descriptor , computed from the different components
	*/
	TUint64 GetUID() const;

	
	/*
	* Get the WireFrame flag
	*/
	FORCE_INLINE TBool IsWareframe()const;

	/*
	* get the Current Culling mode Setting
	*/
	FORCE_INLINE RhiCullingMode GetCullingMode()const;



	/*
	* Set the WireFrame Flag
	*/
	FORCE_INLINE void SetWireframe( TBool a_flag );

	/*
	* Set the desired Culling mode
	*/
	FORCE_INLINE void SetCullingMode( RhiCullingMode a_mode );


	/*
	* Set the Default values
	*/
	void SetDefault();

	/*
	* Configure correctly a Rasterizer Descriptor according to the current values
	*/
	void SetupRasterizerState( D3D11_RASTERIZER_DESC& a_desc );

private:

	RhiCullingMode	m_cullingMode;

	// use the wireframe mode?
	TBool			m_useWireframe;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "RasterizerStateDescriptorDX11.inl"
#endif

#endif