#ifndef _BUILDER_H
#define _BUILDER_H

/*This is the class for a builder unit*/

#include "Unit.h"
#include "Building.h"
class Builder : public Unit
{
public:
	Builder(int id,std::string name, Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround,int faction,float buildSpeed);
	~Builder();
	//TODO add construction
	void draw();
	std::string getName();
	void setName(std::string name);
	int getProgress();
	void setProgress(int progress);
	bool getIsBuiding();
	void setIsBuilding(bool a);
	Building* getBuilding();
	void setBuilding(Building* building);
	void build();
private:
	std::string _name; //Name of unit
	int _progress; //Progress of units creation
	bool _isBuilding; //Is the unit building
	Building* _building; //A pointer to the building being built
};

#endif