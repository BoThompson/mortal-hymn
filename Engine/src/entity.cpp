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
#include "shader.h"
#include "scripts.h"
#include "actor.h"
#include "entity.h"


extern GLuint vbo;
extern GLuint UVbo;
/**
 * Default constructor.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 */

Entity_T::Entity_T()
{
	_scale = glm::vec3(1);
	_position = glm::vec3(0);
	_rotation = glm::vec3(0);
	_texture = NULL;
}

void Entity_T::SetTexture(sf::Texture *texture)
{
	_texture = texture;
}

/**
 * Gets the vertices.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @return A reference to a const std::vector&lt;glm::vec3&gt;
 */

const std::vector<glm::vec3> &Entity_T::Vertices()
{
	return _vertices;
}

/**
 * Sets the vertices.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param verts The vertices.
 */

void Entity_T::SetVertices(std::vector<glm::vec3> verts)
{
	_vertices = verts;
}

/**
 * Gets the UVs.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @return A reference to a const std::vector&lt;glm::vec2&gt;
 */

const std::vector<glm::vec2> &Entity_T::UVs()
{
	return _uvs;
}

/**
 * Sets the UVs.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param UVs The vs.
 */

void Entity_T::SetUVs(std::vector<glm::vec2> UVs)
{
	_uvs = UVs;
}

/**
 * Draws the entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param [in,out] shader The shader.
 * @param 		   MVP    The mvp.
 */

void Entity_T::Draw(Shader &shader, glm::mat4 MVP)
{
	glm::mat4 modelMatrix = glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z)
		* glm::translate(glm::mat4(1), _position)
		* glm::scale(glm::mat4(1), _scale);
	MVP = MVP * modelMatrix;
	glUniformMatrix4fv(shader.Uniform("MVP"), 1, GL_FALSE, &MVP[0][0]);
	if (_texture != NULL)
		sf::Texture::bind(_texture);
		
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVbo);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (_texture != NULL)
		sf::Texture::bind(NULL);
}

/**
 * Gets the position of the entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @return A glm::vec3.
 */

glm::vec3 Entity_T::Position()
{
	return _position;
}

/**
 * Sets the entity's position.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param pos The position.
 */

void Entity_T::SetPosition(glm::vec3 pos)
{
	_position = pos;
}

/**
 * Gets the rotation of the entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @return A glm::vec3.
 */

glm::vec3 Entity_T::Rotation()
{
	return _rotation;
}

/**
 * Sets the entity's rotation.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param rot The rot.
 */

void Entity_T::SetRotation(glm::vec3 rot)
{
	_rotation = rot;
}

/**
 * Gets the scale of the entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @return A glm::vec3.
 */

glm::vec3 Entity_T::Scale()
{
	return _scale;
}

/**
 * Sets the entity's scale.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param scale The scale.
 */

void Entity_T::SetScale(glm::vec3 scale)
{
	_scale = scale;
}

/**
 * Translates the entity by a given vector.
 *
 * @author Ulysee "Bo" Thompson
 * @date 3/3/2017
 *
 * @param vector The glm::vec3 to translate by.
 */

void Entity_T::Translate(glm::vec3 vector)
{
	_position = _position + vector;
}