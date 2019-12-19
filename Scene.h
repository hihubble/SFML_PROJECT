#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Scene
{
public :
	virtual bool initialize(sf::RenderWindow* window) = 0;
	virtual bool update(float frameTime) = 0;
	virtual bool draw() = 0;
	virtual std::string getErrorMessage() = 0;
};