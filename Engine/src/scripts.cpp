/**
 * @file src\scripts.cpp
 *
 * Implements the scripts class.
 */
#ifdef _DEBUG
#undef _DEBUG
#include <python.h>
#define _DEBUG
#else
#include <python.h>
#endif
#include <string.h>
#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "scripts.h"
#include "entity.h"
#include "actor.h"


char cwd_path[4096];
std::map<std::string, PyObject*> modules;

static Entity_T *ObjectAsEntity(PyObject *ptrObj)
{
	return (Entity_T *)PyCapsule_GetPointer(ptrObj, "pointer");;
}




/**
 * Translates.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/20/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments.
 *
 * @return Null if it fails, else a pointer to a PyObject.
 */

static PyObject *Translate(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	int sts;
	float x, y, z;
	if (!PyArg_ParseTuple(args, "Offf", &ptrObj, &x, &y, &z))
		return NULL;
	Entity_T *entity = ObjectAsEntity(ptrObj);
	entity->Translate(glm::vec3(x, y, z));
	//printf("Translate was called.\n");
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *GetPosition(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;

	int sts;
	glm::vec3 pos;
	if (!PyArg_ParseTuple(args, "O", &ptrObj))
		return NULL;
	Entity_T *entity = ObjectAsEntity(ptrObj);
	pos = entity->Position();
	PyObject *object = Py_BuildValue("(fff)", pos.x, pos.y, pos.z);
	return object;
}

/** The interface methods[]. */
static PyMethodDef InterfaceMethods[] = {
	{ "translate", Translate, METH_VARARGS, "Translates a game entity." },
	{ "getposition", GetPosition, METH_VARARGS, "Retrieves the position of a game entity"},
	{ NULL, NULL, 0, NULL }
};

/**
* A py module definition.
*
* @author Ulysee "Bo" Thompson
* @date 2/20/2017
*/

static struct PyModuleDef InterfaceModule = {
	PyModuleDef_HEAD_INIT,
	"game",
	NULL,
	-1,
	InterfaceMethods
};

/**
* Py init interface.
*
* @author Ulysee "Bo" Thompson
* @date 2/20/2017
*
* @return A PyMODINIT_FUNC.
*/

PyMODINIT_FUNC PyInit_Interface(void)
{
	 return PyModule_Create(&InterfaceModule);
}


/**
 * Sets up the python.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/1/2017
 *
 * @return An int.
 */
int setup_python()
{
	PyObject *pCwd;

	//Add the game interface module
	PyImport_AppendInittab("game", PyInit_Interface);
	// Initialize the Python Interpreter
	Py_Initialize();
	PyImport_ImportModule("game");
#ifdef _WIN32
	char tmp_path[4096];
	cwd(tmp_path, sizeof tmp_path);
	char *p2 = cwd_path;
	for (char *ptr = tmp_path; *ptr != '\0'; ptr++)
	{
		if (*ptr == '\\')
		{
			*p2++ = '\\';
		}
		*p2++ = *ptr;
	}
	*p2++ = '\0';
	strcat_s(cwd_path, "\\\\scripts\\\\test.dat");
#else
	cwd(cwd_path, sizeof cwd_path);
#endif
	// Build the name object
	pCwd = PyUnicode_FromString(cwd_path);
	printf(cwd_path);
	printf("\n");
	PyObject *syspath = PySys_GetObject("path");
	PyList_Insert(syspath, 0, pCwd);
	return 0;
}




/**
 * Shutdown python.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/1/2017
 */
void shutdown_python()
{
	// Clean up
	//Py_DECREF(pModule);
	//Py_DECREF();

	// Finish the Python Interpreter
	Py_Finalize();
}

/**
 * Loads a python module.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/1/2017
 *
 * @param [in] module_name If non-null, name of the module.
 *
 * @return Null if it fails, else the python.
 */
PyObject *load_module(const char * const module_name)
{

	PyObject *pModule;
	
	if ((pModule = FSManager::Instance().modules[module_name]) != NULL)
		return pModule;

	// Load the module object
	if ((pModule = PyImport_ImportModule(module_name)) == NULL)
	{
		PyErr_Print();
		return NULL;
	}
	FSManager::Instance().modules[module_name] = pModule;
	//// pDict is a borrowed reference 
	//pDict = PyModule_GetDict(pModule);
	//PyErr_Print();
	//// pFunc is also a borrowed reference 
	//pFunc = PyDict_GetItemString(pDict, "testfun");

	//if (PyCallable_Check(pFunc))
	//{
	//	PyObject_CallObject(pFunc, NULL);
	//}
	//else
	//{
	//	PyErr_Print();
	//}

	
	return pModule;
}

PyObject *NewFSM(const char* const fsmName)
{
	if (fsmName == NULL || strlen(fsmName) == 0)
	{
		printf("Error(NewFSM): fsm Name is not valid.\n");
		return NULL;
	}

	if (FSManager::Instance().modules[fsmName] == NULL)
	{
		printf("Error(NewFSM): module %s is not loaded.\n", fsmName);
		return NULL;
	}

	PyObject *clss = PyObject_GetAttrString(FSManager::Instance().modules[fsmName], fsmName);
	if (clss == NULL)
	{
		printf("Error(NewFSM): module does not contain class %s\n.", fsmName);
		return NULL;
	}
	PyObject *fsm = PyObject_CallMethod(FSManager::Instance().modules[fsmName], fsmName, "");
	return fsm;

}

