/**************************************************************************************************/
/**
 * @file	include\shader.h.
 *
 * @brief	Declares the shader class.
 **************************************************************************************************/
#pragma once

#include <map>

/**************************************************************************************************/
/**
 * @class	Shader
 *
 * @brief	A shader.
 *
 * @author	Aimle
 * @date	3/25/2017
 **************************************************************************************************/
class Shader
{
	bool m_valid;
	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	std::string m_name;
	std::string m_vertexShaderCode;
	std::string m_fragmentShaderCode;
	std::map<std::string, GLuint> m_uniforms;
public:

	/**************************************************************************************************/
	/**
	 * @fn	bool Shader::IsValid();
	 *
	 * @brief	Query if this object is valid.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	True if valid, false if not.
	 **************************************************************************************************/
	bool IsValid() const;
	/**************************************************************************************************/
	/**
	 * @fn	Shader::Shader();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	Shader();

	/**************************************************************************************************/
	/**
	 * @fn	Shader::Shader(const Shader &s);
	 *
	 * @brief	Copy constructor.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	s	The Shader to process.
	 **************************************************************************************************/
	Shader(const Shader &s);

	/**************************************************************************************************/
	/**
	 * @fn	Shader::Shader(std::string name);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name	The name.
	 **************************************************************************************************/
	Shader(std::string name);

	/**************************************************************************************************/
	/**
	 * @fn	Shader::Shader(std::string name, std::string vertFilename, std::string fragFilename);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name			The name.
	 * @param	vertFilename	Filename of the vertical file.
	 * @param	fragFilename	Filename of the fragment file.
	 **************************************************************************************************/
	Shader(std::string name, std::string vertFilename, std::string fragFilename);

	/**************************************************************************************************/
	/**
	 * @fn	bool Shader::LoadVertexShader(std::string filename);
	 *
	 * @brief	Loads vertex shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/
	bool LoadVertexShader(std::string filename);

	/**************************************************************************************************/
	/**
	 * @fn	bool Shader::LoadFragmentShader(std::string filename);
	 *
	 * @brief	Loads fragment shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/
	bool LoadFragmentShader(std::string filename);

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Shader::Uniform(std::string uniformName);
	 *
	 * @brief	Uniforms the given uniform name.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	uniformName	Name of the uniform.
	 *
	 * @return	A GLuint.
	 **************************************************************************************************/
	GLuint Uniform(std::string uniformName);

	/**************************************************************************************************/
	/**
	 * @fn	bool Shader::LinkShader();
	 *
	 * @brief	Links the shader.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/
	bool LinkShader();

	/**************************************************************************************************/
	/**
	 * @fn	void Shader::Use();
	 *
	 * @brief	Uses this object.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 **************************************************************************************************/
	void Use();

	/**************************************************************************************************/
	/**
	 * @fn	void Shader::SetName(std::string name);
	 *
	 * @brief	Sets a name.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @param	name	The name.
	 **************************************************************************************************/
	void SetName(std::string name);

	/**************************************************************************************************/
	/**
	 * @fn	std::string Shader::GetName() const;
	 *
	 * @brief	Gets the name.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The name.
	 **************************************************************************************************/
	std::string GetName() const;

	/**************************************************************************************************/
	/**
	 * @fn	std::string Shader::GetVertexShaderCode() const;
	 *
	 * @brief	Gets vertex shader code.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The vertex shader code.
	 **************************************************************************************************/
	std::string GetVertexShaderCode() const;

	/**************************************************************************************************/
	/**
	 * @fn	std::string Shader::GetFragmentShaderCode() const;
	 *
	 * @brief	Gets fragment shader code.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The fragment shader code.
	 **************************************************************************************************/
	std::string GetFragmentShaderCode() const;

	/**************************************************************************************************/
	/**
	 * @fn	std::map<std::string, GLuint> Shader::GetUniforms() const;
	 *
	 * @brief	Gets the uniforms.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The uniforms.
	 **************************************************************************************************/
	std::map<std::string, GLuint> GetUniforms() const;

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Shader::GetProgramID() const;
	 *
	 * @brief	Gets program identifier.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The program identifier.
	 **************************************************************************************************/
	GLuint GetProgramID() const;

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Shader::GetVertexID() const;
	 *
	 * @brief	Gets vertex identifier.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The vertex identifier.
	 **************************************************************************************************/
	GLuint GetVertexID() const;

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Shader::GetFragmentID() const;
	 *
	 * @brief	Gets fragment identifier.
	 *
	 * @author	Aimle
	 * @date	3/25/2017
	 *
	 * @return	The fragment identifier.
	 **************************************************************************************************/
	GLuint GetFragmentID() const;
};