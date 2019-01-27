
cbuffer perFrameConstants : register(b0)
{
	matrix	m_viewProjection;
};

cbuffer meshInfos : register(b1)
{
	matrix	m_meshTransform;
};

struct Input
{
	float3 position : POSITION;
	float3 color : COLOR;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

#ifdef USE_PREMULTIPLICATION

#define Multiply( b , a )	mul( a , b )
#else

#define Multiply( b , a )	mul( b , a )
#endif


Output main(Input input)
{
	Output output;


	matrix t_mvp	=	Multiply( m_viewProjection , m_meshTransform );
	output.position	=	Multiply( t_mvp , float4( input.position , 1 ) );

	output.color = float4(input.color.rgb, 1.0);

	return output;
}
