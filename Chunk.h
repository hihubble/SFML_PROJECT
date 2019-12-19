#pragma once
class Chunk;
#include "Tile.h"
#define CHUNK_SIZE 16

class Chunk
{
private:
	Tile*** tiles;
	bool active;
	VertexQuads* quads;
	TileBuilder* tileBuilder;
public:
	Chunk(TileBuilder* tileBuilder_, int x, int y);
	void setTile(Tile* tile, int x, int y);
	bool isTile(int x, int y);
	bool needsUpdate();
	void update();
	sf::VertexArray getQuads();
	bool isActive();
	bool modified;
};

