#ifndef __RENDER_SCENE_H__
#define __RENDER_SCENE_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"


class RenderSceneElement;

/*
* Represent a Scene for the renderer
* Contains only Render elements, no game logic
*/
class RenderScene
{
public:

	RenderScene();
	virtual ~RenderScene();

	/*
	* Display the Scene
	*/
	void Draw( RhiGraphicContext* a_context );

	/*
	* Add a Redner element to the scene
	*/
	void AddElement( RenderSceneElement* a_element );
	
private:

	// All the Elements presents in this Scene
	std::vector<RenderSceneElement*>	m_objects;

};

#endif