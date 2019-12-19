#include "Tile.h"

Tile::Tile(TileBuilder* tileBuilder_, Chunk* chunk, std::string tile_name, std::string tile_orientation, int tile_x, int tile_y)
{
	x = tile_x;
	y = tile_y;
	tileBuilder = tileBuilder_;
	quads = new VertexQuads();
	orientation = tile_orientation;
	quads->append(tileBuilder->getTileVertices(tile_name, orientation, x * TILE_SIZE, y * TILE_SIZE));
	name = tile_name;
	exposed = false;
	parent = chunk;
}

void Tile::update()
{
	quads->vertices.clear();
	quads->append(tileBuilder->getTileVertices(name, orientation, x * TILE_SIZE, y * TILE_SIZE));
	parent->modified = true;
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
}

void Tile::setOrientation(std::string newOrientation)
{
	orientation = newOrientation;
}

Tile::~Tile()
{
	quads->vertices.clear();
}
