#pragma once

/**
 * An entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/10/2017
 */
class Entity
{
	std::vector<glm::vec3> _vertices;
	glm::mat4 _modelMatrix;
public:
	const std::vector<glm::vec3> &Vertices();
	void SetVertices(std::vector<glm::vec3> verts);
	glm::mat4 ModelMatrix();
	void SetModelMatrix(glm::mat4 matrix);
	void Translate(glm::vec3 v);
	void Draw();
};