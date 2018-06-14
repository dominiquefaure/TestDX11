#ifndef __RENDER_SCENE_ELEMENT_H__
#define __RENDER_SCENE_ELEMENT_H__

#include "../../Core/CoreIncludes.h"

class RenderSceneElement
{

public:

	RenderSceneElement();
	~RenderSceneElement();


	/*
	* Update the element Transform
	*/
	void SetTransform( Vector3F a_position , Matrix44 a_worldTransform );

	/*
	* Draw this Element
	*/
	virtual void Draw(){}


protected:


	virtual void OnTransformChanged(){}


private:

	// Transform to convert eleemtn from Local space to World space
	Matrix44	m_worldTransform;

	// position of the element in the world
	Vector3F	m_position;
};


#endif