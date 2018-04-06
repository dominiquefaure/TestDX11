#ifndef __RHI_RASTERIZER_STATES_DX11_H__
#define __RHI_RASTERIZER_STATES_DX11_H__

#include "../../../Core/CoreIncludes.h"

#include "../StateObjects/RasterizerStateDescriptorDX11.h"


class StateObjectsManagerDX11;

/*
* Store the Pipeline States for a Context
*/
class PipelineStatesDX11
{

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


private:

	// Last state UID
	TUint64							m_lastRasterizerUID;

	// Object that store the current state values
	RasterizerStateDescriptorDX11	m_rasterizerStates;

	// pointer to the RenderStateManager for quick access
	StateObjectsManagerDX11*		m_stateObjectsManager;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "PipelineStatesDX11.inl"
#endif

#endif