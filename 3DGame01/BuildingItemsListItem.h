#ifndef _BUILDINGLISTITEM_H
#define _BUIDLINGLISTITEM_H
#include "Texture.h"
#include <iostream>
#include <string>
/*An item to use in a list that will hold information on the construction of buildings*/
class BuildingItemsListItem
{
public:
	BuildingItemsListItem(std::string name, std::string description, int cost, Texture* texture,float speedToBuild, int itemType);
	~BuildingItemsListItem();
	std::string getName();
	std::string getDescription();
	int getCost();
	Texture* getTexture();
	int getSpeedToBuild();
	int getItemType();
private:
	std::string _name;
	std::string _description;
	int _cost;
	Texture* _texture;
	int _speedToBuild;
	int _itemType;
};

#endif