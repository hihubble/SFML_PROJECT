#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include "Chunk.h"

class TestChunk : public Scene
{
private:
	std::string errMsg;
	Chunk* chunk;
public:
	TestChunk();
	bool initialize();
	bool update(float frameTime);
	bool draw(sf::RenderWindow* window);
	std::string getErrorMessage();
};

