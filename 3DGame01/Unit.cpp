#include "Unit.h"


Unit::Unit(int id, Vector2f position, std::vector<Texture*>* displayTexture, int damage, int health, int rank, float speed, bool onGround, int type, bool canAttack, int faction, float buildSpeed) :
_position(position),
_displayTexture(displayTexture),
_damage(damage),
_health(health),
_rank(rank),
_speed(speed),
_onGround(onGround),
_pathSize(0),
_moving(false),
_currentMovementIndex(0),
_id(id),
_wait(false),
_isSelected(false),
_type(type),
_canAttack(canAttack),
_faction(faction),
_buildSpeed(buildSpeed),
_percentageBuilt(0),
_isBuilt(false)
{
	_textureToDisplay = _displayTexture->at(0);//Array of textures a unit may use
	_path = new std::vector<Tile*>();
	_nextTile = new Tile(-1, newVector2f(0, 0), NULL, true, newVector2f(0, 0), 0,"000");
}
Unit::~Unit()
{
	delete _displayTexture;
	delete _textureToDisplay;
	delete _path;
	delete _nextTile;
	delete _destination;
}

bool Unit::getIsBuilt()
{
	return _isBuilt;
}


float Unit::getPercentageBuilt()
{
	return _percentageBuilt;
}

void Unit::build()
{
	if (_percentageBuilt < 100)
	{
		_percentageBuilt += _buildSpeed;
		_isBuilt = false;
	}
	else{
		_isBuilt = true;
	}
}

Vector2f Unit::getPosition()
{
	return _position;
}
void Unit::setPosition(Vector2f position)
{
	_position = position;
}
void Unit::setPosition(float x, float y)
{
	_position = newVector2f(x, y);
}
Texture* Unit::getDisplayTexture()
{
	return _textureToDisplay;
}
void Unit::setDisplayTexture(Texture* texture)
{
	_textureToDisplay = texture;
}
int Unit::getDamage()
{
	return _damage;
}
void Unit::setDamage(int damage)
{
	_damage = damage;
}
int Unit::getHealth()
{
	return _health;
}
void Unit::setHealth(int health)
{
	_health = health;
}
int Unit::getRank()
{
	return _rank;
}
void Unit::setRank(int rank)
{
	_rank = rank;
}
float Unit::getSpeed()
{
	return _speed;
}
void Unit::setSpeed(float speed)
{
	_speed = speed;
}
bool Unit::getOnGround()
{
	return _onGround;
}
void Unit::setOnGround(bool onGround)
{
	_onGround = onGround;
}

void Unit::moveUp()
{
	_position.y -= _speed;
	_textureToDisplay = _displayTexture->at(0);
}
void Unit::moveDown()
{
	_position.y += _speed;
	_textureToDisplay = _displayTexture->at(1);
}
void Unit::moveLeft()
{
	_position.x -= _speed;
	_textureToDisplay = _displayTexture->at(2);
}
void Unit::moveRight()
{
	_position.x += _speed;
	_textureToDisplay = _displayTexture->at(3);
}


void Unit::moveUpLeft()
{
	_position.x -= _speed;
	_position.y -= _speed;
	_textureToDisplay = _displayTexture->at(4);
}
void Unit::moveUpRight()
{
	_position.x += _speed;
	_position.y -= _speed;
	_textureToDisplay = _displayTexture->at(5);
}
void Unit::moveDownRight()
{
	_position.x += _speed;
	_position.y += _speed;
	_textureToDisplay = _displayTexture->at(6);
}
void Unit::moveDownLeft()
{
	_position.x -= _speed;
	_position.y += _speed;
	_textureToDisplay = _displayTexture->at(7);
}

bool Unit::getCanAttack()
{
	return _canAttack;
}
void Unit::setCanAttack(bool a)
{
	_canAttack = a;
}


int Unit::getFaction()
{
	return _faction;
}
void Unit::setFaction(int faction)
{
	_faction = faction;
}

//helper function
bool checkList(std::vector<Tile> list, Tile search)
{
	for (std::vector<Tile>::iterator i = list.begin(); i != list.end(); i++)
	{
		if ((*i).getID() == search.getID())
		{
			return true;
		}
	}
	return false;
}

