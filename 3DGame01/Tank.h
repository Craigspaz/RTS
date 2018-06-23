#ifndef _TANK_H
#define _TANK_H
/*Handles the tank unit*/
#include "Unit.h"
#include "GFX.h"
#include <string>
class Tank : public Unit
{
public:
	Tank(int id, std::string name,Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed);
	~Tank();
	void draw();
	std::string getName();
	void setName(std::string name);
private:
	std::string _name;
};

#endif