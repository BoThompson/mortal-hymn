#include "game.h"


void Model::ProcessNode(const aiNode *node, glm::mat4 compositeTransform)
{
	glm::mat4 transform;
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			transform[i][j] = node->mTransformation[j][i];
	aiVector3D scaling, position;
	aiQuaternion rotation;
	node->mTransformation.Decompose(scaling, rotation, position);
	transform = compositeTransform * transform;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], transform);
	}
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		m_meshes[node->mMeshes[i]].SetTransformMatrix(transform);	
}

void Model::LoadMesh(const aiMesh *pMesh, glm::mat4 transform)
{
}

void Model::Load(const aiScene *scene)
{
	Mesh mesh;
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		Mesh mesh;
		mesh.Initialize(scene->mMeshes[i]);
		m_meshes.push_back(mesh);
	}
	ProcessNode(scene->mRootNode, glm::mat4(1));
	
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

void Model::Draw(Shader &shader, glm::mat4 modelMatrix)
{
	int texChannel = 0;
	for (std::vector<Texture*>::iterator i = m_textures.begin(); i != m_textures.end(); i++)
	{
		(*i)->Bind(texChannel++);
	}
	for (std::vector<Mesh>::iterator i = m_meshes.begin(); i != m_meshes.end(); i++)
	{
		i->Draw(shader, modelMatrix);
	}
}