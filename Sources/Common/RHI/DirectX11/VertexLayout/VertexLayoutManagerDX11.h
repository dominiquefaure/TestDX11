#ifndef __RHI_VERTEX_LAYOUT_MANAGER_DX11_H__
#define __RHI_VERTEX_LAYOUT_MANAGER_DX11_H__

#include "../../../Core/CoreIncludes.h"
#include "../../Common/Includes.h"


#include "VertexLayoutDX11.h"

class GraphicDeviceDX11;

class VertexLayoutManagerDX11
{
	friend class GraphicDeviceDX11;

private:

	VertexLayoutManagerDX11();
	~VertexLayoutManagerDX11();

	/*
	* Create all the supported Layouts
	*/
	void Init( GraphicDeviceDX11* a_device );

	/*
	* Get the Vertex Layout matching the given Type
	*/
	VertexLayoutDX11* GetLayout( RhiVertexLayoutType a_type );

	/*
	* Get the Vertex Layout matching the given Key
	*/
	VertexLayoutDX11* GetLayout( RhiVertexLayoutTypeKey a_key );

// fields
private:

	// List of Layout available
	VertexLayoutDX11*				m_layoutList;
};


#endif