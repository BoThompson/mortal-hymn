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
	std::vector<glm::vec2> _uvs;
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	sf::Texture *_texture;
public:
	Entity_T();
	const std::vector<glm::vec3> &Vertices();
	const std::vector<glm::vec2> &UVs();
	void SetVertices(std::vector<glm::vec3> verts);
	void SetUVs(std::vector<glm::vec2> UVs);
	void SetTexture(sf::Texture *texture);
	void Translate(glm::vec3 v);
	void Draw(class Shader &shader, glm::mat4 MVP);
	glm::vec3 Position();
	void SetPosition(glm::vec3 pos);
	glm::vec3 Rotation();
	void SetRotation(glm::vec3 rot);
	glm::vec3 Scale();
	void SetScale(glm::vec3 scale);
};