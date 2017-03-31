#pragma once


struct DamageSegment
{
	int timeRemaining;
	glm::vec2 position;
	glm::vec4 color;
	std::vector<glm::vec2> vertices;
};

struct BarComponent
{
	float x;
	float y;
	float w;
	float h;
};

enum HealthBarComponents
{
	HEALTHBAR_MID,
	HEALTHBAR_END,
	HEALTHBAR_START,
	HEALTHBAR_INNER

};
class HealthBar : UI
{
	int m_currentHealth;
	int m_maxHealth;
	glm::vec2 m_position;
	glm::vec2 m_size;
	std::vector<DamageSegment> m_damageSegments;
	std::array<BarComponent, 4> m_barComponents;
public:
	HealthBar(glm::vec2 position, glm::vec2 size, int current, int max, std::array<BarComponent, 4> barComponents);
	void Set(glm::vec2 position, glm::vec2 size, int current, int max);
	void Set(glm::vec2 position, glm::vec2 size, int current, int max, std::array<BarComponent, 4> barComponents);
	void Resize();
	void Damage(int amount, bool generateSegment);
	void Draw();
	void Update();
};