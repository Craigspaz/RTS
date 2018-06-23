#include "IslandListItem.h"


IslandListItem::IslandListItem(std::string islandID1, std::string islandID2) :
_islandID1(islandID1),
_islandID2(islandID2)
{
}


IslandListItem::~IslandListItem()
{
}

std::string IslandListItem::getIslandID1()
{
	return _islandID1;
}

std::string IslandListItem::getIslandID2()
{
	return _islandID2;
}
