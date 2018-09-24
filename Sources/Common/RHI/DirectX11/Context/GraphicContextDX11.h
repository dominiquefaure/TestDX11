#ifndef __RHI_GRAPHIC_CONTEXT_DX11_H__
#define __RHI_GRAPHIC_CONTEXT_DX11_H__



#include <d3d11.h>

#include "../../../Core/CoreIncludes.h"

#include "GeometryStatesDX11.h"
#include "PipelineStatesDX11.h"

#include "../Buffers/Includes.h"

#include "../../Common/RhiShaderParameterCommon.h"


class GraphicDeviceDX11;
class SwapchainDX11;

class VertexBufferDX11;
class IndexBufferDX11;
class ConstantBufferDX11;

class VertexShaderDX11;
class PixelShaderDX11;
class VertexLayoutDX11;


class ImGuiWrapper;


class GraphicContextDX11
{

	friend class GraphicDeviceDX11;
	friend class ConstantBufferDX11;

	friend class ImGuiWrapper;

public:

	/*
	 * Get the VewrtexLayout currently in use
	 */
	FORCE_INLINE const VertexLayoutDX11* GetVertexLayout()const;

	/*
	* Clear the Screen
	*/
	void Clear( TFloat32 r , TFloat32 g, TFloat32 b );
	
	
	/*
	* Set the Type of primitive the Vertex Streams represent
	*
	* @param a_type		The Type of primitive to use for next drawing
	*/
	void SetPrimitiveType( RhiPrimitiveType a_type );

	/*
	* Set the VertexLayout to use
	*/
	void SetVertexLayout( VertexLayoutDX11* a_layout );

	/*
	* Set one off the Vertex Streams to use
	*
	* @param a_index		:	Index the Stream will be binded at
	* @param a_streamBuffer	:	The Stream storing vertices information's
	* @param a_startOffset	:	Start offset in the Stream
	*/
	void SetVertexStream( TUint32 a_index , VertexBufferDX11* a_streamBuffer , TUint32 a_startOffset = 0 );

	/*
	 *Set the Index buffer to use for Indexed Geometry
	 *
	 *@param a_indexbuffer	The index buffer to use
	 */
	void SetIndexBuffer( IndexBufferDX11* a_indexBuffer , TUint32 a_startOffset = 0 );


	//////
	// Shader Methods
	//////

	/*
	* Bind the Vertex Shader we want to use
	*
	* @param a_shader			the vertex shader to use
	*/
	void SetVertexShader( VertexShaderDX11* a_shader );

	/*
	* Set the Pixel Shader we want to use
	*
	* @param a_shader			the pixel shader to use
	*/
	void SetPixelShader( PixelShaderDX11* a_shader );



	//////
	// CB Methods
	//////

	/*
	* Update the Content of a Constant Buffer using Map/Unmap
	*/
	TBool UpdateConstantBuffer( ConstantBufferDX11* a_buffer , const void* a_data , TUint32 a_size );

	/*
	* Set the Active constant buffer for the Given Slot
	*/
	void SetConstantBuffer( RhiShaderType a_type , int a_slot , const ConstantBufferDX11* a_buffer );





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
	* @param a_primitiveCount	=	Number of Vertex to display
	* @param a_startIndex		=	index of the 1st vertex inside the vertexBuffer
	*/
	void DrawPrimitive( TUint32 a_primitiveCount , TUint32 a_startIndex = 0 );

	/*
	 * Draw an Indexed Primitive
	 * 
	 * @param a_indexCount	number of Indices to use from the index buffer
	 * @param a_startIndex	Start index in side hte index buffer
	 * @param a_startVertex	index of the 1st Vertex to use
	 */
	void DrawIndexedPrimitive( TUint32 a_indexCount , TUint32 a_startIndex = 0 , TUint32 a_startVertex = 0 );




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
	void ResetStates();

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