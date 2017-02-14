
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <vector>
#include "scripts.h"
#include "actor.h"
#include "entity.h"


extern GLuint vbo;

glm::mat4 Entity::ModelMatrix()
{
	return _modelMatrix;
}

void Entity::SetModelMatrix(glm::mat4 matrix)
{
	_modelMatrix = matrix;
}

void Entity::Translate(glm::vec3 v)
{
	glm::translate(_modelMatrix, v);
}

const std::vector<glm::vec3> &Entity::Vertices()
{
	return _vertices;
}
void Entity::SetVertices(std::vector<glm::vec3> verts)
{
	_vertices = verts;
}

void Entity::Draw()
{
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