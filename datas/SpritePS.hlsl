struct Input
{
	float4 position : SV_POSITION;
	float4 color: COLOR0;
	float2 uv : TEXCOORD0;
};


Texture2D<float4> s_spriteTexture : register(t0);
sampler s_spriteSampler : register(s0);


float4 main(Input input) : SV_TARGET
{
	float4 t_texColor	=	 s_spriteTexture.Sample( s_spriteSampler , input.uv );

	return t_texColor * input.color;
}

