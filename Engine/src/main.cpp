/**
 * @file src\main.cpp
 *
 * Implements the main class.
 */
#ifndef _DEBUG
#include <windows.h>
#endif
#include <SFML/Graphics.hpp>

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
	sf::Window window(sf::VideoMode(800, 600), "Mortal Hymn");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}