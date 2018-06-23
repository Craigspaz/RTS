#include "Tank.h"


Tank::Tank(int id,std::string name,Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed) :
Unit(id,position,displayTexture,damage,health,rank,speed,onGround,TANK_TYPE,true,faction,buildSpeed),
_name(name)
{
}

void Tank::draw()
{
	GFX::drawRect(32, 32, getPosition().x, getPosition().y, getDisplayTexture());
}


Tank::~Tank()
{
}


std::string Tank::getName()
{
	return _name;
}
void Tank::setName(std::string name)
{
	_name = name;
}
