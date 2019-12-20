#include "Chunk.h"

void Chunk::load()
{
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			if (isTile(i, j)) tiles[i][j]->load();
		}
	}
}

void Chunk::unload()
{
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			if (isTile(i, j)) tiles[i][j]->unload();
		}
	}
}

Chunk::Chunk(TileBuilder* tileBuilder_, int x, int y)
{
	tileBuilder = tileBuilder_;
	quads = new VertexQuads();
	tiles = new Tile**[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		tiles[i] = new Tile * [CHUNK_SIZE];
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}

	modified = true;
	active = true;
}

void Chunk::setTile(Tile* tile, int x, int y)
{
	tiles[x][y] = tile;
	modified = true;
}

bool Chunk::isTile(int x, int y)
{
	return tiles[x][y] != NULL;
}

bool Chunk::needsUpdate()
{
	return modified;
}

void Chunk::update()
{
	quads->vertices.clear();
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			if (isTile(i, j))
			{
				quads->append(tiles[i][j]->getQuads());
			}
		}
	}
	modified = false;
}

sf::VertexArray Chunk::getQuads()
{
	return quads->vertices;
}

bool Chunk::isActive()
{
	return active;
}

void Chunk::setActive(bool active_)
{
	if (active && !&active_)
	{
		unload();
	}
	else if (!active && active_)
	{
		load();
	}

	active = active_;

	if (active && modified)
	{
		update();
	}
}
