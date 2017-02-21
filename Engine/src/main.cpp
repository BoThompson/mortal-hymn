/**
 * @file src\main.cpp
 *
 * Implements the main class.
 */
#ifndef _DEBUG
#include <windows.h>
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
#include "entity.h"
#include "scripts.h"
#include "actor.h"
#include "shader.h"


static const std::vector<glm::vec3> points = {
								{-1, 0, -10},
								{1, 0, -10},
								{0, 1, -10},

								//Colors!
								{1, .5, 1},
								{.5, 1, 0},
								{0, .5, 1},

								//Barycentric!
								{1, 0, 0 },
								{0, 1, 0 },
								{0, 0, 1 } };
GLuint vbo;


/**
 * Draws the scene (TEMPORARY FUNCTION)
 *
 * @author Ulysee "Bo" Thompson
 * @date 1/26/2017
 */
void draw()
{

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0].x, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (9 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(18 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
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
	Entity_T entity;
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
	glm::mat4 modelMatrix = glm::mat4(1.0);
	glm::mat4 projectionMatrix = glm::mat4(1.0);
	glm::mat4 viewMatrix = glm::mat4(1.0);
	glm::mat4  MVP;
	glm::vec3 camVector = glm::vec3(0, 0, 1);
	glm::vec3 triRotation = glm::vec3(0, 0, 0);
	projectionMatrix = glm::perspective(glm::radians(35.0f), 800.0f / 600.0f, 1.0f, 100.0f);
	//projectionMatrix = glm::ortho(0, 800, 0, 600);
	sf::Window window(sf::VideoMode(800, 600), "Mortal Hymn", sf::Style::Default, settings);
	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		return -1;
	}
	printf("%f %f %f\n%f %f %f\n",
		points[0].x, *(&points[0].x + 1), *(&points[0].x + 2),
		*(&points[0].x + 3), *(&points[0].x + 4), *(&points[0].x + 5));
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	entity.SetVertices(points);
	glBufferData(GL_ARRAY_BUFFER, entity.Vertices().size() * sizeof(glm::vec3), &entity.Vertices()[0][0], GL_STATIC_DRAW);
	shader.LoadFragmentShader("test.frag");
	shader.LoadVertexShader("test.vert");
	shader.LinkShader();
		//printf("Shader successful\n");
	setup_python();
	Actor *test_machine = new Actor(&entity, "testFSM");
	last_time = clock.getElapsedTime();
	int i = 0;
	shader.Use();
	while (window.isOpen())
	{
		sf::Event event;
		triRotation = glm::vec3(0, 0, 0);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					camVector.x += .01;
					break;
				case sf::Keyboard::Left:
					camVector.x -= .01;
					break;
				case sf::Keyboard::Up:
					camVector.y += .01;
					break;
				case sf::Keyboard::Down:
					camVector.y -= .01;
					break;
				case sf::Keyboard::A:
					triRotation.z += .01;
					break;
				case sf::Keyboard::D:
					triRotation.z -= .01;
					break;
				case sf::Keyboard::W:
					triRotation.y += .01;
					break;
				case sf::Keyboard::S:
					triRotation.y -= .01;
					break;
				}
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform1f(shader.Uniform("baryFactor"), .2 + .1 * sinf(clock.getElapsedTime().asSeconds()));
		viewMatrix = glm::lookAt(glm::vec3(camVector), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		MVP = projectionMatrix * viewMatrix;
		glUniformMatrix4fv(shader.Uniform("MVP"), 1, GL_FALSE,  &MVP[0][0]);
		entity.Draw(shader, MVP);
		//draw();
		window.display();
		int elapsed = (clock.getElapsedTime() - last_time).asMilliseconds();
		test_machine->Update(elapsed);
		last_time = clock.getElapsedTime();
		sf::sleep(sf::milliseconds(15 - elapsed));
	}
	shutdown_python();
	return 0;
}
