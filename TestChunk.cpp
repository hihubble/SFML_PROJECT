#include "TestChunk.h"

TestChunk::TestChunk()
{
	errMsg = "";
}

bool TestChunk::initialize(sf::RenderWindow* window_)
{
	window = window_;

	zoom = 0.5;

	camera = new sf::View();
	camera->setCenter(1700, 750);
	camera->setSize(1700 * zoom, 900 * zoom);

	world = new World(camera, 10, 5);

	font.loadFromFile("resources/fonts/Minecraft.ttf");
	text.setFont(font);

	return true;
}

bool TestChunk::update(float frameTime)
{
	float frameRatio = frameTime / 16'000'000;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		camera->move(-10 * frameRatio * zoom, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera->move(10 * frameRatio * zoom, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		camera->move(0, -10 * frameRatio * zoom);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		camera->move(0, 10 * frameRatio * zoom);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		zoom /= 1.005;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		zoom *= 1.005;
	}

	camera->setSize(1700 * zoom, 900 * zoom);
	window->setView(*camera);

	world->update(frameTime);

	fps = 1'000'000'000 / frameTime;

	return true;
}

bool TestChunk::draw()
{
	world->draw(window);

	text.setString(std::to_string(fps));
	text.setScale(zoom, zoom);
	text.setPosition(camera->getCenter().x - (camera->getSize().x / 2), camera->getCenter().y - (camera->getSize().y / 2));
	window->draw(text);

	return true;
}

std::string TestChunk::getErrorMessage()
{
	return errMsg;
}
