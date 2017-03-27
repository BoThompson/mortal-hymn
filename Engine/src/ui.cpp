#include <GL\glew.h>
#include <glm\glm.hpp>
#include <SFML\Graphics.hpp>
#include "game.h"


extern GLuint vbo;
extern GLuint UVbo;
extern Game *game;
void UI::Update()
{
	glm::vec2 gl_position;
	glm::vec2 gl_size;

	if (m_timeRemaining <= 0)
		m_step++;

	if (m_step < m_sprite->GetAnimationLength(m_currentAnimation))
	{
		gl_position.x = (position.x / game->Screen().x) * 2 - 1;
		gl_position.y = -((position.y / game->Screen().y) * 2 - 1);
		gl_size.x = (size.x / game->Screen().x) * 2 - 1;
		gl_size.y = (size.y / game->Screen().y) * 2 - 1;

		glm::vec4 rect = m_sprite->GetFrame(m_currentAnimation, m_step);
		//Texture coordinates
		m_uvs.clear();
		m_uvs[0].x = rect.x;
		m_uvs[0].y = rect.y;
		m_uvs[1].x = rect.x + rect.z;
		m_uvs[1].y = rect.y;
		m_uvs[2].x = rect.x;
		m_uvs[2].y = rect.y + rect.w;
		m_uvs[3].x = rect.x;
		m_uvs[3].y = rect.y + rect.w;
		m_uvs[4].x = rect.x + rect.z;
		m_uvs[4].y = rect.y;
		m_uvs[5].x = rect.x + rect.z;
		m_uvs[5].y = rect.y + rect.w;
		//Vertex coordinates
		m_vertices.clear();
		m_vertices[0].x = gl_position.x;
		m_vertices[0].y = gl_position.y;
		m_vertices[1].x = gl_position.x + gl_size.x;
		m_vertices[1].y = gl_position.y;
		m_vertices[2].x = gl_position.x;
		m_vertices[2].y = gl_position.y + gl_size.y;
		m_vertices[3].x = gl_position.x;
		m_vertices[3].y = gl_position.y + gl_size.y;
		m_vertices[4].x = gl_position.x + gl_size.x;
		m_vertices[4].y = gl_position.y;
		m_vertices[5].x = gl_position.x + gl_size.x;
		m_vertices[5].y = gl_position.y + gl_size.y;
	}
}

void UI::Draw()
{
	game->UseShader("HUD");
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, game->Vbo());
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, game->UVbo());
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}
