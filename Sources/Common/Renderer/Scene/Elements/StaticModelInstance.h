#ifndef __STATIC_MODEL_INSTANCE_H__
#define __STATIC_MODEL_INSTANCE_H__

#include "RenderSceneElement.h"
#include "../../Resources/Includes.h"
#include "../../../Core/CoreIncludes.h"

struct StaticModelVertexConstants
{
	// The Mesh World Transform
	Matrix44	m_worldTransform;
};

class StaticModelInstance : public RenderSceneElement
{
public:

	StaticModelInstance();
	virtual ~StaticModelInstance();

	/*
	* Init the Instance Properties
	*/
	void Init( RhiGraphicDevice* a_device , const ReferenceCountedPtr<Model>& a_model );

	/*
	* Draw this Object
	*/
	virtual void Draw( RhiGraphicContext* a_context );

private:

	//Reference to the Model instanced
	ReferenceCountedPtr<Model>	m_model;


	StaticModelVertexConstants					m_vertexConstants;
	SConstantBuffer<StaticModelVertexConstants>	m_vertexConstantBuffer;
};

#endif