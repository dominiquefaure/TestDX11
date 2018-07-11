#pragma once

#include<Windows.h>

#include "../Common/Includes.h"

#include <d3d11.h>

struct PerFrameConstants
{
	Matrix44	m_viewProjection;
	Vector3F	m_lightDirection;
	float		m_padding1;
	Vector3F	m_lightDiffuse;
	float		m_padding2;

};

struct PerDrawConstants
{
	Matrix44	m_worldTransform;
	Vector3F	m_matDiffuse;
	float		m_padding;

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
	virtual void OnUpdate( TFloat32 a_deltaTime );

	/*
	 *  called every ticks to perform the custom draw operations
	 */
	virtual void OnDraw();

	virtual void DrawDebugUI();	
	/*
	 * Configure the Windows Dialog
	 */
	virtual void OnSetWindowConfig( WinAppConfig& a_config );

private:

	void LoadShaders(  );
	void LoadGoemetry( RhiGraphicDevice* a_device );

	void DrawTriangle( RhiGraphicContext* a_context );

	void CreateConstantBuffer( RhiGraphicDevice* a_device );

	void TestWriter();
// Fields
private:

	StaticMesh*			m_mesh;

	ShaderProgram*		m_shader;


	Vector3F			m_translate;
	Vector3F			m_rotate;
	Vector3F			m_scale;

	PerFrameConstants	m_perFrameConstants;
	PerDrawConstants	m_perDrawConstants;

	SConstantBuffer<PerFrameConstants>	m_perFrameConstantBuffer;
	SConstantBuffer<PerDrawConstants>	m_perDrawConstantBuffer;


};