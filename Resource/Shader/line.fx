
matrix g_world;
matrix g_viewProj;

float4 g_color;

struct VS_INPUT
{
	float3 position : POSITION;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
};

struct PS_INPUT
{
	
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 초기???�수!
	
	float4x4 wvp = mul(g_world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	
	return o;
}


PS_OUTPUT PS_Main_Default() 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	o.diffuse = g_color;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		ZEnable = false;
		ZWriteEnable = false;
		//CullMode = CW;

		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();


	}

	
};
