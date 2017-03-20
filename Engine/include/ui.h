/**
 * @file include\ui.h.
 *
 * Declares the user interface class.
 */
#pragma once

/**
 * A user interface.
 *
 * @author Bo Thompson
 * @date 3/18/2017
 */
class UI
{
	Sprite *m_sprite;   /**< The sprite */
	std::string m_name; /**< The name */
	std::string m_currentAnimation; /**< The current animation */
	int m_step; /**< Amount to increment by */
	int m_timeRemaining;	/**< The time remaining */
	glm::vec2 m_position;   /**< The position */
	std::vector<glm::vec3> m_vertices;	/**< The vertices */
	std::vector<glm::vec3> m_uvs; /**< The uvs */
	glm::vec2 position; /**< Position in pixels from UL */
	glm::vec2 size; /**< Size in pixels */
public:

	/**
	 * Default constructor.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 */
	UI();

	/**
	 * Updates this object.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 */
	void Update();

	/**
	 * Draws this object.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 */
	void Draw();
};