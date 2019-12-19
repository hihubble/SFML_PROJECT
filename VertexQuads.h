#pragma once
#include "sfml/Graphics.hpp"

class VertexQuads
{
public:
	VertexQuads();
	void append(sf::Vertex vertex);
	void append(sf::VertexArray vArray);
	sf::VertexArray vertices;
	//~VertexQuads();
};