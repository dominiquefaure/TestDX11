#ifndef __RENDERER_GEOMETRY_RENDER_LIST_H__
#define __RENDERER_GEOMETRY_RENDER_LIST_H__

#include "GeometryRenderElement.h"

/*
* Store a list of elements to render
* After the list have been draw the elements will be disposed
*/
class GeometryRenderList
{

public:

	GeometryRenderList();
	~GeometryRenderList();

	/*
	* Add a new Element to the List
	*/
	void AddElement( GeometryRenderElement* a_element );

	/*
	* Render all the elements presents in the List
	*/
	void Render(  RhiGraphicContext* a_context );

	/*
	* Clear the List ( all the Render elements will deleted
	*/
	void Clear( );

private:

	// list of Elements to Render
	std::vector<GeometryRenderElement*>	m_elements;

};

#endif