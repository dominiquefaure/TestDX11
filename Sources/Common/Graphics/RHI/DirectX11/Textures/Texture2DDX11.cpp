
#include "Texture2DDX11.h"

#include "../GraphicDeviceDX11.h"


//-------------------------------------------------------------------------
Texture2DDX11::Texture2DDX11()
{
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
Texture2DDX11::~Texture2DDX11()
{
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void Texture2DDX11::Init( GraphicDeviceDX11* a_device , const RhiTextureDescriptor& a_desc , ID3D11Texture2D* a_texture )
{
	m_owner													=	a_device;
	m_descriptor											=	a_desc;

	m_texture												=	a_texture;

	m_resourceView											=	m_owner->CreateShaderResourceView( m_texture , m_descriptor.m_format , m_descriptor.m_mipmapCount );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
ID3D11ShaderResourceView* Texture2DDX11::GetResourceView()
{

	return m_resourceView;
}
//-------------------------------------------------------------------------
