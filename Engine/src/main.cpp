/**
 * @file src\main.cpp
 *
 * Implements the main class.
 */
#ifndef _DEBUG
#include <windows.h>
#endif
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#ifdef _DEBUG
#undef _DEBUG
#include <python.h>
#define _DEBUG
#else
#include <python.h>
#endif

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

static const GLfloat points[] = {-1, 0, 0,
								 1, 0, 0,
								 0, 1, 0};
GLuint vbo;


/**
 * Draws the scene (TEMPORARY FUNCTION)
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/26/2017
 */
void draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

char cwd_path[4096];
/**
 * Tests the embedded Python.
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/26/2017
 *
 * @return Exit-code for the process - 0 for success, else an error code.
 */

int python_test()
{
	
	PyObject *pName, *pModule, *pDict, *pFunc;
	// Initialize the Python Interpreter
	Py_Initialize();
#ifdef _WIN32
	char tmp_path[4096];
	cwd(tmp_path, sizeof tmp_path);
	char *p2 = cwd_path;
	*p2++ = '\'';
	for (char *ptr = tmp_path; *ptr != '\0'; ptr++)
	{
		if(*ptr == '\\')
		{
			*p2++ = '\\';
		}
		*p2++ = *ptr;
	}
	*p2++ = '\'';
	*p2++ = '\0';
#else
	cwd(cwd_path, sizeof cwd_path);
#endif
	// Build the name object
	pName = PyUnicode_FromString("tstr");
	printf(cwd_path);
	printf("\n");
	PyRun_SimpleString("import sys");
	//PyRun_SimpleString("print(sys.path)");
	sprintf_s(tmp_path, "sys.path.append(%s)", cwd_path);
	//PyRun_SimpleString(tmp_path);
	//PyRun_SimpleString("print(sys.path)");
	// Load the module object
	if ((pModule = PyImport_Import(pName)) == NULL)
	{
		PyErr_Print();
		return -1;
	}
	else if (!PyModule_Check(pModule)) {

	}
	else {
		PyModuleDef *def = PyModule_GetDef(pModule);
		PyErr_Print();
		//printf("Module name: %s\n", def->m_name);
		//printf("Module doc: %s\n", def->m_doc);
	}

	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	PyErr_Print();
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, "testfun");

	if (PyCallable_Check(pFunc))
	{
		PyObject_CallObject(pFunc, NULL);
	}
	else
	{
		PyErr_Print();
	}

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);

	// Finish the Python Interpreter
	Py_Finalize();
	return 0;
}




#ifdef _DEBUG
/**
 * Main entry-point for this application.
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/25/2017
 *
 * @param argc The number of command-line arguments provided.
 * @param argv An array of command-line argument strings.
 *
 * @return Exit-code for the process - 0 for success, else an error code.
 */
int main(int argc, char *argv[])
#else
/**
 * Window main.
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/25/2017
 *
 * @param hInstance	    The instance.
 * @param hPrevInstance The previous instance.
 * @param lpCmdLine	    The command line.
 * @param nCmdShow	    The command show.
 *
 * @return An APIENTRY.
 */
int APIENTRY WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow
)
#endif
{
	sf::ContextSettings settings;
	int err;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	sf::Window window(sf::VideoMode(800, 600), "Mortal Hymn", sf::Style::Default, settings);
	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		return -1;
	}
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	python_test();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		window.display();
	}
	return 0;
}
