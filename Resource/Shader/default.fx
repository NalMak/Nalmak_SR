
matrix g_world;
matrix g_viewProj;

texture g_mainTex;
float4 g_mainTexColor;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;

};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse0 : COLOR0;
	float4 diffuse1 : COLOR1;
	float4 diffuse2 : COLOR2;
	float4 diffuse3 : COLOR3;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 초기???�수!

	float4x4 wvp = mul(g_world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.uv = _input.uv;
	//o.normal = float3(0, 0, 1);
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(mainSampler, _input.uv);
	float4 final = diffuse * g_mainTexColor;
	o.diffuse0 = final;
	o.diffuse1 = final;
	o.diffuse2 = final;
	o.diffuse3 = final;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z �������� Ȱ��

		//ZEnable = true;
		//ZWriteEnable = true;
		CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
