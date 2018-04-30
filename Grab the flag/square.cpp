#include "square.h"


void Square::setType(int t)
{
	type = t;
}

void Square::setPlayer(int t)
{
	player = t;
}

void Square::setTool(char b)
{
	tool = b;
}

int Square::getType() const
{
	return type;
}

char Square::getTool()
{
	return tool;
}
