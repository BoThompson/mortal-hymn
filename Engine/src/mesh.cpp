#include "game.h"


void Mesh::Initialize(const aiMesh *mesh)
{
	glm::vec3 v;
	glm::vec2 uv;

	for (int i = 0; i < 4; i++)
		m_vbo[i] = NULL;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(4, &m_vbo[0]);

	m_tris = mesh->mNumFaces;
	if(mesh->HasPositions())
	{
		m_vertices.resize(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_vertices[i].x = mesh->mVertices[i].x;
			m_vertices[i].y = mesh->mVertices[i].y;
			m_vertices[i].z = mesh->mVertices[i].z;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), &m_vertices[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if (mesh->HasTextureCoords(0))
	{
		m_uvs.resize(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_uvs[i].s = mesh->mTextureCoords[0][i].x;
			m_uvs[i].t = mesh->mTextureCoords[0][i].y;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[UV_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), &m_uvs[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1); 
	}

	if (mesh->HasNormals())
	{
		m_normals.resize(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_normals[i].x = mesh->mNormals[i].x;
			m_normals[i].y = mesh->mNormals[i].y;
			m_normals[i].z = mesh->mNormals[i].z;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), &m_normals[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	if (mesh->HasBones())
	{
		std::vector<BoneData> boneDatas;
		std::vector<int> boneCount;
		for (unsigned int i = 0; i < mesh->mNumBones; i++)
		{
			BoneData b;
			aiBone *pBone = mesh->mBones[i];
			b.name = pBone->mName.C_Str();
			for (unsigned int x = 0; x < pBone->mNumWeights; x++)
			{
				Weight w;
				w.vertexID = pBone->mWeights[x].mVertexId;
				w.weight = pBone->mWeights[x].mWeight;
				b.weights.push_back(w);
			}
			for(int x = 0;x < 4;x++)
				for(int y = 0;y < 4;y++)
					b.offset[x][y] = pBone->mOffsetMatrix[y][x];
			boneDatas.push_back(b);
		}
		m_bones.resize(m_vertices.size());
		boneCount.resize(m_vertices.size());
 		for (int j = 0; j < boneDatas.size(); j++)
		{
			m_boneTransforms.push_back(boneDatas[j].offset);
			for (int i = 0; i < m_vertices.size(); i++)
			{
				for (int k = 0; k < boneDatas[j].weights.size(); k++)
				{
					if (i == boneDatas[j].weights[k].vertexID)
					{

						m_bones[i].indices[boneCount[i]] = j;
						m_bones[i].weights[boneCount[i]] = boneDatas[j].weights[k].weight;
						boneCount[i]++;
					}
				}
			}
		}
		glGenBuffers(1, &m_vbo[BONE_INDEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[BONE_INDEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * m_bones.size() * sizeof(GLint), &m_bones[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, m_bones.size(), GL_INT, GL_FALSE, sizeof(VertexBone), NULL);
		glEnableVertexAttribArray(3);

		glGenBuffers(1, &m_vbo[BONE_WEIGHT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[BONE_WEIGHT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * m_bones.size() * sizeof(GLint), &m_bones[0], GL_STATIC_DRAW);
		glVertexAttribPointer(4, m_bones.size(), GL_FLOAT, GL_FALSE, sizeof(VertexBone), (void*)offsetof(VertexBone, weights));
		glEnableVertexAttribArray(4);

	}

	if (mesh->HasFaces())
	{
		m_indices.resize(mesh->mNumFaces * 3);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			m_indices[i * 3] = mesh->mFaces[i].mIndices[0];
			m_indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			m_indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		glGenBuffers(1, &m_vbo[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);
	}
	glBindVertexArray(0);	
	glDeleteBuffers(4, &m_vbo[0]);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(0, &m_vao);
}
void Mesh::Draw(Shader &shader, glm::mat4 modelMatrix)
{
	glm::mat4 M = modelMatrix * m_transformMatrix;
	glm::mat4  MVP = game->GetProjectionMatrix() * game->GetViewMatrix() * M;// *modelMatrix;
	glm::vec4 test = glm::vec4(0, 0, 1, 1);
	test = MVP * test;
	glUniformMatrix4fv(shader.Uniform("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(shader.Uniform("M"), 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(shader.Uniform("V"), 1, GL_FALSE, &(game->GetViewMatrix())[0][0]);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_tris * 3, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	
}

void Mesh::SetTransformMatrix(glm::mat4 transform)
{
	m_transformMatrix = transform;
}