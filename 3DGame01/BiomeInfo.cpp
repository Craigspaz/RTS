#include "BiomeInfo.h"


BiomeInfo::BiomeInfo(std::string type, int x, int y) :
_type(type),
_x(x),
_y(y)
{
}

BiomeInfo::BiomeInfo()
{
	BiomeInfo("0", 0, 0);
}

BiomeInfo::~BiomeInfo()
{
}

void BiomeInfo::setX(int x)
{
	_x = x; 
}
void BiomeInfo::setY(int y)
{
	_y = y;
}
void BiomeInfo::setType(std::string type)
{
	_type = type;
}
int BiomeInfo::getX()
{
	return _x;
}
int BiomeInfo::getY()
{
	return _y;
}
std::string BiomeInfo::getType()
{
	return _type;
}
