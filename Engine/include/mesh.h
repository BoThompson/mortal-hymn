#pragma once

#define VERTEX_BUFFER		0
#define UV_BUFFER			1
#define NORMAL_BUFFER		2
#define INDEX_BUFFER		3


struct Weight
{
	GLuint vertexID;
	float weight;
};

struct Bone
{
	std::string name;
	std::vector<Weight> weights;
	glm::mat4 offset;
};

class Mesh
{
	GLuint m_vao;
	GLuint m_tris;
	std::array<GLuint, 4> m_vbo;
	std::vector<Bone> m_bones;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
	std::vector<GLuint> m_indices;
public:
	~Mesh();
	void Initialize(aiMesh *mesh);
	void Draw();
};