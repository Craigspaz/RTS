#include "BuildingItemsListItem.h"


BuildingItemsListItem::BuildingItemsListItem(std::string name, std::string description, int cost, Texture* texture, float buildSpeed, int itemType) :
_name(name),
_description(description),
_cost(cost),
_texture(texture),
_speedToBuild(buildSpeed),
_itemType(itemType)
{

}
BuildingItemsListItem::~BuildingItemsListItem()
{
	delete _texture;
}
std::string BuildingItemsListItem::getName()
{
	return _name;
}
std::string BuildingItemsListItem::getDescription()
{
	return _description;
}
int BuildingItemsListItem::getCost()
{
	return _cost;
}
Texture* BuildingItemsListItem::getTexture()
{
	return _texture;
}
int BuildingItemsListItem::getSpeedToBuild()
{
	return _speedToBuild;
}

int BuildingItemsListItem::getItemType()
{
	return _itemType;
}