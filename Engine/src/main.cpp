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

static const GLfloat points[] = {-1, 0, 0,
								 1, 0, 0,
								 0, 1, 0};
GLuint vbo;



void draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
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
