#include "VertexQuads.h"

VertexQuads::VertexQuads()
{
	vertices.setPrimitiveType(sf::Quads);
}

void VertexQuads::append(sf::Vertex vertex)
{
	vertices.append(vertex);
}

void VertexQuads::append(sf::VertexArray vArray)
{
	for (int i = 0; i < vArray.getVertexCount(); i++)
	{
		vertices.append(vArray[i]);
	}
}

/*VertexQuads::~VertexQuads()
{
	vertices.clear();
}*/
