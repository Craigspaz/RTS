#ifndef _SOLDIER_H
#define _SOLDIER_H
/*This is the Soldier unit*/
#include "Unit.h"
#include <string>
#include "GFX.h"
class Soldier :
	public Unit
{
public:
	Soldier(int id,std::string name, Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed);
	void draw();
	~Soldier();
	std::string getName();
	void setName(std::string name);
private:
	std::string _name;
};

#endif