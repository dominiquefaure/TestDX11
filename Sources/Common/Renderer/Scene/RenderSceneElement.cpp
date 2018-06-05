#include "RenderSceneElement.h"

//-------------------------------------------------------------------------------------------------
RenderSceneElement::RenderSceneElement()
{
	m_worldTransform.SetIdentity();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
RenderSceneElement::~RenderSceneElement()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void RenderSceneElement::SetTransform( Vector3F a_position , Matrix44 a_worldTransform )
{
	m_position												=	a_position;
	m_worldTransform										=	a_worldTransform;

	// allow custom updates
	OnTransformChanged();
}
//-------------------------------------------------------------------------------------------------
