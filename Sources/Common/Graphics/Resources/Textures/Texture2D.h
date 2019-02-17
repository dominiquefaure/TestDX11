#ifndef __GRAPHICS_RESOURCES_TEXTURE2D_H__
#define __GRAPHICS_RESOURCES_TEXTURE2D_H__

#include "../../RHI/Includes.h"
/*
* Standard Immutable Texture
*/
class Texture2D// : public ReferenceCounted
{
public:

	Texture2D();
	virtual ~Texture2D();


	/*
	* Get the RHI Texture
	*/
	inline RhiTexture2D* GetRhiTexture()
	{
		return m_texture;
	}

	/*
	* Init the Texture using the Given Parameters
	*/
	void Init( const RhiTextureDescriptor& a_descriptor , const TUint8* a_datas );


	//void Load

private:

	// the Rhi Texture
	RhiTexture2D* m_texture;

};


#endif