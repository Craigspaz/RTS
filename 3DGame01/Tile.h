#ifndef _TILE_H
#define _TILE_H
/*This is the class of one square on the map*/
#include <string>
#include <sstream>
#include "Vector.h"
#include "SystemDefs.h"
#include "GFX.h"
class Tile
{
public:
	Tile(int id,Vector2f position, Texture* texture, bool travelable, Vector2f pathCoord, int type, std::string islandID);
	Tile();
	void draw();
	~Tile();
	Vector2f getPosition(); // This is hte position after being multiplied by texture width height
	void setPosition(Vector2f position);
	Texture* getTexture();
	void setTexture(Texture* texture);
	bool getTravelable(); //Pathfinding code
	void setTravelable(bool isSolid); //Pathfinding code
	Vector2f getPathCoord(); //This is the position without being multiplied by texture with and height
	void setPathCoord(Vector2f pathCoord);
	std::string debug(); //Used for debug purposes
	int getType();
	void setType(int type);
	Tile* getParent(); //Pathfinding code
	void setParent(Tile* parent); //Pathfinding code
	int getID(); //Pathfinding code
	int GCost(); //Pathfinding code
	int HCost(); //Pathfinding code
	int FCost(); //Pathfinding code
	void setFCost(int fcost); //Pathfinding code
	void setGCost(int gcost); //Pathfinding code
	void setHCost(int hcost); //Pathfinding code

	std::string getIslandID(); //Pathfinding code
	void setIslandID(std::string islandID); //Pathfinding code
	void changeToBridge(Texture* bridge);
	void destroyBridge();
private:
	Vector2f _position;
	Texture* _oldTexture;
	int _oldType;
	Texture* _texture;
	bool _travelable;
	Vector2f _pathCoord;
	int _type;
	Tile* _parent;
	int _gcost;
	int _hcost;
	int _fcost;
	int _id;
	std::string _islandID;
};

#endif