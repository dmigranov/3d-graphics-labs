
float4x4	lower;
float4x4	upper;
float4x4	matrixWorldViewProjT;
float4		materialColor;




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

	float3 p1 = input.Position;
	float alpha = (p1.y + 1.0)/2.0;


	float4 pos = float4(p1, 1);
	

	float4x4 res = upper * (1 - alpha) + lower * (alpha);
	//res[3][3] = 1;


	float4 newPos = mul(pos, res);

	output.Position	= mul(newPos, matrixWorldViewProjT);
	
	//output.Color	= materialColor;
	output.Color	= input.Color;
	
	return output;
};