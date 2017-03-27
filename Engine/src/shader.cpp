#include <GL\glew.h>
#include <SFML\OpenGL.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "shader.h"

const std::string shader_file_path = "shaders";

void Shader::SetName(std::string name)
{
	m_name = name;
}


bool Shader::LoadVertexShader(std::string filename)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	std::ifstream VertexShaderStream(shader_file_path + "\\" + filename, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			m_vertexShaderCode += Line + "\n";
		VertexShaderStream.close();
	}
	else {
		printf("Failed to open %s. Path may be bad.\n", shader_file_path.c_str());
		getchar();
		return false;
	}
	char const * VertexSourcePointer = m_vertexShaderCode.c_str();
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(m_vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(m_vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		glDeleteShader(m_vertexShaderID);
		m_vertexShaderID = 0;
		return false;
	}
	return true;
}

bool Shader::LoadFragmentShader(std::string filename)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	m_fragmentShaderCode = "";
	std::ifstream FragmentShaderStream(shader_file_path + "\\" + filename, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			m_fragmentShaderCode += Line + "\n";
		FragmentShaderStream.close();
	}
	else {
		printf("Failed to open fragment shader %s. Path may be bad.\n", shader_file_path.c_str());
		getchar();
		return false;
	}
	char const * FragmentSourcePointer = m_fragmentShaderCode.c_str();
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(m_fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(m_fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		m_fragmentShaderID = 0;
		glDeleteShader(m_fragmentShaderID);
		return false;
	}
	return true;
}

bool Shader::LinkShader()
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Link the program
	m_shaderProgramID = glCreateProgram();
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);
	glLinkProgram(m_shaderProgramID);
	if(m_name == "")
		m_name = "ShaderProgram" + m_shaderProgramID;
	// Check the program
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_shaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (!Result && InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_shaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		glDeleteProgram(m_shaderProgramID);
		m_shaderProgramID = 0;
		return false;
	}
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	return true;
}

void Shader::Use()
{
	if(m_shaderProgramID)
		glUseProgram(m_shaderProgramID);
}

GLuint Shader::Uniform(std::string uniformName)
{
	std::map<std::string, GLuint>::iterator it;

	it = m_uniforms.find(uniformName);
	if (it != m_uniforms.end())
		return it->second;
	else {
		m_uniforms[uniformName] = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
		return m_uniforms[uniformName];
	}
}

Shader::Shader()
{
	m_valid = false;
	m_name = "";
}

Shader::Shader(std::string name)
{
	m_valid = false;
	m_name = name;
}

Shader::Shader(std::string name, std::string vertFilename, std::string fragFilename)
{
	m_name = name;
	m_valid = false;
	LoadVertexShader(vertFilename);
	LoadFragmentShader(fragFilename);
	LinkShader();
	//Check to see if it loaded correctly
	m_valid = true;
}

Shader::Shader(const Shader &s)
{
	m_name = s.GetName();
	m_shaderProgramID = s.GetProgramID();
	m_vertexShaderID = s.GetVertexID();
	m_fragmentShaderID = s.GetFragmentID();
	m_uniforms = s.GetUniforms();
	m_vertexShaderCode = s.GetVertexShaderCode();
	m_fragmentShaderCode = s.GetFragmentShaderCode();
	m_valid = s.IsValid();
}


bool Shader::IsValid() const
{
	return m_valid;
}
std::string Shader::GetName() const
{
	return m_name;
}

std::string Shader::GetVertexShaderCode() const
{
	return m_vertexShaderCode;
}
std::string Shader::GetFragmentShaderCode() const
{
	return m_fragmentShaderCode;
}
std::map<std::string, GLuint> Shader::GetUniforms() const
{
	return m_uniforms;
}
GLuint Shader::GetProgramID() const
{
	return m_shaderProgramID;
}
GLuint Shader::GetVertexID() const
{
	return m_vertexShaderID;
}
GLuint Shader::GetFragmentID() const
{
	return m_fragmentShaderID;
}