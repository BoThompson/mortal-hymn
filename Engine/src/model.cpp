#include "game.h"

void Model::Load(const aiScene *scene)
{
	Mesh mesh;

	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		mesh.Initialize(scene->mMeshes[i]);
		m_meshes.push_back(mesh);
		
	}

	aiString path;
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		const aiMaterial *material = scene->mMaterials[i];
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			std::string filepath = "textures\\";
			filepath += path.data;
			m_textures.push_back(game->LoadTexture(filepath));
		}
	}
}

void Model::Draw()
{
	for (std::vector<Texture*>::iterator i = m_textures.begin(); i != m_textures.end(); i++)
	{
		(*i)->Bind();
	}

	for (std::vector<Mesh>::iterator i = m_meshes.begin(); i != m_meshes.end(); i++)
	{
		i->Draw();
	}
}