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
void Texture2D::Init( int a_width , int a_height , void* a_datas )
{
	RhiTextureDescriptor t_desc;

	t_desc.m_width											=	a_width;
	t_desc.m_height											=	a_height;
	t_desc.m_usage											=	RHI_BUFFER_USAGE_IMMUTABLE;
	t_desc.m_format											=	TEXTURE_FORMAT_R8G8B8A8;
	t_desc.m_shaderUsage									=	SHADER_USAGE_RESOURCE_READ;

	m_texture												=	RhiManager::GetInstance()->GetGraphicDevice()->CreateTexture2D( t_desc , a_datas );
}
//------------------------------------------------------------------------------------
