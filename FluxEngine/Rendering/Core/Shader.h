#pragma once

class ShaderVariation;

enum class ShaderType
{
	VertexShader,
	PixelShader,
};

class Shader
{
public:
	Shader(ID3D11Device* pDevice);
	~Shader();

	bool Load(const string& filePath);
	ShaderVariation* GetVariation(ShaderType type, const vector<string>& defines = {});
	const string& GetSource(ShaderType type) const;

private:
	string m_FileDir;

	void Compile();
	bool ProcessSource(ifstream& stream, string& output);
	void CommentFunction(string& input, const string& function);

	string m_VertexShaderSource;
	string m_PixelShaderSource;

	ID3D11Device* m_pDevice;
};