//helper function
int getH(Vector2f start, Vector2f end) //Used to calculate the heuristic in A* Manhattan
{
	return (abs(start.x - end.x) + abs(start.y - end.y));
}
bool Unit::findPath(Unit* unit, Tile* tiles[8192][8192], Tile* endTile, int mapWidth, int mapHeight, bool ignoreDestination, std::vector<IslandListItem>* islandMap)
{
	/*This is the A* Manhattan pathfinding algorithm*/
	unit->setSelected(true);
	std::cout << "Finding Path\n";
	double lastTime = glfwGetTime(); // Was used to determine if pathfinding was taking too long
	unit->getPath()->clear(); // Deletes old path
	unit->setMoving(true);
	Tile* startTile;
	if (unit->getPosition().x == 0 && unit->getPosition().y == 0) //sets start position. The if structure exist due to a rounding error
	{
		startTile = tiles[0][0];
	}
	else
	{
		startTile = tiles[(int)(unit->getPosition().x / TEXTUREWIDTH)][(int)(unit->getPosition().y / TEXTUREHEIGHT)];
	}
	if (ignoreDestination == false)
	{
		if (endTile->getTravelable() == false)//checks if destination can be walked on
		{
			unit->setMoving(false);
			return false;
		}
		if (endTile->getIslandID() != startTile->getIslandID())// checks if there is a path from start to end by checking if the start and destination are on different landmasses
		{
			bool broke = false;
			for (std::vector<IslandListItem>::iterator i = islandMap->begin(); i != islandMap->end(); i++)
			{
				IslandListItem a = *i;
				if (a.getIslandID1() == startTile->getIslandID() && a.getIslandID2() == endTile->getIslandID())
				{
					broke = true;
					break;
				}
			}
			if (broke)
			{
				std::cout << "Start ID: " << startTile->getIslandID() << " End ID: " << endTile->getIslandID() << std::endl;
				unit->setMoving(false);
				return false;
			}
		}
	}
	
	std::vector<Tile*>* openlist = new std::vector<Tile*>();// The Openlist - tiles that need to be checked
	std::vector<Tile*>* closedlist = new std::vector<Tile*>();// The Closedlist - tiles that have been checked
	openlist->push_back(startTile);
	startTile->setGCost(0);
	startTile->setHCost(getH(startTile->getPathCoord(), endTile->getPathCoord()));
	startTile->setFCost(startTile->GCost() + startTile->HCost());
	bool done = false;
	while (!openlist->empty())
	{
		Tile* currentTile = NULL;
		int lowestF = INT_MAX;
		int count = 0;
		int id = 0;
		//finds tiles with lowest F cost;
		for (std::vector<Tile*>::iterator i = openlist->begin(); i != openlist->end(); i++)
		{
			Tile* temp = *i;
			if (temp->FCost() < lowestF)
			{
				currentTile = *i;
				lowestF = temp->FCost();
				id = count;
			}
			count++;
		}
		// Checks if the tiles with the lowest F cost is the destination
		if (currentTile->getID() == endTile->getID() && currentTile->getPathCoord().x == endTile->getPathCoord().x && currentTile->getPathCoord().y == endTile->getPathCoord().y)
		{
			endTile->setParent(currentTile);
			done = true;
			break;
		}
		//removes the tile with the lowest F cost from the openlist and adds it to the closed list
		openlist->erase(openlist->begin() + id);
		closedlist->push_back(currentTile);
		int currentx = currentTile->getPathCoord().x;
		int currenty = currentTile->getPathCoord().y;
		bool uppermiddleTravelable = true;
		bool leftTravelable = true;
		bool rightTravelable = true;
		bool bottommiddleTravelable = true;
		if (currentx > 0) // Checks if the tile with the lowest F cost is not on the left border
		{
			Tile* left = NULL;
			left = tiles[currentx - 1][currenty];
			bool cont = true;
			leftTravelable = left->getTravelable();
			if (left->getPathCoord().x == endTile->getPathCoord().x && left->getPathCoord().y == endTile->getPathCoord().y)//checks if the tile left of the tile with the lowest F cost is the destination
			{
				left->setParent(currentTile);
				endTile = left;
				done = true;
				break;
			}
			if (left->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), left) != closedlist->end()) // if the left tile is not travelable or it is already in the closedlist then stop checking this tile
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the left tile and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 10;
				if (!(std::find(openlist->begin(), openlist->end(), left) != openlist->end()) || gscore < left->GCost())
				{
					left->setParent(currentTile);
					left->setGCost(gscore);
					left->setHCost(getH(left->getPathCoord(), endTile->getPathCoord()));
					left->setFCost(left->GCost() + left->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), left) != openlist->end()))
					{
						openlist->push_back(left);
					}
				}
			}
		}
		else
		{
			leftTravelable = false; 
		}
		if (currentx < mapWidth)//checks that the tile with the lowest F cost is not on the right border of the map
		{
			Tile* right = NULL;
			right = tiles[currentx + 1][currenty];
			rightTravelable = right->getTravelable();
			bool cont = true;
			if (right->getPathCoord().x == endTile->getPathCoord().x && right->getPathCoord().y == endTile->getPathCoord().y) // checks if right tile is the destination
			{
				right->setParent(currentTile);
				endTile = right;
				done = true;
				break;
			}
			if (right->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), right) != closedlist->end())// checks if the tile is not travelable or if it was already checked
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the right tile and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 10;
				if (!(std::find(openlist->begin(), openlist->end(), right) != openlist->end()) || gscore < right->GCost())
				{
					right->setParent(currentTile);
					right->setGCost(gscore);
					right->setHCost(getH(right->getPathCoord(), endTile->getPathCoord()));
					right->setFCost(right->GCost() + right->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), right) != openlist->end()))
					{
						openlist->push_back(right);
					}
				}
			}
		}
		else
		{
			rightTravelable = false;
		}
		if (currenty > 0) // checks that the tile with the lowest F cost is not on the top border of the map
		{
			Tile* uppermiddle = NULL;
			uppermiddle = tiles[currentx][currenty - 1];
			uppermiddleTravelable = uppermiddle->getTravelable();
			bool cont = true;
			if (uppermiddle->getPathCoord().x == endTile->getPathCoord().x && uppermiddle->getPathCoord().y == endTile->getPathCoord().y)//checks to see if the tile above is the destination
			{
				uppermiddle->setParent(currentTile);
				endTile = uppermiddle;
				done = true;
				break;
			}
			if (uppermiddle->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), uppermiddle) != closedlist->end()) //checks to see if the tile above was already checked or if it is not travelable
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the above tile and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 10;
				if (!(std::find(openlist->begin(), openlist->end(), uppermiddle) != openlist->end()) || gscore < uppermiddle->GCost())
				{
					uppermiddle->setParent(currentTile);
					uppermiddle->setGCost(gscore);
					uppermiddle->setHCost(getH(uppermiddle->getPathCoord(), endTile->getPathCoord()));
					uppermiddle->setFCost(uppermiddle->GCost() + uppermiddle->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), uppermiddle) != openlist->end()))
					{
						openlist->push_back(uppermiddle);
					}
				}
			}
		}
		else
		{
			uppermiddleTravelable = false;
		}
		if (currenty < mapHeight) //checks if the tile with the lowest F cost is not on the bottom border
		{
			Tile* bottommiddle = NULL;
			bottommiddle = tiles[currentx][currenty + 1];
			bottommiddleTravelable = bottommiddle->getTravelable();
			bool cont = true;
			if (bottommiddle->getPathCoord().x == endTile->getPathCoord().x && bottommiddle->getPathCoord().y == endTile->getPathCoord().y)//checks to see if the tile below the tile with the lowest F cost is the destination
			{
				bottommiddle->setParent(currentTile);
				endTile = bottommiddle;
				done = true;
				break;
			}
			if (bottommiddle->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), bottommiddle) != closedlist->end())// checks to see if the tile below is not travelable or if it was already checked
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the below tile and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 10;
				if (!(std::find(openlist->begin(), openlist->end(), bottommiddle) != openlist->end()) || gscore < bottommiddle->GCost())
				{
					bottommiddle->setParent(currentTile);
					bottommiddle->setGCost(gscore);
					bottommiddle->setHCost(getH(bottommiddle->getPathCoord(), endTile->getPathCoord()));
					bottommiddle->setFCost(bottommiddle->GCost() + bottommiddle->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), bottommiddle) != openlist->end()))
					{
						openlist->push_back(bottommiddle);
					}
				}
			}
		}
		else
		{
			bottommiddleTravelable = false;
		}
		if (currenty < mapHeight && currentx < mapWidth) // checks that the tile with the lowest F cost is not in the bottom right corner or along the right or bottom borders
		{
			Tile* bottomright = NULL;
			bottomright = tiles[currentx + 1][currenty + 1];
			bool cont = true;
			if (bottomright->getPathCoord().x == endTile->getPathCoord().x && bottomright->getPathCoord().y == endTile->getPathCoord().y)// checks if the tile to the right diagnal below of th tile with the lowest F cost is the destination 
			{
				if (!bottommiddleTravelable || !rightTravelable)//checks to see if it can not travel to the right or down. This makes traveling diagnal not overlap with walls
				{

				}
				else
				{
					bottomright->setParent(currentTile);
					endTile = bottomright;
					done = true;
					break;
				}
			}
			if (bottomright->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), bottomright) != closedlist->end() || (!bottommiddleTravelable) && (!rightTravelable))// checks to see if the diagnal right and below is already checked or not travelable
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the tile below and to the right of the tile wiht the lowest F cost and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 14;
				if (!bottommiddleTravelable || !rightTravelable)
				{
					gscore += 7;// This makes g cost much higher to make paths look better
				}
				if (!(std::find(openlist->begin(), openlist->end(), bottomright) != openlist->end()) || gscore < bottomright->GCost())
				{
					bottomright->setParent(currentTile);
					bottomright->setGCost(gscore);
					bottomright->setHCost(getH(bottomright->getPathCoord(), endTile->getPathCoord()));
					bottomright->setFCost(bottomright->GCost() + bottomright->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), bottomright) != openlist->end()))
					{
						openlist->push_back(bottomright);
					}
				}
			}
		}
		if (currentx > 0 && currenty > 0)// checks if the tile with the lowest F cost is in the top left corner or if it is along the top or left borders
		{
			Tile* upperleft = NULL;
			upperleft = tiles[currentx - 1][currenty - 1];
			bool cont = true;
			if (upperleft->getPathCoord().x == endTile->getPathCoord().x && upperleft->getPathCoord().y == endTile->getPathCoord().y)
			{
				if (!uppermiddleTravelable || !leftTravelable)//checks to see if it can not travel to the right or down. This makes traveling diagnal not overlap with walls
				{

				}
				else
				{
					upperleft->setParent(currentTile);
					endTile = upperleft;
					done = true;
					break;
				}
			}
			if (upperleft->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), upperleft) != closedlist->end() || (!uppermiddleTravelable && !leftTravelable))// checks to see if the tile to the left and up of the tile with the lowest F cost is travelable or already checked
			{
				cont = false;
			}
			if (cont)
			{
				//Sets the parameters of the tile below and to the right of the tile wiht the lowest F cost and adds it to the openlist if was not there and if necessary updates the info
				int gscore = currentTile->GCost() + 14;
				if (!uppermiddleTravelable || !leftTravelable)
				{
					gscore += 7;//makes diagnals look better
				}
				if (!(std::find(openlist->begin(), openlist->end(), upperleft) != openlist->end()) || gscore < upperleft->GCost())
				{
					upperleft->setParent(currentTile);
					upperleft->setGCost(gscore);
					upperleft->setHCost(getH(upperleft->getPathCoord(), endTile->getPathCoord()));
					upperleft->setFCost(upperleft->GCost() + upperleft->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), upperleft) != openlist->end()))
					{
						openlist->push_back(upperleft);
					}
				}
			}
		}
		
		if (currenty > 0 && currentx < mapWidth)//checks to see if the tile with the lowest F is not in the upper right corner or along the right border or the upper border
		{
			Tile* upperright = NULL;
			upperright = tiles[currentx + 1][currenty - 1];
			bool cont = true;
			if (upperright->getPathCoord().x == endTile->getPathCoord().x && upperright->getPathCoord().y == endTile->getPathCoord().y)// checks to see if the tile to the right and above the tile with the lowest F cost is the destination
			{
				if (!uppermiddleTravelable || !rightTravelable)//Fixes diagnals
				{

				}
				else
				{
					upperright->setParent(currentTile);
					endTile = upperright;
					done = true;
					break;
				}
			}
			if (upperright->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), upperright) != closedlist->end() || (!uppermiddleTravelable) && (!rightTravelable))
			{
				cont = false;
			}
			if (cont)
			{
				//sets the properties of the tile to the right and above the tile with the lowest F cost and fixes diagnals and adds it to the openlist
				int gscore = currentTile->GCost() + 14;
				if (!uppermiddleTravelable || !rightTravelable)
				{
					gscore += 7;
				}
				if (!(std::find(openlist->begin(), openlist->end(), upperright) != openlist->end()) || gscore < upperright->GCost())
				{
					upperright->setParent(currentTile);
					upperright->setGCost(gscore);
					upperright->setHCost(getH(upperright->getPathCoord(), endTile->getPathCoord()));
					upperright->setFCost(upperright->GCost() + upperright->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), upperright) != openlist->end()))
					{
						openlist->push_back(upperright);
					}
				}
			}
		}
		
		if (currentx > 0 && currenty < mapHeight)//Checks to see if the tile with the lowest F cost is not in the bottom left corner or along the bottom or left borders
		{
			Tile* bottomleft = NULL;
			bottomleft = tiles[currentx - 1][currenty + 1];
			bool cont = true;
			if (bottomleft->getPathCoord().x == endTile->getPathCoord().x && bottomleft->getPathCoord().y == endTile->getPathCoord().y)//checks to see if the tile to the left and down of the tile with the lowest F cost is the destination
			{
				if (!leftTravelable || !bottommiddleTravelable)//Fixes diagnals
				{

				}
				else
				{
					bottomleft->setParent(currentTile);
					endTile = bottomleft;
					done = true;
					break;
				}
			}
			if (bottomleft->getTravelable() == false || std::find(closedlist->begin(), closedlist->end(), bottomleft) != closedlist->end() || (!leftTravelable) && (!bottommiddleTravelable))// checks to see if the tile to the left and down of the tile with the lowest F cost is already checked or if it is not travelable
			{
				cont = false;
			}
			if (cont)
			{
				//Fixes diagnals and then sets the properties of the bottom left tile and then adds it to the openlist
				int gscore = currentTile->GCost() + 14;
				if (!leftTravelable || !bottommiddleTravelable)
				{
					gscore += 7;
				}
				if (!(std::find(openlist->begin(), openlist->end(), bottomleft) != openlist->end()) || gscore < bottomleft->GCost())
				{
					bottomleft->setParent(currentTile);
					bottomleft->setGCost(gscore);
					bottomleft->setHCost(getH(bottomleft->getPathCoord(), endTile->getPathCoord()));
					bottomleft->setFCost(bottomleft->GCost() + bottomleft->HCost());
					if (!(std::find(openlist->begin(), openlist->end(), bottomleft) != openlist->end()))
					{
						openlist->push_back(bottomleft);
					}
				}
			}
		}
	}
	if (done)// if the pathfinding finished. This builds the path
	{
		Tile* parent = endTile->getParent();
		unit->getPath()->push_back(endTile);
		while (parent->getID() != startTile->getID())
		{
			unit->getPath()->push_back(parent);
			parent = parent->getParent();
		}
		std::reverse(unit->getPath()->begin(), unit->getPath()->end());// the path is built backwards so this reverses it
		unit->setCurrentMovementIndex(0);// this is used to remember what tile in the path the unit is on
		std::cout << "Pathfinding Succeeded\n";
	}
	else
	{
		std::cout << "Pathfinding failed\n";
		return false;
	}
	unit->setSelected(false);
	return true;
}
int Unit::getID()
{
	return _id;
}
void Unit::setID(int id)
{
	_id = id;
}


