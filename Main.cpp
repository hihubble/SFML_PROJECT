#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include <chrono>
#include "Scene.h"
#include <Windows.h>

long timeElapsed(std::chrono::steady_clock::time_point timeStart)
{
	auto timeNow = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(timeNow - timeStart).count();
}

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Terarbis");
	window.setVerticalSyncEnabled(true);

	Scene* currentScene = NULL;
	currentScene->initialize();

	//Starting time
	auto timeStart = std::chrono::steady_clock::now();

	//While run = true, run game
	bool run = true;

	//Game loop
	while (run)
	{
		//Get elapsed time
		long elapsedTime = timeElapsed(timeStart);

		//If elapsed time > 16'000 (60fps)
		if (elapsedTime > 16'000)
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
			window.clear(sf::Color::Black);

			//Draw scene
			if (!currentScene->draw())
			{
				std::string errMsg = currentScene->getErrorMessage();
				MessageBoxA(NULL, errMsg.c_str(), "ERROR", MB_OK);
				break;
			}

			//Display to window
			window.display();
		}
	}

	return 1;
}