#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include "Chunk.h"
#include "World.h"
#include "TileBuilder.h"
#include "VertexQuads.h"

class TestChunk : public Scene
{
private:
	sf::View* camera;
	sf::RenderWindow* window;
	float zoom;
	int fps;

	std::string errMsg;
	sf::Text text;
	sf::Font font;

	World* world;
	TileBuilder* tb;
	VertexQuads* quads;
public:
	TestChunk();
	bool initialize(sf::RenderWindow* window_);
	bool update(float frameTime);
	bool draw();
	std::string getErrorMessage();
};

