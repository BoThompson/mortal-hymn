#include <GL\glew.h>
#include <SFML\OpenGL.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "shader.h"

const std::string shader_file_path = "shaders";

void Shader::SetName(std::string name)
{
	_name = name;
}


bool Shader::LoadVertexShader(std::string filename)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	std::ifstream VertexShaderStream(shader_file_path + "\\" + filename, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			vertexShaderCode += Line + "\n";
		VertexShaderStream.close();
	}
	else {
		printf("Failed to open %s. Path may be bad.\n", shader_file_path.c_str());
		getchar();
		return false;
	}
	char const * VertexSourcePointer = vertexShaderCode.c_str();
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(_vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(_vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		glDeleteShader(_vertexShaderID);
		_vertexShaderID = 0;
		return false;
	}
	return true;
}

bool Shader::LoadFragmentShader(std::string filename)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	fragmentShaderCode = "";
	std::ifstream FragmentShaderStream(shader_file_path + "\\" + filename, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			fragmentShaderCode += Line + "\n";
		FragmentShaderStream.close();
	}
	else {
		printf("Failed to open fragment shader %s. Path may be bad.\n", shader_file_path.c_str());
		getchar();
		return false;
	}
	char const * FragmentSourcePointer = fragmentShaderCode.c_str();
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(_fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(_fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		_fragmentShaderID = 0;
		glDeleteShader(_fragmentShaderID);
		return false;
	}
	return true;
}

bool Shader::LinkShader()
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Link the program
	_shaderProgramID = glCreateProgram();
	glAttachShader(_shaderProgramID, _vertexShaderID);
	glAttachShader(_shaderProgramID, _fragmentShaderID);
	glLinkProgram(_shaderProgramID);
	if(_name == "")
		_name = "ShaderProgram" + _shaderProgramID;
	// Check the program
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_shaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(_shaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		glDeleteProgram(_shaderProgramID);
		_shaderProgramID = 0;
		return false;
	}
	glDetachShader(_shaderProgramID, _vertexShaderID);
	glDetachShader(_shaderProgramID, _fragmentShaderID);

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	return true;
}

void Shader::Use()
{
	if(_shaderProgramID)
		glUseProgram(_shaderProgramID);
}

GLuint Shader::Uniform(std::string uniformName)
{
	std::map<std::string, GLuint>::iterator it;

	it = uniforms.find(uniformName);
	if (it != uniforms.end())
		return it->second;
	else {
		uniforms[uniformName] = glGetUniformLocation(_shaderProgramID, uniformName.c_str());
		return uniforms[uniformName];
	}
}

Shader::Shader()
{
	_name = "";
}

Shader::Shader(std::string name)
{
	_name = name;
}

Shader::Shader(std::string name, std::string vertFilename, std::string fragFilename)
{
	_name = name;
	LoadVertexShader(vertFilename);
	LoadFragmentShader(fragFilename);
	LinkShader();
}