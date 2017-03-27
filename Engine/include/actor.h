#pragma once
class Actor
{
	
	int m_timer;
	int m_state;
	PyObject *m_FSM;
	class Entity *m_entity;
	Actor();
public:
	Actor(Entity *entity, const char *fsmName);
	void SetTimer(int timer);
	int Timer();
	void SetEntity(class Entity *entity);
	Entity *GetEntity();
	void SetState(int state);
	int State();
	void Update(int delta);
};

class FSManager
{
	FSManager() {};
	FSManager(FSManager const&);
	void operator=(FSManager const&);
public:
	static FSManager& Instance()
	{
		static FSManager instance;
		return instance;
	}
	std::map<std::string, PyObject*> modules;
	std::map<std::string, PyObject*> fsms;

};