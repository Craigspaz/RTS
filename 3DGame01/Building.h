#ifndef _BUILDING_H
#define _BUILDING_H

/*This is a class for a building*/

#include "Vector.h"
#include <string>
#include "GFX.h"
#include <vector>
#include "Unit.h"
#include "Tile.h"
class Building
{
public:
	Building(Vector2f position,Vector2f size,std::string name,int type,Texture* texture,int id, int faction);
	void draw();
	~Building();

	bool build(); //Builds the building

	Vector2f getPosition();
	void setPosition(Vector2f position);
	Vector2f getSize();
	void setSize(Vector2f size);
	std::string getName();
	void setName(std::string name);
	int getType();
	void setType(int type);
	Texture* getTexture();
	void setTexture(Texture* texture);
	std::vector<Unit*>* getQueue();
	void addToQueue(Unit* unit);
	void setQueue(std::vector<Unit*>* queue);
	void update();
	bool getIsBuilt();
	int getPercentageBuilt();
	int getId();
	void setIsBuilding(bool a);
	int getFaction();
	void setFaction(int faction);
	void setDestinationTile(Vector2f position);
	Vector2f getDestinationTile();
private:
	Vector2f _position;
	Vector2f _size;
	std::string _name;
	int _type;
	Texture* _texture;
	std::vector<Unit*>* _queue; //The queue of units to build
	int _percentageBuild; //How much of the building is built
	bool _isBuilt;
	int _id;
	int _faction;
	Vector2f _destination; //The destination point for units created at this building
};

#endif