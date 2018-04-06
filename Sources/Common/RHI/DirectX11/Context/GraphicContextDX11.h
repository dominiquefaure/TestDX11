#ifndef __RHI_GRAPHIC_CONTEXT_DX11_H__
#define __RHI_GRAPHIC_CONTEXT_DX11_H__



#include <d3d11.h>

#include "../../../Core/CoreIncludes.h"

#include "GeometryStatesDX11.h"
#include "PipelineStatesDX11.h"

#include "../Buffers/Includes.h"

class GraphicDeviceDX11;
class SwapchainDX11;

class VertexShaderDX11;
class PixelShaderDX11;


class GraphicContextDX11
{

	friend class GraphicDeviceDX11;


public:

	// To be Removed!!!!!!
	inline ID3D11DeviceContext* GetContext()
	{
		return m_deviceContext;
	}


	/*
	* Clear the Screen
	*/
	void Clear( TFloat32 r , TFloat32 g, TFloat32 b );

	/*
	* Set one off the Vertex Streams to use
	*
	* @param a_index		:	Index the Stream will be binded at
	* @param a_streamBuffer	:	The Stream storing vertices information's
	* @param a_startOffset	:	Start offset in the Stream
	*/
	void SetVertexStream( int a_index , VertexBufferDX11* a_streamBuffer , TUint32 a_startOffset = 0 );

	/*
	 *Set the Index buffer to use for Indexed Geometry
	 *
	 *@param a_indexbuffer	The index buffer to use
	 */
	void SetIndexBuffer( IndexBufferDX11* a_indexBuffer , TUint32 a_startOffset = 0 );

	/*
	* Set the Type of primitive the Vertex Streams represent
	*
	* @param a_type		The Type of primitive to use for next drawing
	*/
	void SetPrimitiveType( RhiPrimitiveType a_type );


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


	//////
	// Rasterizer states Methods
	//////

	/*
	* Set the Wireframe/Solid mode
	*/
	FORCE_INLINE void SetWireframe( TBool a_wireframe );

	/*
	* Set the Culling Mode
	*/
	FORCE_INLINE void SetCullingMode( RhiCullingMode a_mode);

	//////
	// Draw Methods
	//////

	/*
	* Draw a Primitive, using the Different Buffer binded
	*
	* @a_primitiveCount	=	Number of Vertex to display
	* @a_startIndex		=	index of the 1st vertex inside the vertexBuffer
	*/
	void DrawPrimitive( int a_primitiveCount , int a_startIndex = 0 );

	void DrawIndexedPrimitive( int a_indexCount , int a_startIndex = 0 , int a_startVertex = 0 );

// Private Methods
private:

	GraphicContextDX11();
	~GraphicContextDX11();

	/*
	* Initialize correctly this Context
	*/
	void Init( GraphicDeviceDX11* a_owner ,  ID3D11DeviceContext* a_context  );

	void SetSwapchain( SwapchainDX11* a_swapchain );

	/*
	* Called at the beginning of the Frame, prepare the rendering
	*/
	void OnBeginFrame();

	/*
	* Flush all the  drawing operations
	*/
	void Flush();

	/*
	* Reset all the States
	*/
	void ResetSttes();

	/*
	* Commit all the modified states since last draw
	*/
	void CommitStates();

private:

	// Set the Owner device
	GraphicDeviceDX11*		m_owner;

	// The Dx context that will perform the render operations
	ID3D11DeviceContext*	m_deviceContext;

	// temporary acces to the Swapchain, later will use RenderTarget
	SwapchainDX11*			m_swapchain;

	GeometryStatesDX11		m_geometryStates;
	PipelineStatesDX11		m_pipelineStates;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "GraphicContextDX11.inl"
#endif

#endif