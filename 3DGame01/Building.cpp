#include "Building.h"


Building::Building(Vector2f position, Vector2f size, std::string name, int type, Texture* texture, int id,int faction) :
_position(position),
_size(size),
_name(name),
_type(type),
_texture(texture),
_percentageBuild(0),
_isBuilt(false),
_id(id),
_faction(faction)
{
	_queue = new std::vector<Unit*>();
	_destination = position;
}

int Building::getId()
{
	return _id;
}
void Building::draw()
{
	GFX::drawRect(_size.x, _size.y, _position.x, _position.y, _texture);
}
Building::~Building()
{
	delete _texture;
	delete _queue;
}

void Building::setIsBuilding(bool a)
{
	_isBuilt = a;
	if (a == true)
	{
		_percentageBuild = 101;
	}
}

Vector2f Building::getPosition()
{
	return _position;
}
void Building::setPosition(Vector2f position)
{
	_position = position;
}
Vector2f Building::getSize()
{
	return _size;
}
void Building::setSize(Vector2f size)
{
	_size = size;
}
std::string Building::getName()
{
	return _name;
}
void Building::setName(std::string name)
{
	_name = name;
}
int Building::getType()
{
	return _type;
}
void Building::setType(int type)
{
	_type = type;
}
Texture* Building::getTexture()
{
	return _texture;
}
void Building::setTexture(Texture* texture)
{
	_texture = texture;
}
std::vector<Unit*>* Building::getQueue()
{
	return _queue;
}

void Building::setQueue(std::vector<Unit*>* queue)
{
	_queue = queue;
}

void Building::update()
{

}

int Building::getPercentageBuilt()
{
	return _percentageBuild;
}

bool Building::build()
{
	_percentageBuild++;
	if (_percentageBuild >= 100)
	{
		_isBuilt = true;
		return true;
	}
	return false;
}

bool Building::getIsBuilt()
{
	return _isBuilt;
}


int Building::getFaction()
{
	return _faction;
}
void Building::setFaction(int faction)
{
	_faction = faction;
}


void Building::setDestinationTile(Vector2f position)
{
	_destination = position;
}
Vector2f Building::getDestinationTile()
{
	return _destination;
}


void Building::addToQueue(Unit* unit)
{
	_queue->push_back(unit);
}