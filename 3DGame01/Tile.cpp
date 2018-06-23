#include "Tile.h"


Tile::Tile(int id, Vector2f position, Texture* texture, bool travelable, Vector2f pathCoord, int type, std::string islandID) :
_position(position),
_texture(texture),
_travelable(travelable),
_pathCoord(pathCoord),
_id(id),
_gcost(0),
_hcost(0),
_fcost(0),
_islandID(islandID),
_type(type)
{
}

Tile::Tile()
{
	std::cout << "POSSIBLE ERROR - DEFAULT USED!\n";
}


Tile::~Tile()
{
	delete _oldTexture;
	delete _texture;
	delete _parent;
}


Vector2f Tile::getPosition()
{
	return _position;
}
void Tile::setPosition(Vector2f position)
{
	_position = position;
}
Texture* Tile::getTexture()
{
	return _texture;
}
void Tile::setTexture(Texture* texture)
{
	_texture = texture;
}
bool Tile::getTravelable()
{
	return _travelable;
}
void Tile::setTravelable(bool travelable)
{
	_travelable = travelable;
}
Vector2f Tile::getPathCoord()
{
	return _pathCoord;
}
void Tile::setPathCoord(Vector2f pathCoord)
{
	_pathCoord = pathCoord;
}

void Tile::draw()
{
	GFX::drawRect(TEXTUREWIDTH, TEXTUREHEIGHT, _position.x, _position.y, _texture);
}
std::string Tile::debug()
{
	std::stringstream ss;
	ss << "PositionX: " << _position.x << ", PositionY: " << _position.y << std::endl;
	return ss.str();
}


int Tile::getType()
{
	return _type;
}
void Tile::setType(int type)
{
	_type = type;
}


Tile* Tile::getParent()
{
	return _parent;
}
void Tile::setParent(Tile* parent)
{
	_parent = parent;
}
int Tile::getID()
{
	return _id;
}


int Tile::GCost()
{
	return _gcost;
}
int Tile::HCost()
{
	return _hcost;
}
void Tile::setGCost(int gcost)
{
	_gcost = gcost;
}
void Tile::setHCost(int hcost)
{
	_hcost = hcost;
}


int Tile::FCost()
{
	return _fcost;
}
void Tile::setFCost(int fcost)
{
	_fcost = fcost;
}

std::string Tile::getIslandID()
{
	return _islandID;
}

void Tile::setIslandID(std::string islandID)
{
	_islandID = islandID;
}


void Tile::changeToBridge(Texture* bridge)
{
	_oldType = _type;
	_oldTexture = _texture;
	_type = BRIDGE;
	_texture = bridge;
	_travelable = true;
}
void Tile::destroyBridge()
{
	_type = _oldType;
	_texture = _oldTexture;
	_travelable = false;
}