#pragma once


class Shader
{
	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
public:
	bool LoadVertexShader(std::string filename);
	bool LoadFragmentShader(std::string filename);
	bool LinkShader();
	void Use();
};