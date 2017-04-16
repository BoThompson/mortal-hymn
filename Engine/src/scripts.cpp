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

/**
 * MSDN recommends against using getcwd & chdir names.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 */

#define cwd _getcwd

/**
 * A macro that defines CD.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 */

#define cd _chdir
#else
#include "unistd.h"

/**
 * A macro that defines cwd.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 */

#define cwd getcwd

/**
 * A macro that defines CD.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 */

#define cd chdir
#endif

#include "game.h"



/** The cwd path[ 4096]. */
char cwd_path[4096];
/** The modules. */
std::map<std::string, PyObject*> modules;

/**
 * Object as entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] ptrObj If non-null, the pointer object.
 *
 * @return Null if it fails, else a pointer to an Entity_T.
 */

static Entity *ObjectAsEntity(PyObject *ptrObj)
{
	return (Entity *)PyCapsule_GetPointer(ptrObj, "pointer");;
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
	float x, y, z;
	if (!PyArg_ParseTuple(args, "Offf", &ptrObj, &x, &y, &z))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	entity->Translate(glm::vec3(x, y, z));
	//printf("Translate was called.\n");
	Py_INCREF(Py_None);
	return Py_None;
}

/**
 * Rotates a passed game entity.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments from python.
 *
 * @return Null if it fails, else a pointer to a PyObject.
 */

static PyObject *Rotate(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	float x, y, z;
	if (!PyArg_ParseTuple(args, "Offf", &ptrObj, &x, &y, &z))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	entity->SetRotation(glm::vec3(x, y, z));
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *Scale(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	float x, y, z;
	if (!PyArg_ParseTuple(args, "Offf", &ptrObj, &x, &y, &z))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	entity->SetScale(glm::vec3(x, y, z));
	Py_INCREF(Py_None);
	return Py_None;
}

/**
 * Gets a position.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments.
 *
 * @return Null if it fails, else the position.
 */

static PyObject *GetPosition(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	glm::vec3 pos;

	if (!PyArg_ParseTuple(args, "O", &ptrObj))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	pos = entity->Position();
	PyObject *object = Py_BuildValue("(fff)", pos.x, pos.y, pos.z);
	return object;
}

/**
 * Gets a rotation.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments.
 *
 * @return Null if it fails, else the rotation.
 */

static PyObject *GetRotation(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	glm::vec3 rot;

	if (!PyArg_ParseTuple(args, "O", &ptrObj))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	rot = entity->Rotation();
	PyObject *object = Py_BuildValue("(fff)", rot.x, rot.y, rot.z);
	return object;
}

/**
 * Gets a scale.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments.
 *
 * @return Null if it fails, else the scale.
 */

static PyObject *GetScale(PyObject *self, PyObject *args)
{
	PyObject *ptrObj;
	glm::vec3 scl;

	if (!PyArg_ParseTuple(args, "O", &ptrObj))
		return NULL;
	Entity *entity = ObjectAsEntity(ptrObj);
	scl = entity->Scale();
	PyObject *object = Py_BuildValue("(fff)", scl.x, scl.y, scl.z);
	return object;
}

/**
 * Gets a time.
 *
 * @author Ulysee "Bo" Thompson
 * @date 2/27/2017
 *
 * @param [in,out] self If non-null, the class instance that this method operates on.
 * @param [in,out] args If non-null, the arguments.
 *
 * @return Null if it fails, else the time.
 */

static PyObject *GetTime(PyObject *self, PyObject *args)
{
	PyObject *object = Py_BuildValue("i", game->Time().asMilliseconds());
	return object;
}
/** The interface methods[]. */
static PyMethodDef InterfaceMethods[] = {
	{ "time",			GetTime,			METH_VARARGS, "Provides the game's current time (in milliseconds)" },
	{ "scale",			Scale,			METH_VARARGS, "Scales a game entity." },
	{ "rotate",			Rotate,			METH_VARARGS, "Rotates a game entity." },
	{ "translate",		Translate,		METH_VARARGS, "Translates a game entity." },
	{ "getposition",		GetPosition,		METH_VARARGS, "Retrieves the position of a game entity"},
	{ "getrotation",		GetRotation,		METH_VARARGS, "Retrieves the rotation of a game entity" },
	{ "getscale",		GetScale,		METH_VARARGS, "Retrieves the scale of a game entity" },
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

PyObject *loadPyModule(const char * const module_name)
{

	PyObject *pModule;
	
	if ((pModule = game->GetPyModule(module_name)) != NULL)
		return pModule;

	// Load the module object
	if ((pModule = PyImport_ImportModule(module_name)) == NULL)
	{
		PyErr_Print();
		return NULL;
	}
	game->AddPyModule(module_name, pModule);
	
	return pModule;
}

/**************************************************************************************************/
/**
 * @fn	PyObject *NewAI(const char* const fsmName)
 *
 * @brief	Creates a new AI from a PyModule
 *
 * @author	Ulysee "Bo" Thompson
 * @date	2/27/2017
 *
 * @param	fsmName	Name of the fsm.
 *
 * @return	Null if it fails, else a pointer to a PyObject.
 **************************************************************************************************/
PyObject *NewAI(const char* const pyName)
{
	 PyObject *module;
	if (pyName == NULL || strlen(pyName) == 0)
	{
		printf("Error(NewAI): py Name is not valid.\n");
		return NULL;
	}

	if ((module = game->GetPyModule(pyName)) == NULL)
	{
		printf("Error(NewAI): module %s is not loaded.\n", pyName);
		return NULL;
	}

	PyObject *clss = PyObject_GetAttrString(module, pyName);
	if (clss == NULL)
	{
		printf("Error(NewAI): module does not contain class %s\n.", pyName);
		return NULL;
	}
	PyObject *ai = PyObject_CallMethod(module, pyName, "");
	return ai;

}

