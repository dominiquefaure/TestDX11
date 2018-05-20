#pragma once

#include<Windows.h>

#include "../Common/Includes.h"

#include <d3d11.h>

struct PerFrameConstants
{
	Matrix44	m_viewProjection;
};

struct PerDrawConstants
{
	Matrix44	m_worldTransform;
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

	void LoadShaders(  );
	void LoadGoemetry( RhiGraphicDevice* a_device );

	void DrawTriangle( RhiGraphicContext* a_context );

	void CreateConstantBuffer( RhiGraphicDevice* a_device );


// Fields
private:

	StaticGeometry*		m_geometry;
	ShaderProgram*		m_shader;


	Vector3F			m_translate;

	PerFrameConstants	m_perFrameConstants;
	PerDrawConstants	m_perDrawConstants;

	RhiConstantBuffer*	m_perFrameConstantBuffer;
	RhiConstantBuffer*	m_perDrawConstantBuffer;

};