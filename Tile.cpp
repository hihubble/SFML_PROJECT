#include "Tile.h"

Tile::Tile(sf::Texture* tile_texture, std::string tile_name, int x, int y)
{
	sprite = new sf::Sprite();
	sprite->setTexture(*tile_texture);
	sprite->setPosition(x * TILE_SIZE, y * TILE_SIZE);
	name = tile_name;
}

sf::Sprite* Tile::getSprite()
{
	return sprite;
}

