#include "Texture2D.h"


//------------------------------------------------------------------------------------
Texture2D::Texture2D()
{
	m_texture												=	NULL;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
Texture2D::~Texture2D()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void Texture2D::Init( const RhiTextureDescriptor& a_descriptor , const TUint8* a_datas )
{
/*	RhiTextureDescriptor t_desc;

	t_desc.m_width											=	a_width;
	t_desc.m_height											=	a_height;
	t_desc.m_usage											=	RHI_BUFFER_USAGE_IMMUTABLE;
	t_desc.m_format											=	TEXTURE_FORMAT_R8G8B8A8;
	t_desc.m_shaderUsage									=	SHADER_USAGE_RESOURCE_READ;
*/
	m_texture												=	RhiManager::GetInstance()->GetGraphicDevice()->CreateTexture2D( a_descriptor , a_datas );
}
//------------------------------------------------------------------------------------
