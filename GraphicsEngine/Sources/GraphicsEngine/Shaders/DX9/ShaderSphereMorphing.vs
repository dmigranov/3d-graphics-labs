float4x4	matrixWorldViewProjT;
float4		materialColor;
//float		time;

struct VS_INPUT
{
	float4 	Position	: POSITION;
	float4 	Normal		: NORMAL;
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

	float radius = 2.0;
	float4 p1 = input.Position;
	float4 t = {1,0,0,0};
	float4 p2 = mul(radius, normalize(p1));

	output.Position	= mul(p2, matrixWorldViewProjT);
	output.Color	= materialColor;
	//output.Color	= input.Color;
	
	return output;
};