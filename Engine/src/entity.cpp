
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>
#include <vector>
#include "shader.h"
#include "scripts.h"
#include "actor.h"
#include "entity.h"


extern GLuint vbo;

Entity_T::Entity_T()
{
	_scale = glm::vec3(1);
	_position = glm::vec3(0);
	_rotation = glm::vec3(0);
}

const std::vector<glm::vec3> &Entity_T::Vertices()
{
	return _vertices;
}
void Entity_T::SetVertices(std::vector<glm::vec3> verts)
{
	_vertices = verts;
}

void Entity_T::Draw(Shader &shader, glm::mat4 MVP)
{
	glm::mat4 modelMatrix = glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z)
		* glm::translate(glm::mat4(1), _position)
		* glm::scale(glm::mat4(1), _scale);
	MVP = MVP * modelMatrix;
	glUniformMatrix4fv(shader.Uniform("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(9 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

glm::vec3 Entity_T::Position()
{
	return _position;
}

void Entity_T::SetPosition(glm::vec3 pos)
{
	_position = pos;
}

glm::vec3 Entity_T::Rotation()
{
	return _rotation;
}

void Entity_T::SetRotation(glm::vec3 rot)
{
	_rotation = rot;
}

glm::vec3 Entity_T::Scale()
{
	return _scale;
}

void Entity_T::SetScale(glm::vec3 scale)
{
	_scale = scale;
}

void Entity_T::Translate(glm::vec3 v)
{
	_position = _position + v;
}