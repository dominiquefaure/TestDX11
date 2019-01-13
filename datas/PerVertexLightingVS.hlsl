
cbuffer perFrameConstants : register(b0)
{
	matrix	m_viewProjection;
	float3	m_lightDir;
	float3	m_lightDiffuse;
};

cbuffer meshInfos : register(b1)
{
	matrix	m_meshTransform;
	float3	m_matDiffuse;
};

struct Input
{
	float3 position : POSITION;
//	float3 color : COLOR;
	float3 normal : NORMAL;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;

};

Output main(Input input)
{
	Output output;


#ifdef USE_PREMULTIPLICATION
	// Pre-multiplication
	matrix t_mvp	=	mul( m_meshTransform , m_viewProjection );
	output.position	=	mul( float4( input.position , 1 ) , t_mvp );
#else
	// Post Multiplication
	matrix t_mvp	=	mul( m_viewProjection , m_meshTransform );
	output.position	=	mul( t_mvp , float4( input.position , 1 ) );
#endif


	float3 diffuse = float3(0.0f, 0.0f, 0.0f); 

	float3 ambient = float3(0.0f, 0.0f, 0.0f);
	float3 spec = float3(0.0f, 0.0f, 0.0f);


	float3 lightVec =	-m_lightDir;

	// compute the normal in model view
	float3 t_normal	=	mul( m_meshTransform , input.normal );


	float t_diffuseFactor	=	dot( lightVec , t_normal );


	if(t_diffuseFactor > 0 )
	{
		diffuse = t_diffuseFactor * m_lightDiffuse; 
	}
	
	output.color	=	float4( diffuse , 1.0 );

	return output;
}
