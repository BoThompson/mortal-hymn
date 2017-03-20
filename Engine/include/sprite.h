/**
 * @file include\sprite.h.
 *
 * Declares the sprite class.
 */
#pragma once

/**
 * A frame data.
 *
 * @author Bo Thompson
 * @date 3/18/2017
 */
struct FrameData
{
	int index;  /**< The frame index */
	int duration;   /**< The duration */
};

/**
 * An animation data.
 *
 * @author Bo Thompson
 * @date 3/18/2017
 */
struct AnimationData
{
	std::vector<FrameData> frames;  /**< The data for each frame */
	int flags;  /**< The animation flags */
};

/**
 * A sprite.
 *
 * @author Bo Thompson
 * @date 3/18/2017
 */
class Sprite
{
	GLuint m_textureID; /**< OpenGL ID for the texture */
	std::string m_name; /**< The sprite name */
	glm::vec2 m_frameSize;  /**< Size of the frame */
	glm::vec2 m_framesPerTexture;   /**< The frames per texture */
	std::map<std::string, AnimationData> m_animations;  /**< The animations */

	/**
	 * Default constructor.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 */
	Sprite();
public:

	/**
	 * Constructor.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @param name			   The name.
	 * @param textureID		   Identifier for the texture.
	 * @param frameSize		   Size of the frame.
	 * @param framesperTexture The framesper texture.
	 */
	Sprite(std::string name, GLuint textureID, glm::vec2 frameSize, glm::vec2 framesperTexture);

	/**
	 * Gets a frame.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @param animation The animation.
	 * @param step	    Amount to increment by.
	 *
	 * @return The frame.
	 */
	glm::vec4 GetFrame(std::string animation, int step);

	/**
	 * Gets a frame.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @param index Zero-based index of the.
	 *
	 * @return The frame.
	 */
	glm::vec4 GetFrame(int index);

	/**
	 * Adds an animation to 'animation'.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @param name	    The name.
	 * @param animation The animation.
	 */
	void AddAnimation(std::string name, AnimationData animation);

	/**
	 * Gets the name.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @return A std::string.
	 */
	std::string Name();

	/**
	 * Gets the texture ID.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @return A GLuint.
	 */
	GLuint Texture();

	/**
	 * Gets animation length.
	 *
	 * @author Bo Thompson
	 * @date 3/18/2017
	 *
	 * @param animation The animation.
	 *
	 * @return The animation length.
	 */
	int GetAnimationLength(std::string animation);
};
