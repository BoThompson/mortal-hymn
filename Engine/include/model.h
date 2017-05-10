#pragma once


class Model
{
	std::vector<Mesh> m_meshes;
	std::vector<Texture*> m_textures;
	std::vector<Animation> m_animations;
public:
	void Load(const aiScene *scene);
	void Draw(Shader &shader, glm::mat4 modelMatrix);
	void LoadMesh(const aiMesh *pMesh, glm::mat4 transform);
	void ProcessNode(const aiNode *node, glm::mat4 compositeTransform);
};