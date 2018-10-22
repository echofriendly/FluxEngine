#include "Constants.hlsl"
#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Lighting.hlsl"
#ifdef SKINNED
#include "Skinning.hlsl"
#endif

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;
#ifdef NORMALMAP
	float3 tangent : TANGENT;
#endif

#ifdef SKINNED
	int4 boneIndex : BLENDINDEX;
	float4 vertexWeight : BLENDWEIGHT;
#endif
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 worldPosition : TEXCOORD1;
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL;

#ifdef NORMALMAP
	float3 tangent : TANGENT;
#endif
};

#ifdef COMPILE_VS
PS_INPUT VSMain(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

#ifdef SKINNED

#ifdef DUAL_QUATERNION
	float2x4 dualQuaternion = BlendBoneTransformsToDualQuaternion(input.boneIndex, input.vertexWeight);
	float4 transformedPosition = float4(DualQuatTransformPoint(input.position, dualQuaternion[0], dualQuaternion[1]), 1);
	float3 transformedNormal = QuaternionRotateVector(input.normal, dualQuaternion[0]);
	float3 transformedTangent = QuaternionRotateVector(input.tangent, dualQuaternion[0]);
#else
	float4x4 finalMatrix = BlendBoneTransformsToMatrix(input.boneIndex, input.vertexWeight);
	float4 transformedPosition = mul(float4(input.position, 1.0f), finalMatrix);
	float3 transformedNormal = mul(input.normal, (float3x3)finalMatrix);
	float3 transformedTangent = mul(input.tangent, (float3x3)finalMatrix);
#endif

	output.position = mul(transformedPosition, cWorldViewProj);
	output.worldPosition = mul(transformedPosition, cWorld);
	output.normal = normalize(mul(transformedNormal, (float3x3)cWorld));

#ifdef NORMALMAP
	output.tangent = normalize(mul(transformedTangent, (float3x3)cWorld));
#endif

#else
	output.position = mul(float4(input.position, 1.0f), cWorldViewProj);
	output.worldPosition = mul(float4(input.position, 1.0f), cWorld);
	output.normal = normalize(mul(input.normal, (float3x3)cWorld));

#ifdef NORMALMAP
	output.tangent = input.tangent;
#endif

#endif

	output.texCoord = input.texCoord;
	return output;
}
#endif

#ifdef COMPILE_PS

float4 PSMain(PS_INPUT input) : SV_TARGET
{
	float4 output = (float4)0;

	float3 normal = normalize(input.normal);

#ifdef NORMALMAP
	normal = CalculateNormal(normal, normalize(input.tangent), input.texCoord, false);
#endif

	float3 viewDirection = normalize(input.worldPosition.xyz - cViewInverse[3].xyz);
	LightResult result = DoLight(input.worldPosition, normal, viewDirection);
	float4 diffuse = result.Diffuse;
	float4 specular = result.Specular;

#ifdef DIFFUSEMAP
	diffuse *= Sample2D(Diffuse, input.texCoord);
#endif

#ifdef SPECULARMAP
	specular *= Sample2D(Specular, input.texCoord);
#endif

	output += diffuse;
	output += specular;

#ifdef ENVMAP
	output += CubeMapReflection(normal, viewDirection, 1.0f, 0.4f, 0.0f);
#endif

	output.a = 0.9f;

	return output;
}
#endif