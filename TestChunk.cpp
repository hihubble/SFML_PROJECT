#include "TestChunk.h"

TestChunk::TestChunk()
{
	errMsg = "";
}

bool TestChunk::initialize(sf::RenderWindow* window_)
{
	window = window_;

	world = new World(30, 15);

	zoom = 1;

	camera.setCenter(1700, 750);
	camera.setSize(1700 * zoom, 900 * zoom);
	window->setView(camera);

	return true;
}

bool TestChunk::update(float frameTime)
{
	float frameRatio = frameTime / 16'000'000;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		camera.move(-10 * frameRatio * zoom, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera.move(10 * frameRatio * zoom, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		camera.move(0, -10 * frameRatio * zoom);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		camera.move(0, 10 * frameRatio * zoom);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		zoom /= 1.005;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		zoom *= 1.005;
	}

	camera.setSize(1700 * zoom, 900 * zoom);
	window->setView(camera);

	world->update(frameTime);

	return true;
}

bool TestChunk::draw()
{
	world->draw(window);

	return true;
}

std::string TestChunk::getErrorMessage()
{
	return errMsg;
}
