#pragma once

#define VERTEX_BUFFER		0
#define UV_BUFFER			1
#define NORMAL_BUFFER		2
#define INDEX_BUFFER		3
#define BONE_INDEX_BUFFER	4
#define BONE_WEIGHT_BUFFER  5


#define BONES_PER_VERTEX 4

struct Weight
{
	GLuint vertexID;
	float weight;
};

struct BoneData
{
	std::string name;
	std::vector<Weight> weights;
	glm::mat4 offset;
};


struct VertexBone
{
	int indices[BONES_PER_VERTEX];
	float weights[BONES_PER_VERTEX];
};

class Mesh
{
	GLuint m_vao;
	GLuint m_tris;
	glm::mat4 m_transformMatrix;
	std::array<GLuint, 4> m_vbo;
	std::vector<glm::mat4> m_boneTransforms;
	std::vector<VertexBone> m_bones;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
	std::vector<GLuint> m_indices;
public:
	~Mesh();
	void Initialize(const aiMesh *mesh);
	void Draw(Shader &shader, glm::mat4 modelMatrix);
	void SetTransformMatrix(glm::mat4 transform);
};