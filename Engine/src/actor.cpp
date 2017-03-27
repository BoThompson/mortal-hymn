#include <gl\glew.h>
#include <glm\glm.hpp>
#include <SFML\graphics.hpp>
#include <vector>
#include "game.h"


/**
 * Default constructor.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/9/2017
 */
Actor::Actor(Entity *entity, const char *fsmName)
{
	PyObject *pResult;
	m_state = -100;
	m_timer = -100;
	if (load_module(fsmName) == NULL)
	{

	}else if((m_FSM = NewFSM(fsmName)) == NULL)
	{
		printf("Error(FSM constructor): python class is null.");
		return;
	}else
	{
		m_entity = entity;
		PyObject *actor = PyCapsule_New(entity, "pointer", NULL);
		PyObject_SetAttrString(m_FSM, "pointer", actor);

		pResult = PyObject_CallMethod(m_FSM, "start", NULL);
		
		m_state = _PyLong_AsInt(PyObject_GetAttrString(m_FSM, "state"));
		m_timer = _PyLong_AsInt(PyObject_GetAttrString(m_FSM, "timer"));
	}
	//else
	//{
	//	PyErr_Print();
	//}
	//Call the initializer and retrieve the states
	//trigger an automatic update
}

/**
 * Sets a timer.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/5/2017
 *
 * @param timer The timer.
 */
void Actor::SetTimer(int timer)
{
	m_timer = timer;
}

/**
 * Gets the timer.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/5/2017
 *
 * @return An int.
 */
int Actor::Timer()
{
	return m_timer;
}

/**
 * Sets a state.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/5/2017
 *
 * @param state The state.
 */
void Actor::SetState(int state)
{
	m_state = state;
}

/**
 * Gets the state.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/5/2017
 *
 * @return An int.
 */
int Actor::State()
{
	return m_state;
}


/**
 * Calls on the Finite State Machine's update method if the timer has elapsed
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/5/2017
 *
 * @param delta The delta.
 */
void Actor::Update(int delta)
{
	if (m_state < 0)
		return;
	if ((m_timer -= delta) < 0)
	{
		//Call the python FSM method
		//Update the state
		PyObject_CallMethod(m_FSM, "update", NULL);
		m_state = _PyLong_AsInt(PyObject_GetAttrString(m_FSM, "state"));
		m_timer = _PyLong_AsInt(PyObject_GetAttrString(m_FSM, "timer"));
	}
}

Entity *Actor::GetEntity()
{
	return m_entity;
}

/**
 * Sets an entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 *
 * @param [in,out] entity If non-null, the entity.
 */

void Actor::SetEntity(Entity *entity)
{
	m_entity = entity;
}