#ifndef __RHI_MANAGER_H__
#define __RHI_MANAGER_H__


#include "../Core/CoreIncludes.h"
#include "RhiWrapper.h"

#include <assert.h>


class ShaderManager;


class RhiManager : public Singleton<RhiManager>
{
	friend class Singleton<RhiManager>;

private:

	RhiManager();
	virtual ~RhiManager();

public:

	/*
	* Get teh Device used to create resource on GPU
	*/
	FORCE_INLINE RhiGraphicDevice* GetGraphicDevice();

	/*
	* Get teh main Context 
	*/
	FORCE_INLINE RhiGraphicContext* GetMainContext();


	void Init( HWND a_handle , TUint32 a_width , TUint32 a_height );

	/*
	* Called at the Start of a Frame, clear the screen
	*/
	void BeginFrame();

	/*
	* Called at the End of a Frame, submit all the rendering commands to Gpu
	*/
	void EndFrame();


private:

	RhiGraphicDevice*		m_device;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "RhiManager.inl"
#endif


#endif