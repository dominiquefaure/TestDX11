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

class VertexShaderDX11;
class PixelShaderDX11;
class VertexLayoutDX11;
class ConstantBufferDX11;

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

	/*
	* Set the Vertx Layout to use
	*/
	void SetVertexLayout( VertexLayoutDX11* a_layout );





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



	//////
	// VS ConstantBuffer Methods
	//////

	/*
	 * Update a Parameter of one of the Cosntant Buffers
	 */
	void SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , TUint32 a_byteCount , const void* a_value );

	/*
	 * Set a VertexShader constant parameter of type Vector3
	 */
	void SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , const Vector3F* a_value );

	/*
	 * Set a VertexShader constant parameter of type Matrix44
	 */
	void SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , const Matrix44* a_value );


	//////
	// PS ConstantBuffer Methods
	//////

	/*
	 * Update a Parameter of one of the Cosntant Buffers
	 */
	void SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , TUint32 a_byteCount , const void* a_value );

	/*
	 * Set a VertexShader constant parameter of type Vector3
	 */
	void SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , const Vector3F* a_value );

	/*
	 * Set a VertexShader constant parameter of type Matrix44
	 */
	void SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , const Matrix44* a_value );

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

	/*
	 * Init tne Different Constant Buffers
	 */
	void InitConstantBuffers( GraphicDeviceDX11* a_device );

	/*
	 * Free the Different Constant Buffer allocated
	 */
	void ReleaseConstantBuffers();


	/*
	* Update the Content of a Constant Buffer using Map/Unmap
	*/
	TBool UpdateConstantBuffer( ID3D11Buffer* a_buffer , void* a_data , TUint32 a_size );

	/*
	* Set the Active constant buffer for the Given Slot
	*/
	void SetConstantBuffer( RhiShaderType a_type , int a_slot , ID3D11Buffer* a_buffer );

	/*
	 * Commit the ConstantBuffer updates
	 */
	void CommitConstantBuffers( );

private:

	// Set the Owner device
	GraphicDeviceDX11*		m_owner;

	// The Dx context that will perform the render operations
	ID3D11DeviceContext*	m_deviceContext;

	// temporary acces to the Swapchain, later will use RenderTarget
	SwapchainDX11*			m_swapchain;

	GeometryStatesDX11		m_geometryStates;
	PipelineStatesDX11		m_pipelineStates;

	// array of constant buffer for VS stage
	ConstantBufferDX11*		m_vsConstantBuffers[ VS_PARAMETER_SLOT_COUNT ];

	// array of constant buffer for PS stage
	ConstantBufferDX11*		m_psConstantBuffers[ PS_PARAMETER_SLOT_COUNT ];

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "GraphicContextDX11.inl"
#endif

#endif