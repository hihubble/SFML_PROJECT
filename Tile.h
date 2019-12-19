#pragma once
class Tile;
#include <SFML/Graphics.hpp>
#include <string>
#include "VertexQuads.h"
#include "TileBuilder.h"
#include "Chunk.h"
#define TILE_SIZE 16

class Tile
{
private:
	VertexQuads* quads;
	TileBuilder* tileBuilder;
	std::string name, orientation;
	int x, y;
	bool exposed;
	Chunk* parent;
public:
	Tile(TileBuilder* tileBuilder, Chunk* chunk, std::string tile_name, std::string tile_orientation, int tile_x, int tile_y);
	void update();
	sf::VertexArray getQuads();
	bool isExposed();
	void setExposed(bool exposed);
	void setOrientation(std::string newOrientation);
	~Tile();
};

