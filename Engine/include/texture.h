#pragma once

class Texture
{
	GLuint m_texID;
	GLuint m_currentUnit;
	GLuint m_targetType;
	std::string m_filename;
	sf::Image m_image;
public:

	/**************************************************************************************************/
	/**
	 * @fn	void Texture::Load(std::string filename, GLuint targetType = GL_TEXTURE_2D);
	 *
	 * @brief	Loads the given file.
	 *
	 * @author	Bo Thompson
	 * @date	4/12/2017
	 *
	 * @param	filename  	Filename of the file.
	 * @param	targetType	(Optional) Type of the target.
	 **************************************************************************************************/
	void Load(std::string filename, GLuint targetType = GL_TEXTURE_2D);
	/**************************************************************************************************/
	/**
	 * @fn	void Texture::Bind(GLuint unit = 0);
	 *
	 * @brief	Binds this texture
	 *
	 * @author	Bo Thompson
	 * @date	4/12/2017
	 *
	 * @param	unit	(Optional) The unit.
	 **************************************************************************************************/
	void Bind(GLuint unit = 0);

	/**************************************************************************************************/
	/**
	 * @fn	void Texture::Unbind()
	 *
	 * @brief	Unbinds this texture.
	 *
	 * @author	Bo Thompson
	 * @date	4/12/2017
	 **************************************************************************************************/
	void Unbind();

	/**************************************************************************************************/
	/**
	 * @fn	void Texture::Buffer(GLuint unit = 0);
	 *
	 * @brief	Buffers the texture's image
	 *
	 * @author	Bo Thompson
	 * @date	4/13/2017
	 *
	 * @param	unit	(Optional) The unit.
	 **************************************************************************************************/
	void Buffer(GLuint unit = 0);

	/**************************************************************************************************/
	/**
	 * @fn	GLuint Texture::ID();
	 *
	 * @brief	Gets the OpenGL Texture ID.
	 *
	 * @author	Bo Thompson
	 * @date	4/13/2017
	 *
	 * @return	A GLuint.
	 **************************************************************************************************/
	GLuint ID();
};