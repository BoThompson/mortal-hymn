#include "game.h"


void Texture::Load(std::string filename, GLuint targetType)
{
	m_targetType = targetType;
	
	if(!m_image.loadFromFile(filename))
	{
		printf("Error: Texture %s did not load correctly.", filename.c_str());
		return;
	}
	m_filename = filename;
	glGenTextures(1, &m_texID);
	Buffer();
}

void Texture::Buffer(GLuint unit)
{
	glActiveTexture(unit);
	glBindTexture(m_targetType, m_texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image.getSize().x, m_image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(m_targetType, 0);
	glActiveTexture(0);
}

GLuint Texture::ID()
{
	return m_texID;
}

void Texture::Bind(GLuint unit)
{
	m_currentUnit = unit;
	glActiveTexture(unit);
	glBindTexture(m_targetType, m_texID);
}

void Texture::Unbind()
{
	glActiveTexture(m_currentUnit);
	glBindTexture(m_targetType, 0);
}