#ifndef _ISLANDLISTITEM_H
#define _ISLANDLISTITEM_H
#include <iostream>
class IslandListItem
{
public:
	IslandListItem(std::string islandID1, std::string islandID2);
	~IslandListItem();
	std::string getIslandID1();
	std::string getIslandID2();
private:
	std::string _islandID1;
	std::string _islandID2;
};

#endif