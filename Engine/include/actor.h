#pragma once
class Actor
{
	
	int _timer;
	int _state;
	PyObject *_FSM;
	class Entity_T *_entity;
	Actor();
public:
	Actor(Entity_T *entity, const char *fsmName);
	void SetTimer(int timer);
	int Timer();
	void SetEntity(class Entity_T *entity);
	class Entity_T *Entity();
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