#ifndef _UNIT_H
#define _UNIT_H
/*Base class for each unit*/
#include "Vector.h"
#include "Textures.h"
#include "SystemDefs.h"
#include <vector>
#include "Tile.h"
#include "SystemDefs.h"
#include <thread>
#include <chrono>
#include "IslandListItem.h"
#include <fstream>
class Unit
{
public:
	Unit(int id,Vector2f position, std::vector<Texture*>* displayTexture,int damage, int health, int rank, float speed,bool onGround,int type, bool canAttack,int faction,float buildSpeed);
	virtual void draw() = 0;
	~Unit();

	Vector2f getPosition();
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	Texture* getDisplayTexture();
	void setDisplayTexture(Texture* texture);
	int getDamage();
	void setDamage(int damage);
	int getHealth();
	void setHealth(int health);
	int getRank();
	void setRank(int rank);
	float getSpeed();
	void setSpeed(float speed);
	bool getOnGround();
	void setOnGround(bool onGround);

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void moveUpLeft();
	void moveUpRight();
	void moveDownLeft();
	void moveDownRight();
	static bool findPath(Unit* unit, Tile* tiles[8192][8192], Tile* destination, int mapWidth, int mapHeight, bool ignoreDestination, std::vector<IslandListItem>* islandMap);
	void move(std::vector<Unit*>* units);
	bool getMoving();
	void setMoving(bool moving);
	bool isNextClearStationary(Tile* next, std::vector<Unit*>* units);

	Tile* getDestination();
	void setDestination(Tile* destination);

	std::vector<Tile*>* getPath();

	Tile* getNextTile();
	int getID();
	void setID(int id);
	bool getWait();
	void setWait(bool wait);
	void setCurrentMovementIndex(int index);
	bool getSelected();
	void setSelected(bool a);
	int getType();
	void clearPath();

	bool getCanAttack();
	void setCanAttack(bool a);
	int getFaction();
	void setFaction(int faction);
	float getPercentageBuilt();
	void build();
	bool getIsBuilt();
private:
	Vector2f _position;
	std::vector<Texture*>* _displayTexture;
	Texture* _textureToDisplay;
	int _damage;
	int _health;
	int _rank;
	float _speed;
	bool _onGround;
	bool _canAttack;
	std::vector<Tile*>* _path;
	int _pathSize;
	bool _moving;
	int _currentMovementIndex;
	Tile* _destination;

	Tile* _nextTile;
	int _id;
	bool _wait;
	bool _isSelected;
	int _type;
	int _faction;
	float _buildSpeed;
	float _percentageBuilt;
	bool _isBuilt;
};

#endif