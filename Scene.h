#pragma once
#include <string>

class Scene
{
public :
	virtual bool initialize() = 0;
	virtual bool update(float frameTime) = 0;
	virtual bool draw() = 0;
	virtual std::string getErrorMessage() = 0;
};