bool Unit::isNextClearStationary(Tile* next, std::vector<Unit*>* units) // This calculate if the next tile has a unit on it
{
	for (std::vector<Unit*>::iterator i = units->begin(); i != units->end(); i++)
	{
		if ((*i)->getID() == getID())
		{
			continue;
		}
		//else if ((*i)->getNextTile()->getID() == getNextTile()->getID() && (*i)->getNextTile()->getID() != -1 && getNextTile()->getID() != -1)
		//{
		//	return false;
		//}
		else if ((int)((*i)->getPosition().x / TEXTUREWIDTH) == (int)next->getPathCoord().x && (int)((*i)->getPosition().y / TEXTUREHEIGHT) == (int)next->getPathCoord().y)
		{
			//if ((*i)->getMoving() == false)
			{
				return false;
			}
		}
		//else if ((int)(((*i)->getPosition().x + TEXTUREWIDTH) / TEXTUREWIDTH) == (int)next->getPathCoord().x && (int)((*i)->getPosition().y / TEXTUREHEIGHT) == (int)next->getPathCoord().y)
		//{
		//	//if ((*i)->getMoving() == false)
		//	{
		//		return false;
		//	}
		//}
		//else if ((int)(((*i)->getPosition().x + TEXTUREWIDTH) / TEXTUREWIDTH) == (int)next->getPathCoord().x && (int)(((*i)->getPosition().y + TEXTUREHEIGHT) / TEXTUREHEIGHT) == (int)next->getPathCoord().y)
		//{
		//	//if ((*i)->getMoving() == false)
		//	{
		//		return false;
		//	}
		//}
		//else if ((int)((*i)->getPosition().x / TEXTUREWIDTH) == (int)next->getPathCoord().x && (int)(((*i)->getPosition().y + TEXTUREHEIGHT) / TEXTUREHEIGHT) == (int)next->getPathCoord().y)
		//{
		//	//if ((*i)->getMoving() == false)
		//	{
		//		return false;
		//	}
		//}
	}
	return true;
}

