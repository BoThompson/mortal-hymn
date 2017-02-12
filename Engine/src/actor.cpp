#include "scripts.h"
#include "actor.h"


/**
 * Default constructor.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/9/2017
 */
Actor::Actor(const char *fsmName)
{
	PyObject *pResult;
	_state = -100;
	_timer = -100;
	if (load_module(fsmName) == NULL)
	{

	}else if((_FSM = NewFSM(fsmName)) == NULL)
	{
		printf("Error(FSM constructor): python class is null.");
		return;
	}else
	{
		pResult = PyObject_CallMethod(_FSM, "start", NULL);
		_state = _PyLong_AsInt(PyObject_GetAttrString(_FSM, "state"));
		_timer = _PyLong_AsInt(PyObject_GetAttrString(_FSM, "timer"));
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
	_timer = timer;
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
	return _timer;
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
	_state = state;
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
	return _state;
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
	if (_state < 0)
		return;
	if ((_timer -= delta) < 0)
	{
		//Call the python FSM method
		//Update the state
		PyObject_CallMethod(_FSM, "update", NULL);
		_state = _PyLong_AsInt(PyObject_GetAttrString(_FSM, "state"));
		_timer = _PyLong_AsInt(PyObject_GetAttrString(_FSM, "timer"));
	}
}
