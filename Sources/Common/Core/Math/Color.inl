
//--------------------------------------------------------------------------------------------
FORCE_INLINE Color::Color()
{
	r														=	1.0f;
	g														=	1.0f;
	b														=	1.0f;
	a														=	1.0f;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
FORCE_INLINE Color::Color( const Color& a_color )
{
	r														=	a_color.r;
	g														=	a_color.g;
	b														=	a_color.b;
	a														=	a_color.a;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
FORCE_INLINE Color::Color( float a_r , float a_g , float a_b , float a_alpha )
{
	r														=	a_r;
	g														=	a_g;
	b														=	a_b;
	a														=	a_alpha;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
FORCE_INLINE void Color::Set( float a_r , float a_g , float a_b , float a_alpha )
{
	r														=	a_r;
	g														=	a_g;
	b														=	a_b;
	a														=	a_alpha;
}
//--------------------------------------------------------------------------------------------