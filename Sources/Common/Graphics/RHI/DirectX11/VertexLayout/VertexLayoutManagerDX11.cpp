#include "VertexLayoutManagerDX11.h"



//-----------------------------------------------------------------------------------------------
VertexLayoutManagerDX11::VertexLayoutManagerDX11()
{
	m_layoutList											=	NULL;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
VertexLayoutManagerDX11::~VertexLayoutManagerDX11()
{
	SAFE_DELETE_ARRAY( m_layoutList );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void VertexLayoutManagerDX11::Init( GraphicDeviceDX11* a_device )
{
	m_layoutList											=	new VertexLayoutDX11[ RHI_VERTEX_LAYOUT_COUNT ];

	m_layoutList[ RHI_VERTEX_LAYOUT_POSITION_ONLY ].Build( RHI_VERTEX_LAYOUT_POSITION_ONLY , RHI_VERTEX_FORMAT_KEY_POSITION_ONLY , a_device );
	m_layoutList[ RHI_VERTEX_LAYOUT_POSITION_COLOR ].Build( RHI_VERTEX_LAYOUT_POSITION_COLOR , RHI_VERTEX_FORMAT_KEY_POSITION_COLORED , a_device );
	m_layoutList[ RHI_VERTEX_LAYOUT_SPRITES ].Build( RHI_VERTEX_LAYOUT_SPRITES , RHI_VERTEX_FORMAT_KEY_SPRITES , a_device );
	m_layoutList[ RHI_VERTEX_LAYOUT_BASIC_LIT ].Build( RHI_VERTEX_LAYOUT_BASIC_LIT , RHI_VERTEX_FORMAT_KEY_BASIC_LIT , a_device );

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
VertexLayoutDX11* VertexLayoutManagerDX11::GetLayout( RhiVertexLayoutType a_type )
{
	return &m_layoutList[ a_type ];
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
VertexLayoutDX11* VertexLayoutManagerDX11::GetLayout( RhiVertexLayoutTypeKey a_key )
{
	// Parse the list of layout to search the one matching the key
	VertexLayoutDX11* t_layout;
	for( int i = 0 ; i < RHI_VERTEX_LAYOUT_COUNT ; i ++ )
	{
		t_layout											=	&m_layoutList[ i ];

		// if it's the one we seek , return it
		if( t_layout->GetLayoutKey() == a_key )
		{
			return t_layout;
		}
	}

	// not found
	return NULL;
}
//-----------------------------------------------------------------------------------------------
