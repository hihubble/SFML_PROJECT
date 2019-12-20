#include "Tile.h"

Tile::Tile(TileBuilder* tileBuilder_, Chunk* chunk, std::string tile_name, std::string tile_orientation, int tile_x, int tile_y)
{
	x = tile_x;
	y = tile_y;
	tileBuilder = tileBuilder_;
	orientation = tile_orientation;
	name = tile_name;
	quads = new VertexQuads();
	quads->append(tileBuilder->getTileVertices(name, orientation, x * TILE_SIZE, y * TILE_SIZE));
	exposed = false;
	parent = chunk;
}

void Tile::update()
{
	quads->vertices.clear();
	quads->append(tileBuilder->getTileVertices(name, orientation, x * TILE_SIZE, y * TILE_SIZE));
	parent->modified = true;
}

void Tile::load()
{
	/*if (quads == NULL) quads = new VertexQuads();
	else quads->clear();
	parent->modified = true;*/
}

void Tile::unload()
{
	/*if (quads != NULL)
	{
		quads->destroy();
		delete quads;
		quads = NULL;
	}*/
}

sf::VertexArray Tile::getQuads()
{
	return quads->vertices;
}

bool Tile::isExposed()
{
	return exposed;
}

void Tile::setExposed(bool exposed_)
{
	exposed = exposed_;
	parent->modified = true;
}

void Tile::setOrientation(std::string newOrientation)
{
	orientation = newOrientation;
	update();
	parent->modified = true;
}

Tile::~Tile()
{
	quads->vertices.clear();
}