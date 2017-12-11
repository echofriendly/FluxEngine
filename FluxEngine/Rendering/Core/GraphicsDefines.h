#pragma once

namespace GraphicsConstants
{
	static const int MAX_VERTEX_BUFFERS = 4;
	static const int SHADER_TYPES = 4;
}

enum class ShaderType : unsigned int
{
	VertexShader = 0,
	PixelShader,
	GeometryShader,
	ComputeShader,
	NONE,
};

inline ShaderType operator|(const ShaderType a, const ShaderType b)
{
	return (ShaderType)((unsigned int)a | (unsigned int)b);
}

inline ShaderType& operator|=(ShaderType& a, const ShaderType b)
{
	a = (ShaderType)((unsigned int)a | (unsigned int)b);
	return a;
}

//The primitive topology for rendering
enum class PrimitiveType : unsigned char
{
	TRIANGLELIST,
	POINTLIST,
	TRIANGLESTRIP,
};

//The windwo type
enum class WindowType : unsigned char
{
	WINDOWED,
	BORDERLESS,
	FULLSCREEN,
};

//The fillmode of the rasterizer state
enum class FillMode : unsigned char
{
	SOLID,
	WIREFRAME,
};

//The cull mode of the rasterizer state
enum class CullMode : unsigned char
{
	FRONT,
	BACK,
	NONE,
};

//The blend mode of the blend state
enum class BlendMode : unsigned char
{
	REPLACE,
	ADD,
	MULTIPLY,
	ALPHA,
	ADDALPHA,
	PREMULALPHA,
	INVDESTALPHA,
	SUBTRACT,
	SUBTRACTALPHA,
	UNDEFINED,
};

//Color write mode of the blend state
enum class ColorWrite : unsigned char //MAX 5!
{
	NONE = 0,
	RED = 1 << 0,
	GREEN = 1 << 1,
	BLUE = 1 << 2,
	ALPHA = 1 << 3,
	ALL = RED | GREEN | BLUE | ALPHA,
};

//Compare mode for rendering state
enum class CompareMode : unsigned char
{
	ALWAYS,
	EQUAL,
	NOTEQUAL,
	LESS,
	LESSEQUAL,
	GREATER,
	GREATEREQUAL,
	UNDEFINED,
};

//Sntecil operation for the depth stencil state
enum class StencilOperation : unsigned char
{
	KEEP,
	ZERO,
	REF,
	INCR,
	DECR
};

//The convention for the shader constant buffer register
enum class ShaderParameterType
{
	PerFrame = 0,
	PerView = 1,
	PerObject = 2,
	Custom = 3,
	MAX
};

//Predefined texture slot per convention
enum class TextureSlot
{
	Diffuse = 0,
	Normal,
	MAX
};

enum class TextureAddressMode
{
	WRAP,
	MIRROR,
	CLAMP,
	BORDER,
	MIRROR_ONCE,
};

enum class TextureFilter
{
	MIN_MAG_MIP_POINT,
	MIN_MAG_POINT_MIP_LINEAR,
	MIN_POINT_MAG_LINEAR_MIP_POINT,
	MIN_POINT_MAG_MIP_LINEAR,
	MIN_LINEAR_MAG_MIP_POINT,
	MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	MIN_MAG_LINEAR_MIP_POINT,
	MIN_MAG_MIP_LINEAR,
	ANISOTROPIC,
	COMPARISON_MIN_MAG_MIP_POINT,
	COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
	COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
	COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
	COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
	COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
	COMPARISON_MIN_MAG_MIP_LINEAR,
	COMPARISON_ANISOTROPIC,
	MINIMUM_MIN_MAG_MIP_POINT,
	MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
	MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
	MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
	MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
	MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
	MINIMUM_MIN_MAG_MIP_LINEAR,
	MINIMUM_ANISOTROPIC,
	MAXIMUM_MIN_MAG_MIP_POINT,
	MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
	MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
	MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
	MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
	MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
	MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
	MAXIMUM_MIN_MAG_MIP_LINEAR,
	MAXIMUM_ANISOTROPIC,
};

//Bitflag to clear textures
enum class ClearFlags
{
	NONE,
	Depth = 1 << 0,
	Stencil = 1 << 1,
	RenderTarget = 1 << 2,
	All = Depth | Stencil | RenderTarget,
};

inline ClearFlags operator|(const ClearFlags a, const ClearFlags b)
{
	return (ClearFlags)((unsigned int)a | (unsigned int)b);
}

inline ClearFlags& operator|=(ClearFlags& a, const ClearFlags b)
{
	a = (ClearFlags)((unsigned int)a | (unsigned int)b);
	return a;
}