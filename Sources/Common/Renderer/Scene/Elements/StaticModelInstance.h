#ifndef __STATIC_MODEL_INSTANCE_H__
#define __STATIC_MODEL_INSTANCE_H__

#include "RenderSceneElement.h"
#include "../../Resources/Includes.h"
#include "../../../Core/CoreIncludes.h"


class StaticModelInstance : public RenderSceneElement
{
public:

	StaticModelInstance();
	virtual ~StaticModelInstance();

	/*
	* Init the Instance Properties
	*/
	void Init( RhiGraphicDevice* a_device , const ReferenceCountedPtr<Model>& a_model );


	virtual void AddToRenderList( RhiGraphicContext* a_context , GeometryRenderList* a_renderList );

private:

	//Reference to the Model instanced
	ReferenceCountedPtr<Model>	m_model;


	StaticModelVertexConstants					m_vertexConstants;
	SConstantBuffer<StaticModelVertexConstants>	m_vertexConstantBuffer;
};

#endif