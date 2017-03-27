/**
 * @file src\entity.cpp
 *
 * Implements the entity class.
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>
#include <SFML\Graphics.hpp>
#include <vector>
#include "game.h"


extern GLuint vbo;
extern GLuint UVbo;

extern Game *game;

Entity::Entity()
{
	m_scale = glm::vec3(1);
	m_position = glm::vec3(0);
	m_rotation = glm::vec3(0);
	m_texture = NULL;
}

void Entity::SetTexture(sf::Texture *texture)
{
	m_texture = texture;
}



const std::vector<glm::vec3> &Entity::Vertices()
{
	return m_vertices;
}


void Entity::SetVertices(std::vector<glm::vec3> verts)
{
	m_vertices = verts;
}


const std::vector<glm::vec2> &Entity::UVs()
{
	return m_uvs;
}


void Entity::SetUVs(std::vector<glm::vec2> UVs)
{
	m_uvs = UVs;
}


void Entity::Draw(Shader &shader, glm::mat4 MVP)
{
	glUseProgram(shader.GetProgramID());
	glm::mat4 modelMatrix = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z)
		* glm::translate(glm::mat4(1), m_position)
		* glm::scale(glm::mat4(1), m_scale);
	MVP = MVP * modelMatrix;
	glUniformMatrix4fv(shader.Uniform("MVP"), 1, GL_FALSE, &MVP[0][0]);
	if (m_texture != NULL)
		sf::Texture::bind(m_texture);
		
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, game->Vbo());
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, game->UVbo());
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (m_texture != NULL)
		sf::Texture::bind(NULL);
}


glm::vec3 Entity::Position()
{
	return m_position;
}


void Entity::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}


glm::vec3 Entity::Rotation()
{
	return m_rotation;
}


void Entity::SetRotation(glm::vec3 rot)
{
	m_rotation = rot;
}


glm::vec3 Entity::Scale()
{
	return m_scale;
}


void Entity::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}


void Entity::Translate(glm::vec3 vector)
{
	m_position = m_position + vector;
}

void Entity::Update()
{
	if (m_actor)
		m_actor->Update(game->Delta().asMilliseconds());
}

void Entity::Initialize()
{
	memset(this, 0, sizeof(Entity));
	m_inUse = true;
}

bool Entity::InUse()
{
	return m_inUse;
}