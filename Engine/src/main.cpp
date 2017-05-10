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
#include "game.h"
#include "entity.h"
#include "scripts.h"
#include "actor.h"
#include "shader.h"

Game *game;


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
{
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----
	
	game = new Game();

	int i = 0;
	int progressCounter = 0;
	game->Startup();
	while (!game->Ended())
	{
		game->Input();
		game->Update();
		game->Draw();
		sf::sleep(sf::milliseconds(15 - game->Delta().asMilliseconds()));
	}
	shutdown_python();
	return 0;
}
