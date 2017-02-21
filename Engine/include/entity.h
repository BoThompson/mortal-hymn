#pragma once

/**
 * An entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/10/2017
 */
class Entity_T
{
	std::vector<glm::vec3> _vertices;
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
public:
	Entity_T();
	const std::vector<glm::vec3> &Vertices();
	void SetVertices(std::vector<glm::vec3> verts);
	void Translate(glm::vec3 v);
	void Draw(class Shader &shader, glm::mat4 MVP);
	glm::vec3 Position();
	void SetPosition(glm::vec3 pos);
	glm::vec3 Rotation();
	void SetRotation(glm::vec3 rot);
	glm::vec3 Scale();
	void SetScale(glm::vec3 scale);
};