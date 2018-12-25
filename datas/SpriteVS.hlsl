
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
	float2 uv : TEXCOORD0;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

Output main(Input input)
{
	Output output;


	matrix t_mvp	=	mul( m_viewProjection , m_meshTransform );
	output.position	=	mul( t_mvp , float4( input.position , 1 ) );

	output.color 	=	float4(input.color.rgb, 1.0);
	output.uv		=	input.uv;
	
	return output;
}
