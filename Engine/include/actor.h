#pragma once
class Actor
{
	
	int _timer;
	int _state;
	PyObject *_FSM;
	Actor();
public:
	Actor(const char *fsmName);
	void SetTimer(int timer);
	int Timer();
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