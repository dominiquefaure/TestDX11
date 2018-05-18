#pragma once

#include<Windows.h>

#include "../Common/Includes.h"

#include <d3d11.h>

struct TriangleVertice
{
	float x;
	float y;
	float z;

	float r;
	float g;
	float b;
	float a;
};


class Sample : public GameApplication
{
public:

	Sample();
	virtual ~Sample();



// pure Virtual methods to be overrided
protected:

	/*
	 * Called at Application initialization, allow to start loading custom data
	 */
	virtual void OnInit();

	/*
	 * Called at Application initialization, allow to start loading custom data
	 */
	virtual void OnClose();

	/*
	 * Called every ticks to perform the update operations
	 */
	virtual void OnUpdate();

	/*
	 *  called every ticks to perform the custom draw operations
	 */
	virtual void OnDraw();

	
	/*
	 * Configure the Windows Dialog
	 */
	virtual void OnSetWindowConfig( WinAppConfig& a_config );

private:

	void CreateVertexBuffer( RhiGraphicDevice* a_device );
	void LoadVertexShader( RhiGraphicDevice* a_device );
	void LoadPixelShader( RhiGraphicDevice* a_device );



	void DrawTriangle( RhiGraphicContext* a_context );




// Fields
private:

	RhiVertexShader*	m_vertexShader;
	RhiPixelShader*		m_pixelShader;


	StaticGeometry*		m_geometry;
};