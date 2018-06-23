#include "Soldier.h"


Soldier::Soldier(int id,std::string name, Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed):
Unit(id,position,displayTexture,damage,health,rank,speed,onGround,SOLDIER_TYPE,true,faction,buildSpeed),
_name(name)
{
}

void Soldier::draw()
{
	GFX::drawRect(32, 32, getPosition().x, getPosition().y, getDisplayTexture());
}


Soldier::~Soldier()
{
}
