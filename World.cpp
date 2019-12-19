#include "World.h"

int World::isTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= tileHorizontalCount || y >= tileVerticalCount)
	{
		return -1;
	}
	return tiles[x][y] != NULL ? 1 : 0;
}

void World::setTile(std::string tileName, int x, int y)
{
	int tileXInChunk = x % CHUNK_SIZE;
	int tileYInChunk = y % CHUNK_SIZE;
	int tileChunkX = x / CHUNK_SIZE;
	int tileChunkY = y / CHUNK_SIZE;

	Tile* tile = new Tile(tileBuilder, chunks[tileChunkX][tileChunkY], tileName, "", x, y);
	tiles[x][y] = tile;
	chunks[tileChunkX][tileChunkY]->setTile(tile, tileXInChunk, tileYInChunk);
}

void World::deleteTile(int x, int y)
{
	if (isTile(x, y) == 1)
	{
		Tile* tile = tiles[x][y];
		tiles[x][y] = NULL;
		chunks[x / CHUNK_SIZE][y / CHUNK_SIZE]->setTile(NULL, x % CHUNK_SIZE, y % CHUNK_SIZE);
		tile->~Tile();
		delete tile;
	}
}

void World::verifyExposition(int x, int y)
{
	if (isTile(x, y) == 1)
	{
		bool exposed = false;
		if (isTile(x - 1, y - 1) == 0) exposed = true;
		else if (isTile(x, y - 1) == 0) exposed = true;
		else if (isTile(x + 1, y - 1) == 0) exposed = true;
		else if (isTile(x - 1, y) == 0) exposed = true;
		else if (isTile(x + 1, y) == 0) exposed = true;
		else if (isTile(x - 1, y + 1) == 0) exposed = true;
		else if (isTile(x, y + 1) == 0) exposed = true;
		else if (isTile(x + 1, y + 1) == 0) exposed = true;
		tiles[x][y]->setExposed(exposed);
	}
}

void World::verifyOrientation(int i, int j)
{
	if (isTile(i, j) == 1)
	{
		bool left = isTile(i - 1, j) == 1;
		bool top = isTile(i, j - 1) == 1;
		bool right = isTile(i + 1, j) == 1;
		bool bottom = isTile(i, j + 1) == 1;

		if (left && top && right && bottom)
		{
			tiles[i][j]->setOrientation("Normal"); // 4 sides are tiles 
		}

		else if (left && top && right)
		{
			tiles[i][j]->setOrientation("Bottom"); // 3 sides are tiles
		}
		else if (left && bottom && right)
		{
			tiles[i][j]->setOrientation("Top");
		}
		else if (left && top && bottom)
		{
			tiles[i][j]->setOrientation("Right");
		}
		else if (top && bottom && right)
		{
			tiles[i][j]->setOrientation("Left");
		}

		else if (left && top)
		{
			tiles[i][j]->setOrientation("BottomRight");
		}
		else if (left && right)
		{
			tiles[i][j]->setOrientation("TopBottom");
		}
		else if (left && bottom)
		{
			tiles[i][j]->setOrientation("TopRight");
		}
		else if (top && right)
		{
			tiles[i][j]->setOrientation("LeftBottom");
		}
		else if (top && bottom)
		{
			tiles[i][j]->setOrientation("LeftRight");
		}
		else if (right && bottom)
		{
			tiles[i][j]->setOrientation("LeftTop");
		}

		else if (left)
		{
			tiles[i][j]->setOrientation("TopBottomRight");
		}
		else if (top)
		{
			tiles[i][j]->setOrientation("LeftBottomRight");
		}
		else if (bottom)
		{
			tiles[i][j]->setOrientation("LeftTopRight");
		}
		else if (right)
		{
			tiles[i][j]->setOrientation("LeftTopBottom");
		}

		else
		{
			tiles[i][j]->setOrientation("LeftTopBottomRight");
		}
		tiles[i][j]->update();
	}
}

void World::verifyAreaOrientation(int x, int y)
{
	verifyOrientation(x, y);
	verifyOrientation(x - 1, y);
	verifyOrientation(x + 1, y);
	verifyOrientation(x, y - 1);
	verifyOrientation(x, y + 1);
}

