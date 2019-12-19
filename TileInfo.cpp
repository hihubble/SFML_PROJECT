#include "TileInfo.h"

TileInfo::TileInfo()
{
}

void TileInfo::setName(std::string name_)
{
	name = name_;
}

std::string TileInfo::getName()
{
	return name;
}

void TileInfo::addOrientation(TileOrientation* tileOrientation)
{
	tileOrientations.insert(std::pair<std::string, TileOrientation*>(tileOrientation->name, tileOrientation));
}

TileOrientation* TileInfo::getOrientation(std::string orientation)
{
	auto iterator = tileOrientations.find(orientation);
	if (iterator != tileOrientations.end())
	{
		return iterator->second;
	}
	else
	{
		iterator = tileOrientations.find(std::string("Normal"));
		if (iterator != tileOrientations.end())
		{
			return iterator->second;
		}
	}
	return NULL;
}

TileOrientation::TileOrientation()
{
	quads = new VertexQuads();
}
