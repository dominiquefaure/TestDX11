#include "RenderScene.h"
#include "Elements/Includes.h"

#include "Rendering/GeometryRenderList.h"

//-------------------------------------------------------------------------------------------
RenderScene::RenderScene()
{
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
RenderScene::~RenderScene()
{
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void RenderScene::AddElement( RenderSceneElement* a_object )
{
	m_objects.push_back( a_object );
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void RenderScene ::Draw( RhiGraphicContext* a_context )
{
	GeometryRenderList t_renderList;

	int t_elementCount										=	m_objects.size();
	for( int i = 0 ; i < t_elementCount ; i ++ )
	{
		m_objects[ i ]->AddToRenderList( a_context , &t_renderList );
	}

	t_renderList.Render( a_context );
}
//-------------------------------------------------------------------------------------------
