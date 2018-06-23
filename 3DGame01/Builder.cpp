#include "Builder.h"


Builder::Builder(int id, std::string name, Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed) :
Unit(id,position,displayTexture,damage,health,rank,speed,onGround,BUILDER_TYPE,false,faction,buildSpeed),
_name(name),
_progress(0),
_isBuilding(false),
_building(NULL)
{
}


Builder::~Builder()
{
}

void Builder::draw()
{
	GFX::drawRect(32, 32, getPosition().x, getPosition().y, getDisplayTexture());
}
std::string Builder::getName()
{
	return _name;
}
void Builder::setName(std::string name)
{
	_name = name;
}
int Builder::getProgress()
{
	return _progress;
}
void Builder::setProgress(int progress)
{
	_progress = progress;
}


bool Builder::getIsBuiding()
{
	return _isBuilding;
}
void Builder::setIsBuilding(bool a)
{
	_isBuilding = a;
}
Building* Builder::getBuilding()
{
	return _building;
}
void Builder::setBuilding(Building* building)
{
	_building = building;
}

void Builder::build()
{
	if (_building->build() == true)
	{
		_isBuilding = false;
		std::cout << "Buildings finished building\n";
	}
}