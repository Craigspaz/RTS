#ifndef _RECTANGLEBOX_H
#define _RECTANGLEBOX_H
#include "Vector.h"
/*Uses two vectors to make a rectangle*/
class RectangleBox
{
public:
	RectangleBox(Vector2f position, Vector2f size);
	~RectangleBox();
	void setPosition(Vector2f position);
	void setSize(Vector2f size);
	Vector2f getPosition();
	Vector2f getSize();
	bool isOverlapping(RectangleBox box);
private:
	Vector2f _position;
	Vector2f _size;
};

#endif