#include "Chunk.h"

Chunk::Chunk()
{
	tiles = new Tile**[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		tiles[i] = new Tile * [CHUNK_SIZE];
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}

	renderTexture = new sf::RenderTexture();
	renderTexture->create(CHUNK_SIZE * TILE_SIZE, CHUNK_SIZE * TILE_SIZE);
	sprite = new sf::Sprite();

	modified = true;
}

void Chunk::setTile(Tile* tile, int x, int y)
{
	tiles[x][y] = tile;
}

bool Chunk::needsRedraw()
{
	return modified;
}

void Chunk::update()
{
	renderTexture->clear();
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			if (tiles[i][j] != NULL)
			{
				renderTexture->draw(*tiles[i][j]->getSprite());
				
			}
		}
	}
	renderTexture->display();
	if(sprite->getTexture() != NULL) sprite->getTexture()->~Texture();
	sprite->setTexture(renderTexture->getTexture());

	modified = false;
}

sf::Sprite* Chunk::getSprite()
{
	return sprite;
}
