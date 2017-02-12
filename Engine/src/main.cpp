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
#include "scripts.h"
#include "actor.h"
#include "shader.h"


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





/**
 * Main entry-point for this application.
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/25/2017
 */
#ifdef _DEBUG
/**
 * @param argc The number of command - line arguments provided.
 * @param argv An array of command - line argument strings.
 */
int main(int argc, char *argv[])
#else
/**
 *
 * @param hInstance	    The instance.
 * @param hPrevInstance The previous instance.
 * @param lpCmdLine	    The command line.
 * @param nCmdShow	    The command show.
 */
int APIENTRY WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow
)
#endif
/**
 *
 * @return An APIENTRY.
 */
{
	sf::ContextSettings settings;
	int err;
	sf::Clock clock;
	sf::Time last_time;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	Shader shader;
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
	shader.LoadFragmentShader("test.frag");
	shader.LoadVertexShader("test.vert");
	shader.LinkShader();
		//printf("Shader successful\n");
	setup_python();
	Actor *test_machine = new Actor("testFSM");
	last_time = clock.getElapsedTime();
	int i = 0;
	shader.Use();
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
		int elapsed = clock.restart().asMilliseconds();		
		test_machine->Update(elapsed);
		last_time = clock.getElapsedTime();
		sf::sleep(sf::milliseconds(15 - elapsed));
	}
	shutdown_python();
	return 0;
}
