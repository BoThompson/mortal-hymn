/**************************************************************************************************/
/**
 * @file	include\entity.h.
 *
 * @brief	Declares the entity class.
 **************************************************************************************************/
#pragma once


/**************************************************************************************************/
/**
 * @class	Entity entity.h include\entity.h
 *
 * @brief	An entity.
 *
 * @author	Bo Thompson
 * @date	3/26/2017
 **************************************************************************************************/
class Entity
{
	bool m_inUse; /**< Is the entity in use */
	std::vector<glm::vec3> m_vertices;   /**< The vertices */
	std::vector<glm::vec2> m_uvs;	/**< The uvs */
	glm::vec3 m_position;	/**< The position */
	glm::vec3 m_rotation;	/**< The rotation */
	glm::vec3 m_scale;   /**< The scale */
	Texture *m_texture;  /**< The texture */
	class Actor *m_actor; /**< The actor object for this entity*/
public:
	Model *m_model;

	/**************************************************************************************************/
	/**
	 * @fn	Entity::Entity();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 **************************************************************************************************/
	Entity();

	/**************************************************************************************************/
	/**
	 * @fn	const std::vector<glm::vec3> Entity::&Vertices();
	 *
	 * @brief	Gets the vertices.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	A reference to a const std::vector&lt;glm::vec3&gt;
	 **************************************************************************************************/
	const std::vector<glm::vec3> &Vertices();

	/**************************************************************************************************/
	/**
	 * @fn	const std::vector<glm::vec2> Entity::&UVs();
	 *
	 * @brief	Gets the vs.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	A reference to a const std::vector&lt;glm::vec2&gt;
	 **************************************************************************************************/
	const std::vector<glm::vec2> &UVs();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetVertices(std::vector<glm::vec3> verts);
	 *
	 * @brief	Sets the vertices.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	verts	The vertices.
	 **************************************************************************************************/
	void SetVertices(std::vector<glm::vec3> verts);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetUVs(std::vector<glm::vec2> UVs);
	 *
	 * @brief	Sets u vs.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	UVs	The vs.
	 **************************************************************************************************/
	void SetUVs(std::vector<glm::vec2> UVs);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetTexture(sf::Texture *texture);
	 *
	 * @brief	Sets a texture.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param [in,out]	texture	If non-null, the texture.
	 **************************************************************************************************/
	void SetTexture(Texture *texture);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::Translate(glm::vec3 v);
	 *
	 * @brief	Translates the given v.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	v	The glm::vec3 to process.
	 **************************************************************************************************/
	void Translate(glm::vec3 vector);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::Draw(class Shader &shader, glm::mat4 MVP);
	 *
	 * @brief	Draws.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param [in,out]	shader	The shader.
	 * @param 		  	MVP   	The mvp.
	 **************************************************************************************************/
	void Draw(class Shader &shader, glm::mat4 MVP);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::DrawModel(class Shader &shader, glm::mat4 MVP);
	 *
	 * @brief	Draw model.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param [in,out]	shader	The shader.
	 * @param 		  	MVP   	The mvp.
	 **************************************************************************************************/
	void DrawModel(class Shader &shader, glm::mat4 MVP);

	/**************************************************************************************************/
	/**
	 * @fn	glm::vec3 Entity::Position();
	 *
	 * @brief	Gets the position.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	A glm::vec3.
	 **************************************************************************************************/
	glm::vec3 Position();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetPosition(glm::vec3 pos);
	 *
	 * @brief	Sets a position.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	pos	The position.
	 **************************************************************************************************/
	void SetPosition(glm::vec3 pos);

	/**************************************************************************************************/
	/**
	 * @fn	glm::vec3 Entity::Rotation();
	 *
	 * @brief	Gets the rotation.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	A glm::vec3.
	 **************************************************************************************************/
	glm::vec3 Rotation();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetRotation(glm::vec3 rot);
	 *
	 * @brief	Sets a rotation.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	rot	The rot.
	 **************************************************************************************************/
	void SetRotation(glm::vec3 rot);

	/**************************************************************************************************/
	/**
	 * @fn	glm::vec3 Entity::Scale();
	 *
	 * @brief	Gets the scale.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @return	A glm::vec3.
	 **************************************************************************************************/
	glm::vec3 Scale();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::SetScale(glm::vec3 scale);
	 *
	 * @brief	Sets a scale.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 *
	 * @param	scale	The scale.
	 **************************************************************************************************/
	void SetScale(glm::vec3 scale);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Bo Thompson
	 * @date	3/26/2017
	 **************************************************************************************************/
	void Update();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::Initialize();
	 *
	 * @brief	Initializes this object.
	 *
	 * @author	Bo Thompson
	 * @date	3/27/2017
	 **************************************************************************************************/
	void Initialize();

	/**************************************************************************************************/
	/**
	 * @fn	bool Entity::InUse();
	 *
	 * @brief	Determines if we can in use.
	 *
	 * @author	Bo Thompson
	 * @date	3/27/2017
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/
	bool InUse();

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::AddActor(const char *moduleName);
	 *
	 * @brief	Adds an actor.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param	moduleName	Name of the module.
	 **************************************************************************************************/
	void AddActor(const char *moduleName);

	/**************************************************************************************************/
	/**
	 * @fn	void Entity::LoadFromDict(json dict);
	 *
	 * @brief	Loads from dictionary.
	 *
	 * @author	Bo Thompson
	 * @date	4/16/2017
	 *
	 * @param	dict	The dictionary.
	 **************************************************************************************************/
	void LoadFromDict(nlohmann::json dict);
};