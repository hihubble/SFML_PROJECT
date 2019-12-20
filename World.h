#pragma once
#include "Tile.h"
#include "Chunk.h"
class World
{
private:
	TileBuilder* tileBuilder;
	sf::View* camera;

	Tile*** tiles;
	Chunk*** chunks;
	int viewX, viewY;
	int worldWidth, worldHeight;
	int tileHorizontalCount, tileVerticalCount;
	int pixelHorizontalCount, pixelVerticalCount;
	int isTile(int x, int y);
	void setTile(std::string tileName, int x, int y);
	void deleteTile(int x, int y);

	void verifyExposition(int x, int y);
	void verifyAreaExposition(int x, int y);

	void verifyOrientation(int x, int y);
	void verifyAreaOrientation(int x, int y);

	void createWorld();

	void createEmptyWorld();
	void generateSimple();
	void setOrientations();
	void setExposition();
public:
	World(sf::View* camera, int w, int h);
	void update(float frameTime);
	void draw(sf::RenderWindow* window);
	void setActivePosition(int x, int y);
};

