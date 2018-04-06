#ifndef __RHI_RASTERIZER_STATES_DX11_H__
#define __RHI_RASTERIZER_STATES_DX11_H__

#include "../../../Core/CoreIncludes.h"

#include "../StateObjects/RasterizerStateDescriptorDX11.h"


class StateObjectsManagerDX11;
class VertexShaderDX11;
class PixelShaderDX11;


/*
* Store the Pipeline States for a Context
*/
class PipelineStatesDX11
{

	enum dirtyFlags
	{
		DIRTY_FLAG_VERTEX_SHADER		=	1,
		DIRTY_FLAG_PIXEL_SHADER			=	2,
	};

public:

	PipelineStatesDX11();
	~PipelineStatesDX11();

	/*
	* Set reference to the State Object manager to avoid get it every times
	*/
	void SetStateObjectManager( StateObjectsManagerDX11* a_manager );

	/*
	* Reset all the values, to be called at beginning of the Context record
	*/
	void Reset();

	/*
	* commit all the updates made since last call
	*/
	void Commit( ID3D11DeviceContext* a_context );



	/*
	* Set the WireFrame Flag
	*/
	FORCE_INLINE void SetWireframe( TBool a_flag );

	/*
	* Set the desired Culling mode
	*/
	FORCE_INLINE void SetCullingMode( RhiCullingMode a_mode );

	/*
	* set the VertexShader to use
	*
	* @param a_shader	The vertexShader to use
	*/
	void SetVertexShader( VertexShaderDX11* a_shader );

	/*
	* set the PixelShader to use
	*
	* @param a_shader	The PixelShader to use
	*/
	void SetPixelShader( PixelShaderDX11* a_shader );


private:

	TUint32							m_dirtyFlags;

	// Last state UID
	TUint64							m_lastRasterizerUID;

	// Object that store the current state values
	RasterizerStateDescriptorDX11	m_rasterizerStates;

	// pointer to the RenderStateManager for quick access
	StateObjectsManagerDX11*		m_stateObjectsManager;

	// Active Shaders to use
	VertexShaderDX11*				m_vertexShader;
	PixelShaderDX11*				m_pixelShader;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "PipelineStatesDX11.inl"
#endif

#endif