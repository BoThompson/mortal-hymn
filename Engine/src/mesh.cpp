#include "game.h"


void Mesh::Initialize(aiMesh *mesh)
{
	glm::vec3 v;
	glm::vec2 uv;

	for (int i = 0; i < 4; i++)
		m_vbo[i] = NULL;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(m_vao);
	m_tris = mesh->mNumFaces * 3;

	if(mesh->HasPositions())
	{
		m_vertices.resize(mesh->mNumVertices * 3);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_vertices[i].x = mesh->mVertices[i].x;
			m_vertices[i].y = mesh->mVertices[i].y;
			m_vertices[i].z = mesh->mVertices[i].z;
		}
		glGenBuffers(1, &m_vbo[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), &m_vertices[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if (mesh->HasTextureCoords(0))
	{
		m_uvs.resize(mesh->mNumVertices * 2);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_uvs[i].s = mesh->mTextureCoords[0][i].x;
			m_uvs[i].t = mesh->mTextureCoords[0][i].y;
		}
		glGenBuffers(1, &m_vbo[UV_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[UV_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), &m_uvs[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1); 
	}

	if (mesh->HasNormals())
	{
		m_normals.resize(mesh->mNumVertices * 3);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			m_normals[i].x = mesh->mNormals[i].x;
			m_normals[i].y = mesh->mNormals[i].y;
			m_normals[i].z = mesh->mNormals[i].z;
		}
		glGenBuffers(1, &m_vbo[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), &m_normals[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	if (mesh->HasBones())
	{
		for (unsigned int i = 0; i < mesh->mNumBones; i++)
		{
			Bone b;
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
			m_bones.push_back(b);
		}
		
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
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);	
}

Mesh::~Mesh()
{
	for (int i = 0; i < 4; i++)
		if (m_vbo[i])
			glDeleteBuffers(1, &m_vbo[i]);

}
void Mesh::Draw()
{
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	if (m_uvs.size() > 0)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[UV_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0][0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_BUFFER]);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, &m_indices[0]);
	//glDrawArrays(GL_TRIANGLES, 0, m_tris);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}