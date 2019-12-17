#include "TestChunk.h"

TestChunk::TestChunk()
{
	errMsg = "";
}

bool TestChunk::initialize()
{
	chunk = new Chunk();
	sf::Texture* ttarget = new sf::Texture();
	ttarget->loadFromFile("resources/tiles/dirt.png");
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			Tile* tile = new Tile(ttarget, "dirt", i, j);
			chunk->setTile(tile, i, j);
		}
	}

	return true;
}

bool TestChunk::update(float frameTime)
{
	if (chunk->needsRedraw())
	{
		chunk->update();
	}
	return true;
}

bool TestChunk::draw(sf::RenderWindow* window)
{

	window->draw(*chunk->getSprite());

	return true;
}

std::string TestChunk::getErrorMessage()
{
	return errMsg;
}
