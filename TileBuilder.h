#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "TileInfo.h"

class TileBuilder
{
private:
	std::map<std::string, TileInfo*> tilesInfos;
	void readTileFile(std::string file);
public:
	TileBuilder(std::string file);
	sf::VertexArray getTileVertices(std::string tileName, std::string orientation, int x, int y);
};

