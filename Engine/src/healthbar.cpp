#include "game.h"


HealthBar::HealthBar(glm::vec2 position, glm::vec2 size, int current, int max, std::array<BarComponent, 4> barComponents)
{
	Set(position, size, current, max, barComponents);
}

void HealthBar::Set(glm::vec2 position, glm::vec2 size, int current, int max, std::array<BarComponent, 4> barComponents)
{
	m_position = position;
	m_size = size;
	m_currentHealth = current;
	m_maxHealth = max;
	m_barComponents = barComponents;
	Resize();
}

void HealthBar::Set(glm::vec2 position, glm::vec2 size, int current, int max)
{
	m_position = position;
	m_size = size;
	m_currentHealth = current;
	m_maxHealth = max;
	Resize();
}


void HealthBar::Resize()
{
	float deltaX = m_size.x / 20;
	//Clear the vertices and UVs
	m_vertices.clear();
	m_uvs.clear();
	//Draw the outside
	// Draw the bar
	// If they only have 5 max health, draw a single segment
	if (m_maxHealth <= 5)
	{

	}
	else
	{
		// Draw the beginning
		for (int i = 0; i < m_maxHealth; i += 5)
		{
			//LL triangle
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * i, m_position.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x, m_barComponents[HEALTHBAR_MID].y + m_barComponents[HEALTHBAR_MID].h));
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * i, m_position.y - m_size.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x, m_barComponents[HEALTHBAR_MID].y));
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * (i + 1), m_position.y - m_size.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x + m_barComponents[HEALTHBAR_MID].w, m_barComponents[HEALTHBAR_MID].y));
			//UR triangle
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * i, m_position.y - m_size.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x, m_barComponents[HEALTHBAR_MID].y));
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * (i + 1), m_position.y - m_size.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x + m_barComponents[HEALTHBAR_MID].w, m_barComponents[HEALTHBAR_MID].y));
			m_vertices.push_back(glm::vec2(m_position.x + deltaX * (i + 1), m_position.y));
			m_uvs.push_back(glm::vec2(m_barComponents[HEALTHBAR_MID].x + m_barComponents[HEALTHBAR_MID].w, m_barComponents[HEALTHBAR_MID].y + m_barComponents[HEALTHBAR_MID].h));
		}
	}
	for (int i = 0; i < m_currentHealth; i += 5)
	{

	}
	//Draw the end
	
	//Draw the damage segments
	for (std::vector<DamageSegment>::iterator it = m_damageSegments.begin(); it != m_damageSegments.end(); it++)
	{

	}
}

void HealthBar::Damage(int amount, bool generateSegment)
{

}