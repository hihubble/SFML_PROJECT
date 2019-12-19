#include "TileBuilder.h"
#include <fstream>
#include "TileInfo.h"
#include <list>

void TileBuilder::readTileFile(std::string file)
{
	std::ifstream inFile(file);
	if (inFile.is_open())
	{
		std::string line;

		std::list<std::vector<std::string>> tiles;

		// Build list of tiles
		while (std::getline(inFile, line))
		{
			if (line.compare(std::string("<Tile>")) == 0)
			{
				std::vector<std::string> currentTile;
				while (line.compare(std::string("</Tile>")) != 0)
				{
					if (std::getline(inFile, line))
					{
						currentTile.push_back(line);
					}
					else
					{
						// Reached end of file while parsing tile
					}
				}
				tiles.push_back(currentTile);
			}
		}
		inFile.close();

		// Analyze tile by tile
		for (std::vector<std::string> tile : tiles)
		{
			TileInfo* tileInfo = new TileInfo();

			for (int j = 0; j < tile.size(); j++)
			{
				std::string tileLine = tile[j];
				int lineLength = tileLine.length();
				if (tileLine.find(std::string("<Name>")) != std::string::npos) // If line contains Name tag
				{
					for (int c = 0; c < lineLength; c++)
					{
						if (tileLine.substr(c, 6).compare(std::string("<Name>")) == 0) // Read Name line
						{
							std::string tileName = "";
							c += 6;
							if (tileLine.find(std::string("</Name>")) != std::string::npos)
							{
								while (tileLine.substr(c, 7).compare(std::string("</Name>")) != 0) // While Name end tag not reached
								{
									tileName += tileLine[c];
									c++;
								}
								tileInfo->setName(tileName);
								break;
							}
						}
					}
				}
				else if (tileLine.find(std::string("<Orientation>")) != std::string::npos) // If line contains Orientation tag
				{
					TileOrientation* tileOrientation = new TileOrientation();

					while (!(tileLine.find(std::string("</Orientation>")) != std::string::npos))
					{
						j++;
						tileLine = tile[j];
						lineLength = tileLine.length();
						if (tileLine.find(std::string("<Direction>")) != std::string::npos) // If line contains Direction tag
						{
							for (int c = 0; c < lineLength; c++)
							{
								if (tileLine.substr(c, 11).compare(std::string("<Direction>")) == 0) // Read Direction line
								{
									std::string direction = "";
									c += 11;
									while (tileLine.substr(c, 12).compare(std::string("</Direction>")) != 0) // While Direction end tag not reached
									{
										direction += tileLine[c];
										c++;
									}
									tileOrientation->name = direction;
									break;
								}
							}
						}
						else if (tileLine.find(std::string("<Vertex>")) != std::string::npos) // If line contains Name tag
						{
							for (int c = 0; c < lineLength; c++)
							{
								if (tileLine.substr(c, 8).compare(std::string("<Vertex>")) == 0) // Read Direction line
								{
									int* vertexInfos = new int[8];
									int vertexInfoIndex = 0;
									std::string tempValueStr = "";
									c += 8;
									while (tileLine.substr(c, 9).compare(std::string("</Vertex>")) != 0) // While Direction end tag not reached
									{
										if (tileLine[c] >= '0' && tileLine[c] <= '9')
										{
											tempValueStr += tileLine[c];
										}
										else
										{
											vertexInfos[vertexInfoIndex] = std::stoi(tempValueStr);
											vertexInfoIndex++;
											tempValueStr = "";
										}
										c++;
									};
									if (tempValueStr.compare(std::string("")) != 0 && vertexInfoIndex != 6)
									{
										vertexInfos[vertexInfoIndex] = std::stoi(tempValueStr);
										vertexInfoIndex++;
										tempValueStr = "";
									}
									tileOrientation->quads->append(sf::Vertex(sf::Vector2f(vertexInfos[0], vertexInfos[1]), sf::Color::Color(vertexInfos[4], vertexInfos[5], vertexInfos[6], vertexInfos[7])));
									tileOrientation->quads->append(sf::Vertex(sf::Vector2f(vertexInfos[2], vertexInfos[1]), sf::Color::Color(vertexInfos[4], vertexInfos[5], vertexInfos[6], vertexInfos[7])));
									tileOrientation->quads->append(sf::Vertex(sf::Vector2f(vertexInfos[2], vertexInfos[3]), sf::Color::Color(vertexInfos[4], vertexInfos[5], vertexInfos[6], vertexInfos[7])));
									tileOrientation->quads->append(sf::Vertex(sf::Vector2f(vertexInfos[0], vertexInfos[3]), sf::Color::Color(vertexInfos[4], vertexInfos[5], vertexInfos[6], vertexInfos[7])));
									break;
								}
							}
						}
					}
					tileInfo->addOrientation(tileOrientation);
				}
			}
			tilesInfos.insert(std::pair<std::string, TileInfo*>(tileInfo->getName(), tileInfo));
		}
	}
}

TileBuilder::TileBuilder(std::string file)
{
	readTileFile(file);
}

sf::VertexArray TileBuilder::getTileVertices(std::string tileName, std::string orientation, int x, int y)
{
	if (orientation.compare("Normal") != 0)
	{
		int bp = 0;
	}

	sf::VertexArray tileVertices;
	tileVertices.setPrimitiveType(sf::Quads);

	auto iterator = tilesInfos.find(tileName);
	if (iterator != tilesInfos.end())
	{
		TileInfo* tileInfo = iterator->second;
		sf::VertexArray tileOriginal = tileInfo->getOrientation(std::string(orientation))->quads->vertices;
		for (int i = 0; i < tileOriginal.getVertexCount(); i++)
		{
			sf::Vertex vertex = tileOriginal[i];
			/*sf::Vertex original = tileOriginal[i];
			sf::Vertex vertex;
			vertex.color = original.color;
			vertex.position = original.position;*/
			vertex.position.x += x;
			vertex.position.y += y;
			tileVertices.append(vertex);
		}
	}
	return tileVertices;
}
