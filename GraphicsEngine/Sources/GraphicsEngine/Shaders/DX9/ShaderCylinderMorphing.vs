float4x4	matrixWorldViewProjT;

float4		materialColor;
float4		time;

struct VS_INPUT
{
	float3 	Position	: POSITION;
	float4 	Color		: COLOR;
};

struct VS_OUTPUT
{
	float4 	Position	: POSITION;
	float4 	Color		: COLOR0;
};

VS_OUTPUT main( VS_INPUT input )
{
	VS_OUTPUT output;

	//float radius = 2.0;
	float3 p1 = input.Position;
	float3 p2 = 2 * normalize(p1);
	//float t = time[0];


	//float3 pos = p1 * (1 - time[0]) + p2 * time[0];
	float3 pos = lerp (p1, p2, time[0]);
	float4 pos4 = float4(pos, 1);


	output.Position	= mul(pos4, matrixWorldViewProjT);
	
	//output.Color	= materialColor;
	output.Color	= input.Color;
	
	return output;
};