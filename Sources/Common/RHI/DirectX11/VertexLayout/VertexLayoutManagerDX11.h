#ifndef __VERTEX_LAYOUT_MANAGER_DX11_H__
#define __VERTEX_LAYOUT_MANAGER_DX11_H__

#include "../../../Core/CoreIncludes.h"

#include "VertexLayoutDX11.h"

class GraphicDeviceDX11;

class VertexLayoutManagerDX11
{

	friend class GraphicDeviceDX11;


// Methods
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
	VertexLayoutDX11* GetLayout( RhiVertexFormatTypes a_type );

	/*
	* Get the Vertex Layout matching the given Key
	*/
	VertexLayoutDX11* GetLayout( RhiVertexFormatTypeKey a_key );

// fields
private:

	// List of Layout available
	VertexLayoutDX11*				m_layoutList;
};


#endif