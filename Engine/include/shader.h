#pragma once

#include <map>

class Shader
{
	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	std::map<std::string, GLuint> uniforms;
public:
	bool LoadVertexShader(std::string filename);
	bool LoadFragmentShader(std::string filename);
	GLuint Uniform(std::string uniformName);
	bool LinkShader();
	void Use();
};