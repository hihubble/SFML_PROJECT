#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#define TILE_SIZE 16

class Tile
{
private:
	sf::Sprite* sprite;
	std::string name;
public:
	Tile(sf::Texture* tile_texture, std::string tile_name, int x, int y);
	sf::Sprite* getSprite();
};

