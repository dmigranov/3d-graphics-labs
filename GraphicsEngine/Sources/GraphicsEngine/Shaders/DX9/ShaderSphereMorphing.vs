float4x4	matrixWorldViewProjT;
float4		materialColor;
float4		time;

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

	//float radius = 2.0;
	float4 p1 = input.Position;
	float4 p2;
	float t = time[0];
	p2.xyz = 2 * normalize(p1.xyz);
	p2.w = p1.w;


	//float4 p2 = mul(radius, normalize(p1));
	//p1 = p1 * 5;
	/*p1[0] = 3 * p1[0];
	p1[1] = 3 * p1[1];
	p1[2] = 3 * p1[2];*/
	//p1.xyz = mul (3.0f, p1.xyz);
	float4 pos;
	pos.w = p1.w;
	//pos.xyz = p1.xyz * (1 - t) + p

	output.Position	= mul(p2, matrixWorldViewProjT);
	
	//output.Color	= materialColor;
	output.Color	= input.Color;
	
	return output;
};