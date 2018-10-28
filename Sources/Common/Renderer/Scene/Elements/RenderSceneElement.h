#ifndef __RENDER_SCENE_ELEMENT_H__
#define __RENDER_SCENE_ELEMENT_H__

#include "../../../Core/CoreIncludes.h"
#include "../../../RHI/Includes.h"

class GeometryRenderList;

class RenderSceneElement
{

public:

	RenderSceneElement();
	virtual ~RenderSceneElement();


	/*
	* Update the element Transform
	*/
	void SetTransform( Vector3F a_position , Matrix44 a_worldTransform );

	/*
	* Add the Element to a Render List
	*/
	virtual void AddToRenderList( RhiGraphicContext* a_context , GeometryRenderList* a_renderList ){}

protected:


	virtual void OnTransformChanged(){}


protected:

	// Transform to convert eleemtn from Local space to World space
	Matrix44	m_worldTransform;

	// position of the element in the world
	Vector3F	m_position;
};


#endif