//LIBRARIES
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include <chrono>
#include <Windows.h>
#include <thread>
#include <time.h>

//USER HEADERS
#include "Scene.h"
#include "TestChunk.h"

//DEBUG includes

long timeElapsed(std::chrono::steady_clock::time_point timeStart)
{
	auto timeNow = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(timeNow - timeStart).count();
}

int main(int argc, char* argv[])
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1700, 900), "Terarbis");
	//window->setVerticalSyncEnabled(true);

	Scene* currentScene = new TestChunk();

	//Starting time
	auto timeStart = std::chrono::steady_clock::now();

	//While run = true, run game
	bool run = true;

	//Target FPS
	int fps = 10000;

	currentScene->initialize(window);

	// TESTS

	// ENDTESTS

	//Game loop
	while (run)
	{
		//Get elapsed time
		long elapsedTime = timeElapsed(timeStart);

		//If elapsed time > 16'000'000 (60fps)
		if (elapsedTime >= 1'000'000'000 / fps)
		{
			//Last frame time_point = now
			timeStart = std::chrono::steady_clock::now();

			//Update scene
			if (!currentScene->update((float)elapsedTime))
			{
				std::string errMsg = currentScene->getErrorMessage();
				MessageBoxA(NULL, errMsg.c_str(), "ERROR", MB_OK);
				break;
			}

			//Clear window
			window->clear(sf::Color::Color(135, 206, 235, 0));

			//Draw scene
			if (!currentScene->draw())
			{
				std::string errMsg = currentScene->getErrorMessage();
				MessageBoxA(NULL, errMsg.c_str(), "ERROR", MB_OK);
				break;
			}

			//Display to window
			window->display();
		}
	}

	return 1;
}