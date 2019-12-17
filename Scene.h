#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Scene
{
public :
	virtual bool initialize() = 0;
	virtual bool update(float frameTime) = 0;
	virtual bool draw(sf::RenderWindow* window) = 0;
	virtual std::string getErrorMessage() = 0;
};