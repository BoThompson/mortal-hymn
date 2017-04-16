#pragma once


class Model
{
	std::vector<Mesh> m_meshes;
	std::vector<Texture*> m_textures;
	std::vector<Animation> m_animations;
public:
	void Load(const aiScene *scene);
	void Draw();
};