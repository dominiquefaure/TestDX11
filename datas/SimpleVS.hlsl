
cbuffer meshInfos : register(b0)
{
	float3 m_worldPosition;
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

Output main(Input input)
{
	Output output;

	output.position = float4( m_worldPosition + input.position, 1.0 );

	output.color = float4(input.color.rgb, 1.0);

	return output;
}