void World::verifyAreaExposition(int x, int y)
{
	verifyExposition(x, y);
	verifyExposition(x - 1, y);
	verifyExposition(x + 1, y);
	verifyExposition(x, y - 1);
	verifyExposition(x, y + 1);
}

void World::createWorld()
{
	createEmptyWorld();
	generateSimple();
	setOrientations();
	setExposition();
}

void World::createEmptyWorld()
{
	//Instanciating Chunk array with empty chunks
	chunks = new Chunk * *[worldWidth];
	for (int i = 0; i < worldWidth; i++)
	{
		chunks[i] = new Chunk * [worldHeight];
		for (int j = 0; j < worldHeight; j++)
		{
			chunks[i][j] = new Chunk(tileBuilder, i, j);
		}
	}

	//Allocating Tile array
	tiles = new Tile * *[tileHorizontalCount];
	for (int i = 0; i < tileHorizontalCount; i++)
	{
		tiles[i] = new Tile * [tileVerticalCount];
		for (int j = 0; j < tileVerticalCount; j++)
		{
			tiles[i][j] = NULL;
		}
	}
}

void World::generateSimple()
{
	srand(time(0));
	for (int i = 0; i < tileHorizontalCount; i++)
	{
		for (int j = tileVerticalCount - 1; j >= 0; j--)
		{
			if (j < tileVerticalCount / 2)
			{
				if (tiles[i][j + 1] != NULL)
				{
					int proba = 2;
					proba += isTile(i - 1, j) == 1;
					proba += isTile(i + 1, j) == 1;
					proba += isTile(i - 1, j + 1) == 1;
					proba += isTile(i + 1, j + 1) == 1;
					proba += isTile(i - 1, j - 1) == 1;
					proba += isTile(i + 1, j + 1) == 1;

					proba *= 4;

					if ((rand() % proba + 5) < proba)
					{
						setTile("dirt" , i, j);
					}
				}
			}
			else
			{
				setTile("dirt" , i, j);
			}
		}
	}
}

void World::setOrientations()
{
	for (int i = 0; i < tileHorizontalCount; i++)
	{
		for (int j = tileVerticalCount - 1; j >= 0; j--)
		{
			verifyOrientation(i, j);
		}
	}
}

void World::setExposition()
{
	for (int i = 0; i < tileHorizontalCount; i++)
	{
		for (int j = tileVerticalCount - 1; j >= 0; j--)
		{
			if (isTile(i, j) == 1)
			{
				bool exposed = false;
				if (isTile(i - 1, j - 1) == 0) exposed = true;
				else if (isTile(i, j - 1) == 0) exposed = true;
				else if (isTile(i + 1, j - 1) == 0) exposed = true;
				else if (isTile(i - 1, j) == 0) exposed = true;
				else if (isTile(i + 1, j) == 0) exposed = true;
				else if (isTile(i - 1, j + 1) == 0) exposed = true;
				else if (isTile(i, j + 1) == 0) exposed = true;
				else if (isTile(i + 1, j + 1) == 0) exposed = true;
				tiles[i][j]->setExposed(exposed);
			}
		}
	}
}

World::World(int w, int h)
{
	worldWidth = w;
	worldHeight = h;

	tileHorizontalCount = worldWidth * CHUNK_SIZE; // Horizontal number of tiles (horizontal number of chunks * number of tiles per chunk);
	tileVerticalCount = worldHeight * CHUNK_SIZE; // Vertical number of tiles (vertical number of chunks * number of tiles per chunk);

	pixelHorizontalCount = tileHorizontalCount * TILE_SIZE;
	pixelVerticalCount = tileVerticalCount * TILE_SIZE;

	tileBuilder = new TileBuilder("resources/tiles/tiles.tvx");

	createWorld();
}

void World::update(float frameTime)
{
	for (int i = 0; i < worldWidth; i++)
	{
		for (int j = 0; j < worldHeight; j++)
		{
			if (chunks[i][j]->isActive() && chunks[i][j]->needsUpdate())
			{
				chunks[i][j]->update();
			}
		}
	}
}

void World::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < worldWidth; i++)
	{
		for (int j = 0; j < worldHeight; j++)
		{
			if (chunks[i][j]->isActive())
			{
				window->draw(chunks[i][j]->getQuads());
			}
		}
	}
}

void World::setActivePosition(int x, int y)
{
}
