#pragma once
#include "GraphicsDefines.h"
class Shader;
class ConstantBuffer;
class Graphics;

enum class ShaderType : unsigned int;

struct ShaderParameter
{
	ShaderType Type;
	string Name;
	int Buffer;
	int Size;
	int Offset;
	ConstantBuffer* pBuffer;
};

class ShaderVariation
{
public:
	ShaderVariation(Shader* pOwner, const ShaderType type);
	~ShaderVariation();

	bool Create(Graphics* pGraphics);
	void Release();
	void SetDefines(const string& defines);

	const map<string, ShaderParameter>& GetParameters() const { return m_ShaderParameters; }
	const array<ConstantBuffer*, (unsigned int)ShaderParameterType::MAX>& GetConstantBuffers() const { return m_ConstantBuffers; }

	const void* GetShaderObject() const { return m_pShaderObject; }
	const vector<char>& GetByteCode() const { return m_ShaderByteCode; }

	const std::string& GetName() const { return m_Name; }

private:
	bool Compile(Graphics* pGraphics);

	void ShaderReflection(char* pBuffer, unsigned bufferSize, Graphics* pGraphics);

	Shader* m_pParentShader;
	ShaderType m_ShaderType;

	void* m_pShaderObject = nullptr;

	string m_Name;
	vector<string> m_Defines;
	vector<char> m_ShaderByteCode;

	map<string, ShaderParameter> m_ShaderParameters;
	array<ConstantBuffer*, (unsigned int)ShaderParameterType::MAX> m_ConstantBuffers = {};
};