/**************************************************************************************************/
/**
 * @file	src\actor.cpp.
 *
 * @brief	Implements the actor class.
 **************************************************************************************************/
#include "game.h"

/**************************************************************************************************/
Actor::Actor(Entity *entity, const char *fsmName)
{
	PyObject *pResult;
	m_state = -100;
	m_timer = -100;
	if (loadPyModule(fsmName) == NULL)
	{

	}else if((m_pyModule = NewAI(fsmName)) == NULL)
	{
		printf("Error(FSM constructor): python class is null.");
		return;
	}else
	{
		m_entity = entity;
		PyObject *actor = PyCapsule_New(entity, "pointer", NULL);
		PyObject_SetAttrString(m_pyModule, "pointer", actor);

		pResult = PyObject_CallMethod(m_pyModule, "start", NULL);
		
		m_state = _PyLong_AsInt(PyObject_GetAttrString(m_pyModule, "state"));
		m_timer = _PyLong_AsInt(PyObject_GetAttrString(m_pyModule, "timer"));
	}
	//else
	//{
	//	PyErr_Print();
	//}
	//Call the initializer and retrieve the states
	//trigger an automatic update
}

/**************************************************************************************************/
void Actor::SetTimer(int timer)
{
	m_timer = timer;
}
/**************************************************************************************************/
int Actor::Timer()
{
	return m_timer;
}
/**************************************************************************************************/
void Actor::SetState(int state)
{
	m_state = state;
}
/**************************************************************************************************/
int Actor::State()
{
	return m_state;
}

/**************************************************************************************************/
void Actor::Update(int delta)
{
	if (m_state < 0)
		return;
	if ((m_timer -= delta) < 0)
	{
		//Call the python FSM method
		//Update the state
		PyObject_CallMethod(m_pyModule, "update", NULL);
		m_state = _PyLong_AsInt(PyObject_GetAttrString(m_pyModule, "state"));
		m_timer = _PyLong_AsInt(PyObject_GetAttrString(m_pyModule, "timer"));
	}
}
/**************************************************************************************************/
Entity *Actor::GetEntity()
{
	return m_entity;
}

/**************************************************************************************************/
void Actor::SetEntity(Entity *entity)
{
	m_entity = entity;
}

/**************************************************************************************************/
void Actor::Reset()
{
	m_entity = 0;
	m_inUse = true;
	m_pyModule = NULL;
	m_state = 0;
	m_timer = 0;
}
/**************************************************************************************************/

bool Actor::InUse()
{
	return m_inUse;
}
/**************************************************************************************************/
Actor::Actor()
{

}
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
