#ifndef _BIOMEINFO_H
#define _BIOMEINFO_H
#include <iostream>
class BiomeInfo
{
public:
	BiomeInfo(std::string type, int x, int y);
	BiomeInfo();
	~BiomeInfo();

	void setX(int x);
	void setY(int y);
	void setType(std::string type);
	int getX();
	int getY();
	std::string getType();
private:
	int _x;
	int _y;
	std::string _type;
};

#endif