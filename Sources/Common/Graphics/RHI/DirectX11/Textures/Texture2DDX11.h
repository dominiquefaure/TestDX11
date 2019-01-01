#ifndef __RHI_TEXTURE2D_DX11_H__
#define __RHI_TEXTURE2D_DX11_H__


#include "../../Common/Includes.h"
#include <d3d11.h>

class GraphicDeviceDX11;

class Texture2DDX11
{
	friend class GraphicDeviceDX11;

private:

	Texture2DDX11();
	~Texture2DDX11();


public:


	ID3D11ShaderResourceView* GetResourceView();

protected:

	void Init( GraphicDeviceDX11* a_device , const RhiTextureDescriptor& a_desc , ID3D11Texture2D* a_texture );


// Fields
private:


	RhiTextureDescriptor		m_descriptor;

	// the Graphic Device used to Create this Texture
	GraphicDeviceDX11*			m_owner;

	// the Dx Texture
	ID3D11Texture2D*			m_texture;


	ID3D11ShaderResourceView*	m_resourceView;

};


#endif