#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "VertexQuads.h"

class TileOrientation
{
public:
	TileOrientation();
	std::string name;
	VertexQuads* quads;
};

class TileInfo
{
private:
	std::string name;
	std::map<std::string, TileOrientation*> tileOrientations;
public:
	TileInfo();
	void setName(std::string name);
	std::string getName();
	void addOrientation(TileOrientation* tileOrientation);
	TileOrientation* getOrientation(std::string orientation);
};

