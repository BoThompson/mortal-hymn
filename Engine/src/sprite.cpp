
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include "sprite.h"
/********************************************************************************/
static std::map<std::string, Sprite> SpriteList;


/********************************************************************************/
Sprite::Sprite(std::string name, GLuint textureID, glm::vec2 frameSize, glm::vec2 framesPerTexture)
{
	m_name = name;
	m_textureID = textureID;
	m_frameSize = frameSize;
	m_framesPerTexture = framesPerTexture;
}

glm::vec4 Sprite::GetFrame(std::string animation, int step)
{
	if(m_animations.find(animation) != m_animations.end())
		return GetFrame(m_animations[animation].frames[step].index);
	else
		return glm::vec4(0, 0, 0, 0);
}

glm::vec4 Sprite::GetFrame(int index)
{
	glm::vec2 frameCoords;
	glm::vec4 frameRect;
	frameCoords.y = (int)(index / m_framesPerTexture.x);
	frameCoords.x = index % (int)m_framesPerTexture.y;
	frameRect.x = frameCoords.x * m_frameSize.x;
	frameRect.y = frameCoords.y * m_frameSize.y;
	frameRect.z = frameCoords.x * (m_frameSize.x + 1);
	frameRect.w = frameCoords.y * (m_frameSize.y + 1);
	return frameRect;
}

void Sprite::AddAnimation(std::string name, AnimationData animation)
{
	m_animations[name] = animation;
}

std::string Sprite::Name()
{
	return m_name;
}

GLuint Sprite::Texture()
{
	return m_textureID;
}

int Sprite::GetAnimationLength(std::string animation)
{
	std::map<std::string,AnimationData>::iterator anim = m_animations.find(animation);
	if (anim != m_animations.end())
		return anim->second.frames.size();
	else
		return 0;
}