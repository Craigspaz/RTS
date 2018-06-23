#include "RectangleBox.h"


RectangleBox::RectangleBox(Vector2f position, Vector2f size):
_position(position),
_size(size)
{
}


void RectangleBox::setPosition(Vector2f position)
{
	_position = position;
}
void RectangleBox::setSize(Vector2f size)
{
	_size = size;
}
Vector2f RectangleBox::getPosition()
{
	return _position;
}
Vector2f RectangleBox::getSize()
{
	return _size;
}
bool RectangleBox::isOverlapping(RectangleBox box)
{
	float x = box.getPosition().x;
	float y = box.getPosition().y;
	float sizex = box.getSize().x;
	float sizey = box.getSize().y;

	if (_position.x > x && _position.x < x + sizex && _position.y > y && _position.y < y + sizey)
	{
		return true;
	}
	else if (_position.x + _size.x > x && _position.x + _size.x < x + sizex && _position.y > y && _position.y < y + sizey)
	{
		return true;
	}
	else if (_position.x > x && _position.x > x + sizex && _position.y + _size.y > y && _position.y + _size.y < y + sizey)
	{
		return true;
	}
	else if (_position.x + _size.x > x && _position.x + _size.x < x + sizex && _position.y + _size.y > y && _position.y + _size.y < y + sizey)
	{
		return true;
	}
	else
	{
		return false;
	}
}


RectangleBox::~RectangleBox()
{
}
