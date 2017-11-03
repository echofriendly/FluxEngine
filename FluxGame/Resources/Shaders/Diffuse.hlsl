#include "Uniforms.hlsl"
#include "Samplers.hlsl"

#ifdef COMPILE_PS
cbuffer cShaderConstantsPS : register(b3)
{
	float4 cColorPS;
}
#endif

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

#ifdef COMPILE_VS
PS_INPUT VSMain(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	input.position += input.worldPosition;
	output.position = mul(cWorldViewProjVS, float4(input.position + sin(cElapsedTimeVS) * input.normal * 0.1f, 1.0f));
	output.normal = normalize(mul((float3x3)cWorldVS, input.normal));
	output.texCoord = input.texCoord;

	return output;
}
#endif

#ifdef COMPILE_PS
float4 PSMain(PS_INPUT input) : SV_TARGET
{
	float diffuseStrength = saturate(dot(input.normal, -cLightDirectionPS));
	float4 sample = tDiffuseTexture.Sample(sDiffuseSampler, input.texCoord);
	return float4((sample.rgb * cColorPS.rgb) * diffuseStrength, 1.0f);
}
#endif