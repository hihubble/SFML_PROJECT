#pragma once
#include "Tile.h"
#define CHUNK_SIZE 16

class Chunk
{
private:
	Tile*** tiles;
	sf::RenderTexture* renderTexture;
	sf::Sprite* sprite;
	bool modified;
public:
	Chunk();
	void setTile(Tile* tile, int x, int y);
	bool needsRedraw();
	void update();
	sf::Sprite* getSprite();
};

