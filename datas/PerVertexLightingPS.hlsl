cbuffer MaterialParams : register(b0)
{
	float3	m_matDiffuse;
};


struct Input
{
	float4 position : SV_POSITION;
	float4 color: COLOR0;

};

float4 main(Input input) : SV_TARGET
{
	return input.color * float4( m_matDiffuse , 1.0 );
//	return float4( 1.0 , 0.0 , 1.0 , 1.0 );
}