Tile* Unit::getNextTile()
{
	return _nextTile;
}

void Unit::move(std::vector<Unit*>* units)
{
	//std::cout << "_pathSize = " << _path->size() << std::endl;
	//if (_currentMovementIndex < 0)
	//{
	//	_currentMovementIndex = 0;
	//	//std::cout << "Current Movement Index was less than 0\n";
	//}
	if (_currentMovementIndex >= _path->size())
	{
		//std::cout << "Current Movement Index was greater than Path size\n";
		_moving = false;
		return;
	}
	Tile* next = _path->at(_currentMovementIndex);
	_nextTile = next;
	Tile* nextSNext = NULL;
	bool nextNextExist = false;
	if (_currentMovementIndex + 1 < _path->size())
	{
		nextSNext = _path->at(_currentMovementIndex + 1);
		nextNextExist = true;
	}
	//int nx = nextSNext->getPathCoord().x * TEXTUREWIDTH;
	//int ny = nextSNext->getPathCoord().y * TEXTUREHEIGHT;
	int x = next->getPathCoord().x * TEXTUREWIDTH;
	int y = next->getPathCoord().y * TEXTUREHEIGHT;
	bool nextIsClear = isNextClearStationary(next, units);
	bool nextNextIsClear = false;
	bool m = true;
	if (nextNextExist)
	{
		nextNextIsClear = isNextClearStationary(nextSNext, units);
	}
	//if (_currentMovementIndex != 0)
	//std::cout << "NEXTX: " << x << ", NEXTY: " << y << std::endl;
	if ((int)_position.x == x && (int)_position.y == y)
	{
		_currentMovementIndex++;
		//std::cout << "Current Movement Index ++\n";
	}
	if (nextIsClear)
	{
		//std::cout << "Moving\n";
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
		if (_position.x - x > 0)
		{
			left = true;
		}
		if (_position.x - x < 0)
		{
			right = true;
		}
		if (_position.y - y > 0)
		{
			up = true;
		}
		if (_position.y - y < 0)
		{
			down = true;
		}

		if (left && up)
		{
			moveUpLeft();
		}
		else if (up && right)
		{
			moveUpRight();
		}
		else if (down && left)
		{
			moveDownLeft();
		}
		else if (down && right)
		{
			moveDownRight();
		}
		else if (left)
		{
			moveLeft();
		}
		else if (right)
		{
			moveRight();
		}
		else if (up)
		{
			moveUp();
		}
		else if (down)
		{
			moveDown();
		}
		up = false;
		down = false;
		left = false;
		right = false;
	}
}


bool Unit::getMoving()
{
	return _moving;
}
void Unit::setMoving(bool moving)
{
	_moving = moving;
}


Tile* Unit::getDestination()
{
	return _destination;
}
void Unit::setDestination(Tile* destination)
{
	_destination = destination;
}


std::vector<Tile*>* Unit::getPath()
{
	return _path;
}

bool Unit::getWait()
{
	return _wait;
}

void Unit::setWait(bool wait)
{
	_wait = wait;
}

void Unit::setCurrentMovementIndex(int index)
{
	_currentMovementIndex = index;
}

bool Unit::getSelected()
{
	return _isSelected;
}

void Unit::setSelected(bool a)
{
	_isSelected = a;
}

int Unit::getType()
{
	return _type;
}

void Unit::clearPath()
{
	_path->empty();
}